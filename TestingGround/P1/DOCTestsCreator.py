import random as ra


mydir = "DOCTests/"
base=100
delta=100
num=100
sizes = [base+(n*delta) for n in range(num)]
sizeStr = [str(n) for n in range(num)]

okok = len(sizeStr)
for i in range(okok):
  if len(sizeStr[i])==1:
    sizeStr[i]='0'+sizeStr[i]

# Random for Ex2
ID='Ex2-'
n=0
for size in sizes:
  print("Vamos no size="+sizeStr[n])
  mystr=''
  for i in range(size):
    mystr+=(str(ra.randint(0,size))+" ")
  mystr+='\n'
  for i in range(size):
    mystr+=(str(ra.randint(0,size))+" ")
  mystr+='\n'
  f = open(mydir+ID+sizeStr[n]+".in","w")
  f.write("2\n"+mystr)
  f.close()
  n+=1


asas #remove to run tests1

# Ordenadas crescente
ID = "OC-"
previous=0
n=0
for size in sizes:
  print("Vamos no size="+sizeStr[n])
  mystr=''
  for i in range(size):
    mystr+=(str(i)+" ")
  f = open(mydir+ID+sizeStr[n]+".in","w")
  f.write("1\n"+mystr)
  f.close()
  n+=1



# Ordenadas decrescente
ID="DC-"
n=0
for size in sizes:
  print("Vamos no size="+sizeStr[n])
  mystr=''
  for i in range(size,0,-1):
    mystr+=(str(i)+" ")
  f = open(mydir+ID+sizeStr[n]+".in","w")
  f.write("1\n"+mystr)
  f.close()
  n+=1



# Random 1 - Concentrado
ID="RC-"
n=0
for size in sizes:
  print("Vamos no size="+sizeStr[n])
  mystr=''
  for i in range(size):
    mystr+=(str(ra.randint(0,round(size/4)))+" ")
  f = open(mydir+ID+sizeStr[n]+".in","w")
  f.write("1\n"+mystr)
  f.close()
  n+=1

# Random 2 - Disperso
ID="RD-"
n=0
for size in sizes:
  print("Vamos no size="+sizeStr[n])
  mystr=''
  for i in range(size):
    mystr+=(str(ra.randint(0,(size*4)))+" ")
  f = open(mydir+ID+sizeStr[n]+".in","w")
  f.write("1\n"+mystr)
  f.close()
  n+=1


# Tests by me
