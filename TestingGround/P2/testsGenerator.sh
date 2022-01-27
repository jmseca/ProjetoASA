#/bin/bash

make

rm Tests/*

baseSize=100
addSize=100
testNumber=100
zeros=""

getDigits () {
  arg=$1
  if [ $arg -eq 0 ]; then
    return 1
  fi
	ret=0
	while [ $arg -ne 0 ]
	do
		arg=$((arg / 10)) 
		ret=$((ret + 1))

	done
  return $ret
}

getDigits $testNumber
maxDigits=$?

for ((n = 0 ; n < $testNumber ; n++ ));
do
	testSize=$((baseSize * n))
	testSize=$((testSize + baseSize))
	forLimit=$testNumber/10
	getDigits $n
	testDigits=$?
	zeros=
	for ((i = 0 ; i < $((maxDigits - testDigits)) ; i++ ));
	do 
		zeros+=0
	done
	file=Tests/test$zeros$n 
	./randGeneoTree $testSize 0.5 > $file
done

