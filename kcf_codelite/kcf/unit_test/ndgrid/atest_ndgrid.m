clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');


% testcase1  4*2
input1 = zeros(2,2);
input2 = zeros(2,2);
input1 = 1:4;
input2 = 1:2;
stest_ndgrid(input1,input2,1);


% testcase2  256*128
input1 = 1:256;
input2 = 1:128;
stest_ndgrid(input1,input2,2);

%testcase3  1024*1024
input1 = 1:1024;
input2 = 1:2048;
stest_ndgrid(input1,input2,3);
