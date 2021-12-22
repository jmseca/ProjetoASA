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

/*
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

int numberOfMaxSizeSubseq(elementArray* eArr, int max){
  int ind = eArr->currSize-1;
  int rep = 0;
  element elem = eArr->arr[ind];
  while ( elem.step == (max-1)){
    rep += elem.reps;
    ind--;
    elem = eArr->arr[ind];
  }
  return rep;
}
*/


int binarySearch(int* array, int s, int e, int find) {
  int m,comp;
  if ( (e==-1) || find > array[e]){
    return e+1;
  }
  m = (s + e)/2;
  comp = array[m]-find;
  if (!comp)
    return m;
  else if (comp<0)  
    return binarySearch(array, m+1, e, find);
  else
    return binarySearch(array, s, m-1, find);
}


int main(){

  int arr[] = {3,4};
  int find = 1;

  printf("%d\n",binarySearch(arr,0,1,1));


  return 0;
}