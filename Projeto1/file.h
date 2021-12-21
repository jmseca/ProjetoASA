#ifndef __file_h__
#define __file_h__

typedef struct {
   int size;
   int currSize;
   int* arr;
} vetor;

typedef struct {
  int value;
  short reps;
  short step;
} element;

vetor* initVetor();

void addToVetor(vetor* vet,int new);

vetor* changeVetorValue(int ind, int newVal);

void printVetor(vetor* vet);

void freeVetor(vetor *vet);

int* zeroArray(int size);

// Element

typedef struct {
  int value;
  short reps;
  short step;
} element;

typedef struct {
  element* arr;
  int currSize;
} elementArray;

element initNullElement();

elementArray* initElementArray(int size);

int elementComparator(element e1, element e2);

int elementBinarySearch(elementArray* array, int s, int e, element find);

char removeIfNecessary(elementArray* eArr, element* elem, int ind);

void shiftRightElementArray(elementArray* eArr,int ind);

void handleAddToElementArray(elementArray* eArr, int value);

void addToElementArray(elementArray* eArr, element elem, int ind);

int getElementArrayMaxValue(elementArray* eArr);

//Main

void parseInput(vetor* vet, char* buffer);

vetor* getVetorFromInput();






#endif