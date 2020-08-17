#!/bin/bash
function main(){
  frame_begin=$1;
  frame_num=$2;
  seq=$3;
  feature_type=$4;

  rm ./mexa64/*.mexa64
  cp ../unit_test/*/mex_*.c ./
  cp /home/zhangxin/github_repo/kcf_m/*.m ./m_kcf
  name1="../color/"
  name2="$seq"
  name3="_p_def.h"
  str1=$name1$name2$name3
  cp $str1 ./p_def.h
  cp ../src/my_fft.h ./
  matlab -nodisplay -r "init_mexa64();quit"
  mv *.mexa64 ./mexa64
  rm *.c
  matlab -nodisplay -r "main($frame_begin,$frame_num,$seq,'$feature_type');quit">>./mirror_test.txt
}
rm mirror_test.txt
main 1 10 1 "gaussian"
main 1 10 1 "polynomial"
main 1 10 1 "linear"
main 1 10 2 "gaussian"
main 1 10 2 "polynomial"
main 1 10 2 "linear"
