#!/usr/bin/env bash
n=1000000
m=1000
d=10
declare -a file=("interchange" "insertion" "merge" "flash")
for i in `seq 4 4`
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
