clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');


% testcase1  2*2
input1 = zeros(4,2);
stest_gaussian_shaped_labels(input1,1);


% testcase2  256*128
input1 = zeros(128,256);

stest_gaussian_shaped_labels(input1,2);

%testcase3  1024*1024
input1 = zeros(1024,1024);

for j=1:1024
  for k=1:1024
    input1(j,k) = j*0.01;
  end
end

stest_gaussian_shaped_labels(input1,3);
