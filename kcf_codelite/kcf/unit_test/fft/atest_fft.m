clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');

% testcase1  1*8
input1 = [1+i,2+i,3+i,4+i,5+i,6-i,7+i,8+i];
input2 = 8;
stest_fft(input1,input2,1);


% testcase2  1*256
input1 = zeros(1,256);
for j=1:256
    input1(j) = 0.1*(j-2i);
end
input2 = 256;
stest_fft(input1,input2,2);

%t
input1 = zeros(1,1024);
for j=1:1024
    input1(j) = 0.01*(1 + i*j);
end
input2 = 1024;
stest_fft(input1,input2,3);
