function [positions, time] = tracker(video_path, img_files, pos, target_sz, ...
	padding, kernel, lambda, output_sigma_factor, interp_factor, cell_size, ...
	features, show_visualization,frame_begin, frame_num, seq)

    fp = fopen(['pos_' num2str(seq) '.txt'],'w');
	resize_image = (sqrt(prod(target_sz)) >= 100);  
	if resize_image,
		pos = floor(pos / 2);
		target_sz = floor(target_sz / 2);
    end
	window_sz = [256 128];
	output_sigma = sqrt(prod(target_sz)) * output_sigma_factor / cell_size;
    if isfield(features, 'deep') && features.deep
        yf = fft2(gaussian_shaped_labels(output_sigma, ceil(window_sz / cell_size)));
    else
        yf = fft2(gaussian_shaped_labels(output_sigma, floor(window_sz / cell_size)));
    end

	cos_window = hann(size(yf,1)) * hann(size(yf,2))';	
	
	
	if show_visualization,  %create video interface
		update_visualization = show_video(img_files, video_path, resize_image);
	end


	time = 0;  %to calculate FPS
	positions = zeros(frame_num, 2);  %to calculate precision
	for frame = (frame_begin):(frame_begin + frame_num - 1)
		im = imread([video_path img_files(frame).name]);
        if ~isfield(features, 'deep')
            if size(im,3) > 1,
                im = rgb2gray(im);
            end
        end
		if resize_image,
			im = imresize(im, 0.5);
        end
		tic()
		if frame > frame_begin,
			patch = get_subwindow(im, pos, window_sz);
			zf = fft2(get_features(patch, features, cell_size, cos_window));
			switch kernel.type
			case 'gaussian',
				kzf = gaussian_correlation(zf, model_xf, kernel.sigma);
			case 'polynomial',
				kzf = polynomial_correlation(zf, model_xf, kernel.poly_a, kernel.poly_b);
			case 'linear',
				kzf = linear_correlation(zf, model_xf);
			end
			response = real(ifft2(model_alphaf .* kzf));  %equation for fast detection
			[vert_delta, horiz_delta] = find(response == max(response(:)), 1);
			if vert_delta > size(zf,1) / 2,  %wrap around to negative half-space of vertical axis
				vert_delta = vert_delta - size(zf,1);
			end
			if horiz_delta > size(zf,2) / 2,  %same for horizontal axis
				horiz_delta = horiz_delta - size(zf,2);
			end
			pos = pos + cell_size * [vert_delta - 1, horiz_delta - 1];
		end

		%obtain a subwindow for training at newly estimated target position
		patch = get_subwindow(im, pos, window_sz);
		xf = fft2(get_features(patch, features, cell_size, cos_window));

		%Kernel Ridge Regression, calculate alphas (in Fourier domain)
		switch kernel.type
		case 'gaussian',
			kf = gaussian_correlation(xf, xf, kernel.sigma);
		case 'polynomial',
			kf = polynomial_correlation(xf, xf, kernel.poly_a, kernel.poly_b);
		case 'linear',
			kf = linear_correlation(xf, xf);
		end
		alphaf = yf ./ (kf + lambda);   %equation for fast training

		if frame == frame_begin,  %first frame, train with a single image
			model_alphaf = alphaf;
			model_xf = xf;
		else
			%subsequent frames, interpolate model
			model_alphaf = (1 - interp_factor) * model_alphaf + interp_factor * alphaf;
			model_xf = (1 - interp_factor) * model_xf + interp_factor * xf;
		end

		%save position and timing
		positions(frame,:) = pos;
        fprintf(fp,'%f %f\n',pos(1),pos(2));
		time = time + toc();

		%visualization
		if show_visualization,
			box = [pos([2,1]) - target_sz([2,1])/2, target_sz([2,1])];
			stop = update_visualization(frame, box);
			if stop, break, end  %user pressed Esc, stop early
			drawnow
% 			pause(0.05)  %uncomment to run slower
		end
		
    end
	if resize_image,
		positions = positions * 2;
    end
    fclose(fp);
end

