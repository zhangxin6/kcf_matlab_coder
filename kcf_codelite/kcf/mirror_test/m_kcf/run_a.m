function []=run_a(frame_begin,frame_num,seq,feature_type)
  clc;close all;
  if (nargin < 3)
     frame_begin =1 ;
     frame_num =101 ;
     seq = 2;
  end
  data_path =  ['/home/zhangxin/Desktop/codelite/kcf/color/' num2str(seq)];

  run_tracker(data_path, feature_type, 'gray', true, true, frame_begin,frame_num,seq);

  endl = 1
