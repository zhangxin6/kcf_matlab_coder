function [img_files, pos, target_sz, ground_truth, video_path] = load_video_info(base_path, video, frame_begin,seq)
	video_path = [video '/'];

	%try to load ground truth from text file (Benchmark's format)
	filename = [base_path 'ground_rect_' num2str(seq) '.txt'];
	f = fopen(filename);
	assert(f ~= -1, ['No initial position or ground truth to load ("' filename '").'])
    for i=1:frame_begin
      tline = fgetl(f);
    end 
    t1 = regexp(tline,',','split');
    ground_truth(1,1) = str2num(t1{1});
    ground_truth(1,2) = str2num(t1{2});
    ground_truth(1,3) = str2num(t1{3});
    ground_truth(1,4) = str2num(t1{4});
	fclose(f);

	target_sz = [ground_truth(1,4), ground_truth(1,3)];
	pos = [ground_truth(1,2), ground_truth(1,1)] + floor(target_sz/2);
    img_files = dir([video_path '*.jpg']);
end
