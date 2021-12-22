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

elementArray* initElementArray(int siz){
  elementArray* eArr = (elementArray*) malloc(sizeof(elementArray));
  element* newArr = (element*) malloc(sizeof(element)*siz);
  int i;
  for (i=0; i<siz;i++){
    newArr[i] = initNullElement();
  }
  eArr->arr = newArr;
  eArr->currSize=0;
  eArr->size = siz;
  return eArr;
} 


int elementComparator(element e1, element e2){
  int out = e1.value - e2.value;
  return !out ? 1 : out;
}

int getElementArrayMaxValue(elementArray* eArr){
  return eArr->arr[(eArr->currSize)-1].step +1;
}


int elementBinarySearch(elementArray* array, int s, int e, element find) {
  //printf("s->%d,e->%d,value->%d\n",s,e,find.value);
  int m,comp;
  if ( (e==-1) || find.value > array->arr[e].value){
    return e+1;
  }
  m = (s + e)/2;
  comp = elementComparator(array->arr[m],find);
  //printf("comp->%d\n",comp);
  if (!comp)
    return m;
  else if (comp<0)  
    return elementBinarySearch(array, m+1, e, find);
  else
    return elementBinarySearch(array, s, m-1, find);
}


void printElementArray(elementArray* eArr){
  printf("ArraySize=%d\n",eArr->currSize);
  int i = 0;
  int size = eArr->currSize;
  for (i=0;i<size;i++){
    printf("Value=%d\tReps=%d\tSteps=%d\n",eArr->arr[i].value,eArr->arr[i].reps,eArr->arr[i].step);
    printf("|\n");
  }
}


void handleAddToElementArray(elementArray* eArr, int value){
  element elem = newElementWithValue(value);
  int ind = elementBinarySearch(eArr,0,eArr->currSize-1,elem);
  int removed = removeIfNecessary(eArr,&elem,ind);
  //printf("Removing -> %d\n",removed);
  if (!removed){
    shiftRightElementArray(eArr,ind);
  }
  addToElementArray(eArr,elem,ind);
  if (removed>1){
    shiftLefElementArray(eArr,ind,removed-1);
  }
}

void printElement(element elem){
  printf("Value=%d\tReps=%d\tSteps=%d\n",elem.value,elem.reps,elem.step);
}

void setElementReps(elementArray* eArr,int ind, element* elem){
  if (!ind){
    elem->reps=1;
  } else {
    element indElement = eArr->arr[ind-1];
    while (((indElement.step + 1) == elem->step)){
      elem->reps+=indElement.reps;
      ind--;
      if (ind-1 <0){
        break;
      }
      indElement = eArr->arr[ind-1];
    }
  }
}


int removeIfNecessary(elementArray* eArr, element* elem, int ind){
  int removing=0;
  int maxInd = eArr->size -1;
  //printElement(*elem);
  elem->step = !ind ? 0 : eArr->arr[ind-1].step +1; 
  
  setElementReps(eArr,ind,elem);
  
  if (ind != eArr->currSize && eArr->currSize!=0){
    while ( (eArr->arr[ind].step < elem->step) && (ind < eArr->currSize)){
      removing++;
      ind++;
    }
    eArr->currSize -= removing;
    return removing;
  } else {
    return 1;
  }
}

void shiftRightElementArray(elementArray* eArr,int ind){
  int size = eArr->currSize;
  while (size>ind){
    eArr->arr[size] = eArr->arr[size-1];
    size--;
  }
}

void shiftLefElementArray(elementArray* eArr, int ind, int jump){
  int initInd = eArr->currSize-1;
  while ((initInd-jump) > ind){
    eArr->arr[initInd-jump] = eArr->arr[initInd];
    initInd--;
  }
}

void addToElementArray(elementArray* eArr, element elem, int ind){
  eArr->arr[ind] = elem;
  eArr->currSize++;
}

int numberOfMaxSizeSubseq(elementArray* eArr, int max){
  int ind = eArr->currSize-1;
  int out=0;
  element indElement = eArr->arr[ind];
  while (indElement.step+1 == max){
    out += indElement.reps;
    ind--;
    if (ind<0){
      break;
    }
    indElement = eArr->arr[ind];
  }
  return out;
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
  int max=0,hMany,ind;
  elementArray* elementArr = initElementArray(size);
  //printVetor(vet);
  for (ind=0;ind<size;ind++){
    handleAddToElementArray(elementArr,getVetorValue(vet,ind));
    //printElementArray(elementArr);
    //printf("DONE\n");
  }
  max = getElementArrayMaxValue(elementArr);
  hMany = numberOfMaxSizeSubseq(elementArr,max);
  printf("%d %d\n",max,hMany);
}

int main(){
  
  char exercise;
  scanf("%c\n",&exercise);
  if (exercise=='1'){
    runExercise1();
  } else {
    printf("Hello\n");
  }
  return 0;
}