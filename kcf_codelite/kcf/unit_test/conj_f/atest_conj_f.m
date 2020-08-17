clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');


% testcase1  2*2
input1 = zeros(2,2);
input1 = [1+i,2-i;3+i,4-i];
stest_conj_f(input1,1);


% testcase2  256*128
input1 = zeros(256,128);
for j=1:256
  for k=1:128
    input1(j,k) = j*0.1+2i;
  end
end

stest_conj_f(input1,2);

%testcase3  1024*1024
input1 = zeros(1024,1024);

for j=1:1024
  for k=1:1024
    input1(j,k) = j*0.01+3i;
  end
end

stest_conj_f(input1,3);
