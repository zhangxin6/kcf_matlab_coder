clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');


% testcase1  16*32
input1 = zeros(16,32);
for j=1:16
  for k=1:32
    input1(j,k) = j*128+k;
  end
end

stest_get_features(input1,1);


% testcase2  128*128
input1 = zeros(128,128);
for j=1:16
  for k=1:32
    input1(j,k) = j*128+k;
  end
end

stest_get_features(input1,2);

% testcase3  2048*1024
input1 = zeros(2048,1024);
for j=1:2048
  for k=1:1024
    input1(j,k) = j*128+k;
  end
end

stest_get_features(input1,3);
