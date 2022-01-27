import matplotlib.pyplot as plt
import os
import math


SaveDir = '/mnt/c/Users/joaom/Documents/IST/2º Ano/Semestre1/ASA/Projetos/Parte2/'
testsDir = "Tests/"
testTimesDir = "TestTimes/"
tests = os.listdir(testsDir)
VEs = []
tests.sort()
for test in tests:
  f = open(testsDir+test,'r')
  f.readline()
  stri = str(f.readline())
  ve =  [int(i) for i in stri.split(' ')]
  VEs += [ve]


yTimePoints = [-1]*len(tests)

times = os.listdir(testTimesDir)
times.sort()

n=0
for time in times:
  f = open(testTimesDir+time,'r')
  line = f.readlines()
  timeArr = [int(el[:-1]) for el in line]
  size = 20
  timeArr.sort()
  soma = sum(timeArr[40:61])
  media = round(soma/size)
  yTimePoints[n]=media
  n+=1


xPointsPre = [sum(subl) for subl in VEs]

lW = '2.5' #linewidth



plt.plot(xPointsPre,yTimePoints,color='r',linewidth = lW,label='Problema 2')
plt.plot()
plt.title("Problema 2")
plt.xlabel("Vertices + Arestas (V+E)")
plt.ylabel("Clock ticks (ct)")
plt.legend()
plt.savefig(SaveDir+"Projeto2.jpg")
plt.clf()





