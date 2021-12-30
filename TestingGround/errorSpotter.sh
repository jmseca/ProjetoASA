#/bin/bash

testNumber=39

rm file.out pythonfile.out


for i in RandomTests/*
do
    #echo $i
    ./file < $i >> file.out 
    python3 correct2.py < $i >> pythonfile.out
done


diff file.out pythonfile.out

