clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');

% testcase1  2*4
input1 = [1+5i,2+5i,3+5i,4+5i;5+5i,6+5i,7+5i,8+5i];
input2= 4;
input3 = 2;
stest_ifft2(input1,input2,input3,1);

% testcase2  2*4
input1 = [1+i,2+i,3+i,4+i;5+i,6+i,7+i,8+i];
input2= 4;
input3 = 2;
stest_ifft2(input1,input2,input3,2);
% testcase3  256*128
input1 = zeros(256,128);
for j=1:256
  for k=1:128
    input1(j,k) = j*128+k*i;
  end
end

input2 = 128;
input3 = 256;
stest_ifft2(input1,input2,input3,3);

%testcase4  1024*2048
input1 = zeros(1024,2048);
for j=1:1024
  for k=1:2048
    input1(j,k) = (j+k*i);
  end
end
input2 = 2048;
input3 = 1024;
stest_ifft2(input1,input2,input3,4);
