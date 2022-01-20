import random as ra

dir = "RandomTests/"
sizeLim1,sizeLim2 = 10,15

tests = 100

for n in range(tests):
    mystr='2\n'
    arr1Size = ra.randint(sizeLim1,sizeLim2)
    arr2Size = ra.randint(sizeLim1,sizeLim2)
    for t1 in range(arr1Size):
        mystr+=str(ra.randint(0,5))+' '
    mystr+='\n'
    for t1 in range(arr2Size):
        mystr+=str(ra.randint(0,5))+' '
    mystr+='\n'
    f = open(dir+"Random"+str(n)+".in","w")
    f.write(mystr)
    f.close()
    n+=1

