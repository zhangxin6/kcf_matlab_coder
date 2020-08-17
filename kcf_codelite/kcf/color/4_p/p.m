filename = 'ground_rect_3.txt';
f = fopen(filename);
assert(f ~= -1, ['No initial position or ground truth to load ("' filename '").'])
fp = fopen('ground_rect_4.txt','w');
for i=1:80
  tline = fgetl(f);

    t1 = regexp(tline,',','split');
    ground_truth(1,1) = str2num(t1{1})-130;
    ground_truth(1,2) = str2num(t1{2})-40;
    ground_truth(1,3) = str2num(t1{3});
    ground_truth(1,4) = str2num(t1{4});

    fprintf(fp,'%d,%d,%d,%d\n',ground_truth(1,1),ground_truth(1,2),ground_truth(1,3),ground_truth(1,4));
end
fclose(fp);
fclose(f);imtoor
endl=1
