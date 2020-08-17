function []=kcf_single(frame_begin,frame_num)

    if (nargin < 4)
       frame_begin = 1 ;
       frame_num = 80 ;
    end
    data_path =  ['/home/zhangxin/Desktop/codelite/kcf/color/4'];
    run_tracker(data_path,frame_begin,frame_num);
    endl = 1


    function [precision, fps] = run_tracker(data,frame_begin,frame_num)
      base_path = '/home/zhangxin/Desktop/codelite/kcf/color/';
      [pos,target_sz,video_path] = load_video_info(base_path,data,frame_begin);
      [positions] = tracker(base_path,video_path,pos,target_sz,frame_begin,frame_num);
    end

    function [pos, target_sz, video_path] = load_video_info(base_path, video, frame_begin)
        gt0 = 117;
        gt1 = 23;
        gt2 = 12;
        gt3 = 13;

        video_path = [video '/'];
    	target_sz = [gt3, gt2];
    	pos = [gt1, gt0] + floor(target_sz/2);
    end

    function [positions] = tracker(base_path,video_path,pos,target_sz,frame_begin,frame_num)

        padding = 1.5;
        lambda = 1e-4;
        output_sigma_factor = 0.1;
        interp_factor = 0.075;
        cell_size = 1;

        box_w = 16;
        box_h = 16;

        fp = fopen(['pos_4.txt'],'w');
        window_sz =[box_w box_h];
        model_xf = zeros(box_w,box_h);
        model_alphaf = zeros(box_w,box_h);
        %%%%%%%%%%%%%%%%%
    	output_sigma = sqrt(prod(target_sz)) * output_sigma_factor;
        yf = fft2(gaussian_shaped_labels(output_sigma, floor(window_sz)));
    	cos_window = hann(size(yf,1)) * hann(size(yf,2))';

    	positions = zeros(frame_num, 2);  %to calculate precision
    	for frame = (frame_begin):(frame_begin + frame_num - 1)
    		im = zeros(50,140);
            if size(im,3) > 1,
                im = rgb2gray(im);
            end
            if frame == frame_begin,
                patch = get_subwindow(im, pos, window_sz);
        		xf = fft2(get_features(patch, cos_window));
        		%Kernel Ridge Regression, calculate alphas (in Fourier domain)
        		kf = linear_correlation(xf, xf);
        		alphaf = yf ./ (kf + lambda);
                model_alphaf = alphaf;
    			model_xf = xf;
            else
    			patch = get_subwindow(im, pos, window_sz);
    			zf = fft2(get_features(patch,cos_window));
    		    kzf = linear_correlation(zf, model_xf);
                response = real(ifft2(model_alphaf .* kzf));
    			[vert_delta, horiz_delta] = find(response == max(response(:)), 1);
    			if vert_delta > size(zf,1) / 2,  %wrap around to negative half-space of vertical axis
    				vert_delta = vert_delta - size(zf,1);
    			end
    			if horiz_delta > size(zf,2) / 2,  %same for horizontal axis
    				horiz_delta = horiz_delta - size(zf,2);
    			end
    			pos = pos + [vert_delta - 1, horiz_delta - 1];
    		    %obtain a subwindow for training at newly estimated target position
    		    patch = get_subwindow(im, pos, window_sz);
    		    xf = fft2(get_features(patch, cos_window));
    		    %Kernel Ridge Regression, calculate alphas (in Fourier domain)
    		    kf = linear_correlation(xf, xf);
    		    alphaf = yf ./ (kf + lambda);   %equation for fast training
    		    model_alphaf = (1 - interp_factor) * model_alphaf + interp_factor * alphaf;
    		    model_xf = (1 - interp_factor) * model_xf + interp_factor * xf;
    		end
    		%save position and timing
    		positions(frame,:) = pos;
            fprintf(fp,'%f %f\n',pos(1),pos(2));
        end
        fclose(fp);
    end

    function labels = gaussian_shaped_labels(sigma, sz)
    	[rs, cs] = ndgrid((1:sz(1)) - floor(sz(1)/2), (1:sz(2)) - floor(sz(2)/2));
    	labels = exp(-0.5 / sigma^2 * (rs.^2 + cs.^2));
    	labels = circshift(labels, -floor(sz(1:2) / 2) + 1);
    end

    function out = get_subwindow(im, pos, sz)
    	xs = floor(pos(2)) + (1:sz(2)) - floor(sz(2)/2);
    	ys = floor(pos(1)) + (1:sz(1)) - floor(sz(1)/2);
    	%check for out-of-bounds coordinates, and set them to the values at
    	%the borders
    	xs(xs < 1) = 1;
    	ys(ys < 1) = 1;
    	xs(xs > size(im,2)) = size(im,2);
    	ys(ys > size(im,1)) = size(im,1);
    	%extract image
    	out = im(ys, xs, :);
    end

    function x = get_features(im,cos_window)
    	x = double(im) / 255;
    	x = x - mean(x(:));
    	if ~isempty(cos_window),
    		x = bsxfun(@times, x, cos_window);
    	end
    end

    function kf = linear_correlation(xf, yf)
    	kf = sum(xf .* conj(yf), 3) / numel(xf);
    end

end
