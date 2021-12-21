#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
  int value;
  short reps;
  short step;
} element;

typedef struct {
  element* arr;
  int currSize;
} elementArray;

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

element* initElementArray(int size){
  element* newArr = (element*) malloc(sizeof(element)*size);
  int i;
  for (i=0; i<size;i++){
    newArr[i] = initNullElement();
  }
  return newArr;
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
  }
  addToElementArray(eArr,elem,ind);

}

char removeIfNecessary(elementArray* eArr, element* elem, int ind){
  element indElement = eArr->arr[ind];
  char removing=0;
  if (!ind){
    return 0;
  }
  elem->step = eArr->arr[ind-1].step; 
  
  if (indElement.value==elem->value &&
  indElement.step == elem->step){
    elem->reps = indElement.reps +1;
    removing=1;
  }
  if (removing && indElement.step < elem->step){ // will remove
    eArr->currSize--;
    return 1;
  } else {
    return 0;
  }
}

void shiftRightElementArray(elementArray* eArr,int ind){
  int size = eArr->currSize;
  while (size>ind){
    eArr->arr[size] = eArr->arr[size-1];
  }
}

void addToElementArray(elementArray* eArr, element elem, int ind){
  eArr->arr[ind] = elem;
  eArr->currSize++;
}

int numberOfMaxSizeSubseq(elementArray* eArr, int max){
  int ind = eArr->currSize-1;
  int rep = 0;
  element elem = eArr->arr[ind];
  while ( elem.step == (max-1)){
    rep += elem.reps;
    ind--;
    elem = eArr->arr[ind];
  }

}

