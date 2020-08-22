#!/bin/bash
for((i=1;;i++))
do
  echo $i
  ./gen > garden.in
  ./a.out || break
  mv garden.out out1
  ./long || break
  mv garden.out out2
  diff -b out1 out2 || break
done
