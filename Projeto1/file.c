#include "file.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define VETOR_BASE_SIZE 2
#define BUFFER_SIZE 128



/* VETOR */

vetor* initVetor(){
   vetor *vet = (vetor*) malloc(sizeof(vetor));
   vet->arr = (int*) malloc(sizeof(int)*VETOR_BASE_SIZE);
   vet->size = VETOR_BASE_SIZE;
   vet->currSize = 0;
   return vet;
}

void addToVetor(vetor *vet,int new){
   if (vet->size == vet->currSize){
      vet->size*=2;
      vet->arr = (int*) realloc(vet->arr,sizeof(int)*(vet->size));
   }
  vet->arr[vet->currSize] = new;
  vet->currSize++;
}

int getVetorValue(vetor* vet, int pos){
  return vet->arr[pos];
}

void printVetor(vetor *vet){ /*Checking if everything is fine*/
   int i;
   for (i=0;i<(vet->currSize);i++){
      printf("%d,",vet->arr[i]);
   }
   printf("\n");
}

void freeVetor(vetor *vet){
   free(vet->arr);
   free(vet);
}

int* zeroArray(int size){
   int *arr = (int*) malloc(sizeof(int)*size);
   int i;
   for(i=0;i<size;i++){
      arr[i]=0;
   }
   return arr;
}

// ELEMENT

element initNullElement(){
  element new;
  new.value = INFINITY;
  return new;
}

element newElementWithValue(int val){
  element new;
  new.value = val;
  new.step=0;
  new.reps=0;
  return new;
}

elementArray* initElementArray(int size){
  elementArray* eArr = (elementArray*) malloc(sizeof(elementArray));
  element* newArr = (element*) malloc(sizeof(element)*size);
  int i;
  for (i=0; i<size;i++){
    newArr[i] = initNullElement();
  }
  eArr->arr = newArr;
  eArr->currSize=0;
  return eArr;
} 


int elementComparator(element e1, element e2){
  int out = e1.value - e2.value;
  return !out ? -1 : out;
}

int getElementArrayMaxValue(elementArray* eArr){
  return eArr->arr[(eArr->currSize)-1].value;
}


int elementBinarySearch(elementArray* array, int s, int e, element find) {
  int m,comp;
  if ( (e==-1) || find.value > array->arr[e].value){
    return e+1;
  }
  m = (s + e)/2;
  comp = elementComparator(array->arr[m],find);
  if (!comp)
    return m;
  else if (comp<0)  
    return binarySearch(array, m+1, e, find);
  else
    return binarySearch(array, s, m-1, find);
}

void handleAddToElementArray(elementArray* eArr, int value){
  element elem = newElementWithValue(value);
  int ind = elementBinarySearch(eArr,0,eArr->currSize-1,elem);
  char removed = removeIfNecessary(eArr,&elem,ind);
  if (!removed){
    shiftRightElementArray(eArr,ind);  
    eArr->currSize++;
  }
  addToElementArray(eArr,elem,ind);

}

char removeIfNecessary(elementArray* eArr, element* elem, int ind){
  if (!ind){
    return 0;
  }
  element indElement = eArr->arr[ind];
  elem->step = eArr->arr[ind-1].step; 
  return indElement.step < elem->step; 
}

void shiftRightElementArray(elementArray* eArr,int ind){
  int size = eArr->currSize;
  while (size>ind){
    eArr->arr[size] = eArr->arr[size-1];
  }
}

void addToElementArray(elementArray* eArr, element elem, int ind){
  eArr->arr[ind] = elem;
}



vetor* getVetorFromInput(){
  vetor* vet = initVetor();
  char finishedReading = 0;
  char buffer[BUFFER_SIZE];
  while (!finishedReading){
    buffer[BUFFER_SIZE-2]='\0';
    fgets(buffer,BUFFER_SIZE,stdin);
    if (buffer[BUFFER_SIZE-2]=='\0'){
      finishedReading = 1;
    }
    parseInput(vet,buffer);
  }
  return vet;
}

void parseInput(vetor* vet, char* buffer){
  char c;
  char read = 0;
  char ind = 0;
  int i;

  while ((c=buffer[ind])!='\0' && c!='\n'){
    if (c!=' ' && !read){
      i = atoi(&buffer[ind]);
      addToVetor(vet,i);
      read=1;
    }
    if (c==' ') {read = 0;}
    ind++;
  }
}

void runExercise1(){
  vetor* vet = getVetorFromInput();
  exercise1(vet);
}

void exercise1(vetor* vet){
  int size = vet->currSize;
  int ind=0,max=0,hMany;
  elementArray* elementArr = initElementArray(size);
  while (size-max>=ind){
    handleAddToElementArray(elementArr,getVetorValue(vet,ind));
    max = getElementArrayMaxValue(elementArr);
  }
  hMany = numberOfMaxSizeSubseq(elementArr,max);
  pritnf("%d %d\n",max,hMany);
}

int main(){
  
  char exercise;
  scanf("%c\n",&exercise);
  if (exercise=='1'){
    runExercise1();
  } else {
    printf("Hello\n");
  }

   vetor* vet = getVetorFromInput();
   printVetor(vet);

   return 0;
}