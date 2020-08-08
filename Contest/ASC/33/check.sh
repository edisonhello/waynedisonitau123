#!/bin/bash
for((i=0;;i++))
do
  ./gen > points.in
  ./a.out
  ./bf < points.in > bf.out
  diff points.out bf.out || break
done
