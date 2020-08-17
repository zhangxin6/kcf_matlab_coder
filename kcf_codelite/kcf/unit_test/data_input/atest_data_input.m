clc; close all;clear all;

p1 = mfilename('fullpath');
j=findstr(p1,'/');
p1=p1(1:j(end));
cd(p1);
addpath('../');

% testcase1  128
input1 = zeros(1,128);
input2 = '128.txt';
stest_data_input(input1,input2,1);


% testcase2  256
input1 = zeros(1,256);
input2 = '256.txt';
stest_data_input(input1,input2,2);

% testcase3  32768
input1 = zeros(1,32768);
input2 = '32768.txt';
stest_data_input(input1,input2,3);
