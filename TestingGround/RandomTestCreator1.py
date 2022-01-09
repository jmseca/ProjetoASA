import random as ra

dir = "RandomTests/"
fixedSize = 3
testsPerType = 10
for n in range(testsPerType):
    mystr=''
    for i in range((10**fixedSize)):
        mystr+=(str(ra.randint(-2000,20000))+' ')

    f = open(dir+"Random"+str(n)+"-10_"+str(fixedSize)+".in","w")
    f.write("1\n"+mystr)
    f.close()
    n+=1


for n in range(testsPerType,testsPerType*2):
    mystr=''
    for i in range(10**fixedSize):
        mystr+=(str(ra.randint(-200,2000))+' ')

    f = open(dir+"Random"+str(n)+"-10_"+str(fixedSize)+".in","w")
    f.write("1\n"+mystr)
    f.close()
    n+=1  


for n in range(testsPerType*2,testsPerType*3):
    mystr=''
    for i in range(10**fixedSize):
        mystr+=(str(ra.randint(-70000,-1))+' ')

    f = open(dir+"Random"+str(n)+"-10_"+str(fixedSize)+".in","w")
    f.write("1\n"+mystr)
    f.close()
    n+=1 

for n in range(testsPerType*3,testsPerType*4):
    mystr=''
    for i in range(10**fixedSize):
        mystr+=(str(ra.randint(0,99))+' ')

    f = open(dir+"Random"+str(n)+"-10_"+str(fixedSize)+".in","w")
    f.write("1\n"+mystr)
    f.close()
    n+=1 