clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');


% testcase1  432*576
input1 = zeros(432,576);
for j=1:432
  for k=1:576
    input1(j,k) = j*128+k;
  end
end
input2 = [100,150];
stest_get_subwindow(input1,input2,1);

% testcase2
input2 = [3,200];
stest_get_subwindow(input1,input2,2);


% testcase3
input2 = [420,570];
stest_get_subwindow(input1,input2,3);
