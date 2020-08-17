cd './4';  type='.txt';
s = dir(cd);
for i=1:size(s,1)
  as = regexp(s(i).name,'\.','split');
  if(size(as,1)<1 || size(as,2)<2)
      continue;
  else
      if (as{1,2} == "jpg")
        im = imread(s(i).name);
        if size(im,3) > 1,
                im = rgb2gray(im);
        end
        fid = fopen([as{1,1} '.txt'],'wb');
        %fid = fopen(['0000' as{1,1} '.txt'],'wb');
        fwrite(fid,im,'short');
        fclose(fid);
      end
  end
end
endl=1
