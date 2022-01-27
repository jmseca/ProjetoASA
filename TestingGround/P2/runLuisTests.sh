#/bin/bash

make

rm smol_tests/myout

for i in smol_tests/testsOrdenados/*.in
do
  ./fileCopy < $i >> smol_tests/myout
done


diff smol_tests/myout smol_tests/luisOut 

