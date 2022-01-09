#/bin/bash

rm  *CTime/*
rm  RDTime/*

runsPerTest=100

for OCTest in DOCTests/DC*
do
	echo $OCTest
	s=${OCTest##*/}
	for ((n = 0 ; n < $runsPerTest ; n++ ));
	do
		./file < $OCTest | sed -n 2p >> DCTime/${s%.*}.out
	done
done	


for OCTest in DOCTests/OC*
do
	echo $OCTest
	s=${OCTest##*/}
	for ((n = 0 ; n < $runsPerTest ; n++ ));
	do
		./file < $OCTest | sed -n 2p >> OCTime/${s%.*}.out
	done
done	


for OCTest in DOCTests/RC*
do
	echo $OCTest
	s=${OCTest##*/}
	for ((n = 0 ; n < $runsPerTest ; n++ ));
	do
		./file < $OCTest | sed -n 2p >> RCTime/${s%.*}.out
	done
done	



for OCTest in DOCTests/RD*
do
	echo $OCTest
	s=${OCTest##*/}
	for ((n = 0 ; n < $runsPerTest ; n++ ));
	do
		./file < $OCTest | sed -n 2p >> RDTime/${s%.*}.out
	done
done	














