


img_files = dir('*.jpg');

for i=1:size(img_files,1)
    image = imread(img_files(i).name);
    image1 = image(41:90,131:270);
    if(i<10)
        imwrite(image1,strcat('./1/0000000',num2str(i),'.jpg'));
    else
         imwrite(image1,strcat('./1/000000',num2str(i),'.jpg'));
    end    
end
endl=1