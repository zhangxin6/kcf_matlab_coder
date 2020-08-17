clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');

% testcase0  8*2
input1 = zeros(8,2);
input2 = zeros(8,2);
input1 = [1+i,i;1-i,-1-i;3+2i,4-6i;3+2i,8-7i;3+2i,9-6i;3+2i,4-11i;3+2i,20-21i;3+5i,7-6i];
input2 = [3+i,i;1-4i,-1-2i;5+2i,4-6i;3+7i,8-7i;4+5i,9-6i;3+2i,4-11i;3+2i,10-21i;76+2i,11-5i];
input3 = 0.2;
stest_gaussian_correlation(input1,input2,input3,0);

% testcase1  2*2
input1 = zeros(2,2);
input2 = zeros(2,2);
input1 = [1+i,i;1-i,-1-i];
input2 = [3+2i,4-3i;8+5i,7-6i];
input3 = 0.2;
stest_gaussian_correlation(input1,input2,input3,1);


% testcase2  256*128
input1 = zeros(256,128);
input2 = zeros(256,128);
for j=1:256
  for k=1:128
    input1(j,k) = j+k*i;
  end
end

for j=1:256
  for k=1:128
    input2(j,k) = 2*j+3*k*i;
  end
end
input3 = 0.2;
stest_gaussian_correlation(input1,input2,input3,2);

%testcase3  1024*1024
input1 = zeros(1024,1024);
input2 = zeros(1024,1024);

for j=1:1024
  for k=1:1024
    input1(j,k) = j-k*i;
  end
end

for j=1:1024
  for k=1:1024
    input2(j,k) = 100*j+200*k*i;
  end
end
input3 = 0.2;
stest_gaussian_correlation(input1,input2,input3,3);
% testcase2  256*128
input1 = zeros(256,128);
input2 = zeros(256,128);
for j=1:256
  for k=1:128
    input1(j,k) = j+k*i;
  end
end

for j=1:256
  for k=1:128
    input2(j,k) = 2*j+3*k*i;
  end
end
input3 = 0.4;
stest_gaussian_correlation(input1,input2,input3,4);
