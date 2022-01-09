import matplotlib.pyplot as plt
import os
import math

LeDir = ["OCTime/","RDTime/","DCTime/","Ex2Time/"]
xPoints=[i for i in range(1,101)]
k1=5
k2=5
yPointsLog = [round(i*math.log(i,2)) for i in xPoints]
yPointsKLog = [k1*el for el in yPointsLog]
yPointsN2 = [(i**2) for i in xPoints]
yPointsKN2 = [k2*el for el in yPointsN2]
yDC=[]
yOC=[]
yRD=[]
yE2=[]
yFuncPoints = [yOC,yRD,yDC,yE2]
xPoints = [i*100 for i in range(1,101)]

n=0
for TestsDir in LeDir:
    Tests = os.listdir(TestsDir)
    Tests.sort()
    for test in Tests:
        f = open(TestsDir+test,'r')
        keepReading=True
        line = f.readlines()
        timeArr = [int(el[:-1]) for el in line]
        size = 20
        timeArr.sort()
        soma = sum(timeArr[40:61])
        media = round(soma/size)
        yFuncPoints[n]+=[media]
    n+=1

# Plot

lW = '2.5' #linewidth

plt.plot(xPoints,yPointsLog,':',color='black',label='n.log(n)')
plt.plot(xPoints,yPointsKLog,'--',color='black',label='k.n.log(n), k=5')
plt.plot(xPoints,yOC,color='r',linewidth = lW,label='Vetor Ordem Crescente')
plt.plot(xPoints,yRD,color='b',linewidth = lW,label='Vetor Random')
plt.plot()
plt.title("Problema 1 - Sem pior caso")
plt.xlabel("Tamanho do Vetor (n)")
plt.ylabel("Clock ticks (ct)")
plt.legend()
plt.savefig("P1V1.png")
plt.clf()

plt.plot(xPoints,yPointsKN2,'-.',color='black',label='k.n^2, k=5')
plt.plot(xPoints,yPointsN2,'--',color='black',label='n^2')
plt.plot(xPoints,yPointsKLog,':',color='black',label='k.n.log(n), k=5')
plt.plot(xPoints,yOC,color='r',linewidth = lW, label='Vetor Ordem Crescente')
plt.plot(xPoints,yRD,color='b',linewidth = lW,label='Vetor Random')
plt.plot(xPoints,yDC,color='g',linewidth = lW,label='Vetor Ordem Decrescente')
plt.plot()
plt.title("Problema 1")
plt.xlabel("Tamanho do Vetor (n)")
plt.ylabel("Clock ticks (ct)")
plt.legend()
plt.savefig("P1V2.png")
plt.clf()


yPointsK2N2 = [10*el for el in yPointsN2]
plt.plot(xPoints,yPointsK2N2,'-.',color='black',label='k.n^2. k=10')
plt.plot(xPoints,yPointsKN2,':',color='black',label='k.n^2, k=5')
plt.plot(xPoints,yE2,color='b',label='Vetores Random')
plt.plot()
plt.title("Problema 2")
plt.xlabel("Tamanho dos Vetores (n)")
plt.ylabel("Clock ticks (ct)")
plt.legend()
plt.savefig("P2.png")
plt.clf()

plt.plot(xPoints,yPointsK2N2,'-.',color='black',label='k.n^2. k=10')
plt.plot(xPoints,yPointsN2,'--',color='black',label='n^2')
plt.plot(xPoints,yPointsKLog,':',color='black',label='k.n.log(n), k=5')
plt.plot(xPoints,yE2,color='r',linewidth = lW,label='P2 Random')
plt.plot(xPoints,yDC,color='b',linewidth = lW,label='P1 Ordem Decrescente')
plt.plot(xPoints,yRD,color='g',linewidth = lW,label='P1 Random')
#plt.plot(xPoints,yOC,color='g',linewidth = lW, label='P1 Ordem Crescente')

plt.title("Análise Experimental do Projeto1")
plt.xlabel("Tamanho do(s) Vetor(es) (n)")
plt.ylabel("Clock ticks (ct)")
plt.legend()
plt.savefig("Mega.png")
plt.clf()