#/bin/bash

source "testsGenerator.sh"

runsPerTest=100

rm TestTimes/*

getDigits $testNumber
maxDigits=$?

n=0
for test in Tests/*
do
  getDigits $n
	testDigits=$?
  zeros=
  for ((i = 0 ; i < $((maxDigits - testDigits)) ; i++ ));
	do 
		zeros+=0
	done
	file=TestTimes/time$zeros$n.out
  (( n++ )) 
  for ((m = 0 ; m < $runsPerTest ; m++ ));
  do
    ./fileTime < $test >> $file
  done
done
