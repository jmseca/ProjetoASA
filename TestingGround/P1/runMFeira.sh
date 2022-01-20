#/bin/bash

i=0

rm MFeira/*

for inputFile in ~/IST/proj-ist-unit-tests/asa/2021-2022/asa-p1/tests/p1*.in
do
    #echo $inputFile
    if [ $i -gt 9 ]; then
        ../Projeto1/file < $inputFile > MFeira/myout$i.out
    else
        ../Projeto1/file < $inputFile > MFeira/myout0$i.out
    fi
    i=$((i+1))
done


rm MFeira/allOut.out

arrMyOut=(MFeira/myout*)
arrTestOut=(~/IST/proj-ist-unit-tests/asa/2021-2022/asa-p1/tests/p1*.out)


for ((n = 0 ; n < $((i-1)) ; n++ ));
do
    #echo $n
    diff ${arrMyOut[$n]} ${arrTestOut[$n]} >> MFeira/allOut.out
    echo "||||||||||||\n||||||||||" >> MFeira/allOut.out
done



