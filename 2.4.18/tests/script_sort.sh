#!/usr/bin/env bash
n=10000000
m=500
d=10
declare -a file=("interchange" "insertion" "merge" "flash")
for i in `seq 1 4`
do
	s=${file[$i-1]}
	j=$d
	((k=2*j))
	echo "$s $j $n"
	./index_sort $n $j 0 $i > $s
	for j in `seq $k $j $m`
	do
		echo "$s $j $n"
		./index_sort $n $j 0 $i >> $s
	done
done
