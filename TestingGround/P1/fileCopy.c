/*#include "file.h"*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/*#include <time.h>*/
#include <string.h>


#define VETOR_BASE_SIZE 2
#define BUFFER_SIZE 128

/*Structs*/
typedef struct {
   long int size;
   long int currSize;
   int* arr;
} vetor;

typedef struct {
  int value;
  long int reps;
  long int step;
} element;

typedef struct {
  element* arr;
  long int currSize;
  long int size;
} elementArray;

/*.h stuff*/

element initNullElement();

elementArray* initElementArray(int size);

int elementComparator(element e1, element e2);

int elementBinarySearch(elementArray* array, int s, int e, element find);

int removeIfNecessary(elementArray* eArr, element* elem, int ind);

void shiftRightElementArray(elementArray* eArr,int ind);

void shiftLefElementArray(elementArray* eArr, int ind, int jump);

void handleAddToElementArray(elementArray* eArr, int value);

void addToElementArray(elementArray* eArr, element elem, int ind);

int getElementArrayMaxValue(elementArray* eArr);

void setElementReps(elementArray* eArr,int ind, element* elem);

long int numberOfMaxSizeSubseq(elementArray* eArr, int max);

void printElementArray(elementArray* eArr);

/* Main */

int getCutNumber(char** prev, int* prevSize, char* buffer, short* ind);

int possibleCutNumber(char** prev, int* prevSize, char* buffer);

void parseInput(vetor* vet, char* buffer, char** prev, int* prevSize);

vetor* getVetorFromInput();

short runExercise1();

void exercise1(vetor* vet);

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

/* ELEMENT*/

element initNullElement(){
  element new;
  new.value = 0;
  return new;
}

element newElementWithValue(int val){
  element new;
  new.value = val;
  new.step=0;
  new.reps=0;
  return new;
}

char elementSameValueSameStep(element e1, element e2){
  return (e1.step == e2.step) && (e1.value == e2.value);
}

elementArray* initElementArray(int siz){
  elementArray* eArr = (elementArray*) malloc(sizeof(elementArray));
  element* newArr = (element*) malloc(sizeof(element)*siz);
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
  int size = eArr->currSize;
  return !size ? 0: eArr->arr[(size-1)].step +1;
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
    return elementBinarySearch(array, m+1, e, find);
  else
    return elementBinarySearch(array, s, m-1, find);
}


void printElementArray(elementArray* eArr){
  printf("ArraySize=%ld\n",eArr->currSize);
  int i = 0;
  int size = eArr->currSize;
  for (i=0;i<size;i++){
    printf("Value=%d\tReps=%ld\tSteps=%ld\n",eArr->arr[i].value,eArr->arr[i].reps,eArr->arr[i].step);
    printf("|\n");
  }
}


void handleAddToElementArray(elementArray* eArr, int value){
  element elem = newElementWithValue(value);
  int ind = elementBinarySearch(eArr,0,eArr->currSize-1,elem);
  int removed = removeIfNecessary(eArr,&elem,ind);
  if (removed==-1){
    return;
  }
  if (!removed){
    shiftRightElementArray(eArr,ind);
  }
  addToElementArray(eArr,elem,ind);
  if (removed>1){
    shiftLefElementArray(eArr,ind,removed-1);
  }
}

void printElement(element elem){
  printf("Value=%d\tReps=%ld\tSteps=%ld\n",elem.value,elem.reps,elem.step);
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
  elem->step = !ind ? 0 : eArr->arr[ind-1].step +1; 
  
  setElementReps(eArr,ind,elem);
  
  if (ind != eArr->currSize && eArr->currSize!=0){
    while ( (eArr->arr[ind].step < elem->step) && (ind < eArr->currSize)){
      removing++;
      ind++;
    }
    if (!removing && elementSameValueSameStep(*elem,eArr->arr[ind])){
      eArr->arr[ind].reps+= elem->reps;
      return -1;
    }
    eArr->currSize -= removing==1 ? 1 : 0;
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
  int oldInd;
  ind++;
  while ((oldInd = ind+jump)<(eArr->currSize)){
    eArr->arr[ind]=eArr->arr[oldInd];
    ind++;
  }
  eArr->currSize-=(jump+1);
}

void addToElementArray(elementArray* eArr, element elem, int ind){
  eArr->arr[ind] = elem;
  eArr->currSize++;
}

long int numberOfMaxSizeSubseq(elementArray* eArr, int max){
  int ind = eArr->currSize-1;
  if (ind==-1) { return 0; }
  long int out=0;
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
  char* check;
  char finishedReading = 0;
  char buffer[BUFFER_SIZE];
  char** prev = (char**) malloc(sizeof(char*));
  *prev = NULL;
  int prevSize=0;
  while (!finishedReading){
    buffer[BUFFER_SIZE-2]='\0';
    check=fgets(buffer,BUFFER_SIZE,stdin);
    if (check==NULL) { break; }
    if (buffer[BUFFER_SIZE-2]=='\0'){
      finishedReading = 1;
    }
    parseInput(vet,buffer,prev,&prevSize);
  }
  return vet;
}

int getCutNumber(char** prev, int* prevSize, char* buffer, short* ind){
  int prevInd;
  int availableSize;
  char c;
  prevInd = strlen(*prev);
  availableSize = *prevSize-prevInd-1;
  while ((c=buffer[*ind])!=' ' && c!='\n' && c!='\0'){
    if (availableSize <= 0){
      availableSize = *prevSize-1;
      (*prevSize)*=2;
      *prev = (char*) realloc(*prev,(*prevSize)*sizeof(char));
    }
    availableSize--;
    *(*(prev)+prevInd)=c;
    prevInd++;
    (*ind)++;
  }
  *(*(prev)+prevInd)='\0';
  return atoi(*prev);
}

int possibleCutNumber(char** prev, int* prevSize, char* buffer){
  short ind2;
  char c;
  ind2 = BUFFER_SIZE-3; 
  while ((c=buffer[ind2])!=' ' && c!='\0'){
    ind2--;
  }
  *prevSize = (BUFFER_SIZE-ind2-2)*2; 
  *prev = (char*) malloc((*prevSize)*sizeof(char));
  strcpy(*prev,&buffer[++(ind2)]);
  return ind2;
}

void parseInput(vetor* vet, char* buffer, char** prev, int* prevSize){
  char c;
  char read = 0;
  short ind = 0;
  int i;
  int stop = BUFFER_SIZE;
  if (*prev!=NULL){
    i = getCutNumber(prev,prevSize,buffer,&ind);
    addToVetor(vet,i);
    free(*prev);
    *prev=NULL;
  }
  if ((c=buffer[BUFFER_SIZE-2])!=' ' && c!='\0'){
    stop = possibleCutNumber(prev,prevSize,buffer); 
  }
  while (ind<stop && (c=buffer[ind])!='\0' && c!='\n'){
    if (c!=' ' && !read){
      i = atoi(&buffer[ind]);
      addToVetor(vet,i);
      read=1;
    }
    if (c==' ') {read = 0;}
    ind++;
  }
}

short runExercise1(){
  vetor* vet = getVetorFromInput();
  if (vet==NULL){
    return -1;
  }
  exercise1(vet);
  return 0;

}

void checkOCone(vetor* vet,int size){
  int i;
  for (i=0;i<size;i++){
    if ((size-i)!=(vet->arr[i])){
    }
  }
}

void printReps(elementArray* eArr){ 
  int i, size = eArr->currSize;
  for (i=0;i<size;i++){
    printf("%d(s-%ld,r-%ld),",eArr->arr[i].value,eArr->arr[i].step,eArr->arr[i].reps);
  } printf("\n");
}

void exercise1(vetor* vet){
  int size = vet->currSize;
  long int max=0,hMany;
  int ind;
  elementArray* elementArr = initElementArray(size);
  for (ind=0;ind<size;ind++){
    handleAddToElementArray(elementArr,getVetorValue(vet,ind));
    /*printElementArray(elementArr);*/
  }
  max = getElementArrayMaxValue(elementArr);
  hMany = numberOfMaxSizeSubseq(elementArr,max);
  printf("%ld %ld\n",max,hMany);
}

/**/

int main(){
  short check;
  int exercise;
  check=scanf("%d\n",&exercise);
  if (check!=1){
    return -1;
  }
  if (exercise==1){
    if(runExercise1()==-1){
      return -1;
    }
  } else {
    vetor* vet = NULL;
    printf("%d\n",vet->arr[100]);
  }
  return 0;
}
