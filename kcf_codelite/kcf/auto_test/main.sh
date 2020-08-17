#!/bin/bash
function main(){
  frame_begin=$1;
  frame_num=$2;
  seq=$3;

  name1="../color/"
  name2="$seq"
  name3="_p_def.h"
  str1=$name1$name2$name3
  cp $str1 ../src/p_def.h

  matlab -nodisplay -r "gen_line;quit"
  sh test.sh
  chmod 777 ../Debug/kcfs
  ./../Debug/kcfs $frame_begin $frame_num $seq

  cd ./../../../kcf_m
  matlab -nodisplay -r "run_a($frame_begin,$frame_num,$seq);quit"
  mv pos_*.txt /home/zhangxin/Desktop/codelite/kcf/output

  cd ./../kcf_codelite/kcf/auto_test
  cp ../color/ground_rect*.txt ../output
  matlab -nodisplay -r "add_rect($frame_begin,$frame_num,$seq);quit"

  rm ../Debug/*
  rm test.sh
  rm kcfsz.txt
}

main 1 80 4
