#!/bin/bash
rm unit_test.txt
list=$(find -iname atest_*)
for i in ${list[@]}
do
  j=$(echo $i|awk -F '/' '{print $3}'|awk -F '.' '{print $1}')
  t=$(echo $j|awk -F 'atest_' '{print $2}')
  echo $t
  cd $t
  matlab -nodisplay -r "$j;quit">>../unit_test.txt
  cd ../
done
