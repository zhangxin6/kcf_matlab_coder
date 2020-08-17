clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');



% testcase1  2*4
input1 = [1,2,3,4;5,6,7,8];
input2= 4;
input3 = 2;
stest_fft2_d(input1,input2,input3,1);
% testcase2  256*128
input1 = zeros(256,128);
for j=1:256
  for k=1:128
    input1(j,k) = j*128;
  end
end

input2 = 128;
input3 = 256;
stest_fft2_d(input1,input2,input3,2);

%testcase3  1024*2048
input1 = zeros(1024,2048);
for j=1:1024
  for k=1:2048
    input1(j,k) = j;
  end
end
input2 = 2048;
input3 = 1024;
stest_fft2_d(input1,input2,input3,3);
