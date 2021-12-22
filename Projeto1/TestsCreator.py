import random as ra


# Ordenadas crescente
OCTestId = "OC"
n=0
sizes = [10**2,10**3,10**4,10**5,10**6,10**7]
sizeStr = ["10_2","10_3","10_4","10_5","10_6","10_7"]
types = ["one","two","random"]

previous=0
for type in types:
  print("type="+type)
  n=0
  for size in sizes:
    mystr=''
    if type=='one':
      for i in range(size):
        mystr+=(str(i)+" ")
    elif type=="two":
      for i in range(size):
        mystr+=(str(i*2)+" ")
    else:
      for i in range(size):
        rint = ra.randint(1,5)
        previous+=rint
        mystr+=(str(previous)+" ")
    f = open(OCTestId+type+sizeStr[n]+".in","w")
    f.write("1\n"+mystr)
    f.close()
    n+=1



# Ordenadas decrscente


# Random



# Tests by me