clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');


% testcase1  2*2
input1 = zeros(2,2);
input2 = zeros(2,2);
input1 = [1+i,i;1-i,-1-i];
input2 = [3+2i,4-3i;8+5i,7-6i];
stest_div_f(input1,input2,1);


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

stest_div_f(input1,input2,2);

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

stest_div_f(input1,input2,3);
