#/bin/bash

testNumber=39


for i in RandomTests/*
do
    #echo $i
    ./file < $i >> file.out 
    python3 correct.py < $i >> pythonfile.out
done

