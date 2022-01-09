#/bin/bash

rm Ex2Time/*

runsPerTest=100

for OCTest in DOCTests/Ex*
do
	echo $OCTest
	s=${OCTest##*/}
	for ((n = 0 ; n < $runsPerTest ; n++ ));
	do
		./file < $OCTest | sed -n 2p >> Ex2Time/${s%.*}.out
	done
done	
