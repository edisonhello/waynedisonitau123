#!/bin/bash

for((i=0;;i++))
do
  echo $i
  ./gen > in 2> /dev/null
  ./b.out < in > out1 2> /dev/null
  ./bf < in > out2 2> /dev/null
  diff out1 out2 || break
done
