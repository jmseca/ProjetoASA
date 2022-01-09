#/bin/bash

testNumber=39

rm file.out pythonfile.out
rm RandomTests/*

cp ../Projeto1/file.cpp fileCopy.cpp
make cpp

echo "(1) Problema 1 || (2) Problema 2"
read x

if [ $x -eq 1 ]; then
	pyFile=correct1.py
	python3 RandomTestCreator1.py
else 
	pyFile=correct2.py
	python3 RandomTestCreator2.py
fi


for i in RandomTests/*
do
    #echo $i
    ./file < $i >> file.out 
    python3 $pyFile < $i >> pythonfile.out
done


diff file.out pythonfile.out

