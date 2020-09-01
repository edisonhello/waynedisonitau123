#!/bin/bash
for((i=0;;i++))
do
  echo $i
  ./gen > in
  ./a.out < in || break
done
