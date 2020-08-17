
%
%  High-Speed Tracking with Kernelized Correlation Filters
%
%  Joao F. Henriques, 2014
%  http://www.isr.uc.pt/~henriques/
%
%  Main interface for Kernelized/Dual Correlation Filters (KCF/DCF).
%  This function takes care of setting up parameters, loading video
%  information and computing precisions. For the actual tracking code,
%  check out the TRACKER function.
%
%  RUN_TRACKER
%    Without any parameters, will ask you to choose a video, track using
%    the Gaussian KCF on HOG, and show the results in an interactive
%    figure. Press 'Esc' to stop the tracker early. You can navigate the
%    video using the scrollbar at the bottom.
%
%  RUN_TRACKER VIDEO
%    Allows you to select a VIDEO by its name. 'all' will run all videos
%    and show average statistics. 'choose' will select one interactively.
%
%  RUN_TRACKER VIDEO KERNEL
%    Choose a KERNEL. 'gaussian'/'polynomial' to run KCF, 'linear' for DCF.
%
%  RUN_TRACKER VIDEO KERNEL FEATURE
%    Choose a FEATURE type, either 'hog' or 'gray' (raw pixels).
%
%  RUN_TRACKER(VIDEO, KERNEL, FEATURE, SHOW_VISUALIZATION, SHOW_PLOTS)
%    Decide whether to show the scrollable figure, and the precision plot.
%
%  Useful combinations:
%  >> run_tracker choose gaussian hog  %Kernelized Correlation Filter (KCF)
%  >> run_tracker choose linear hog    %Dual Correlation Filter (DCF)
%  >> run_tracker choose gaussian gray %Single-channel KCF (ECCV'12 paper)
%  >> run_tracker choose linear gray   %MOSSE filter (single channel)
%


function [precision, fps] = run_tracker(data, kernel_type, feature_type, show_visualization, show_plots, frame_begin, frame_num,seq)
  base_path = '/home/zhangxin/Desktop/codelite/kcf/color/';

	%default settings
	if (nargin < 1)
    video = choose_video(base_path);
  else
    video = data;
  end

	if nargin < 2, kernel_type = 'gaussian'; end
	if nargin < 3, feature_type = 'hog'; end
	if nargin < 4, show_visualization = true; end
	if nargin < 5, show_plots = true; end



	kernel.type = kernel_type;
	features.gray = false;
	features.hog = false;
	padding = 1.5;  %extra area surrounding the target
	lambda = 1e-4;  %regularization
	output_sigma_factor = 0.1;  %spatial bandwidth (proportional to target)

	switch feature_type
	case 'gray',
		interp_factor = 0.075;  %linear interpolation factor for adaptation
		kernel.sigma = 0.2;  %gaussian kernel bandwidth
		kernel.poly_a = 1;  %polynomial kernel additive term
		kernel.poly_b = 7;  %polynomial kernel exponent
		features.gray = true;
		cell_size = 1;
	case 'hog',
		interp_factor = 0.02;
		kernel.sigma = 0.5;
		kernel.poly_a = 1;
		kernel.poly_b = 9;
		features.hog = true;
		features.hog_orientations = 9;
		cell_size = 4;
  case 'deep'
    interp_factor = 0.02;
		kernel.sigma = 0.5;
		kernel.poly_a = 1;
		kernel.poly_b = 9;
		features.deep = true;
		cell_size = 8;
    init_vgg;
	otherwise
		error('Unknown feature.')
	end


	[img_files, pos, target_sz, ground_truth, video_path] = load_video_info(base_path, video, frame_begin,seq);
	%call tracker function with all the relevant parameters
	[positions, time] = tracker(video_path, img_files, pos, target_sz, padding, kernel, lambda, output_sigma_factor, interp_factor, ...
		cell_size, features, show_visualization, frame_begin, frame_num, seq);
end
