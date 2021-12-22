#ifndef __file_h__
#define __file_h__

typedef struct {
   int size;
   int currSize;
   int* arr;
} vetor;

vetor* initVetor();

void addToVetor(vetor* vet,int new);

vetor* changeVetorValue(int ind, int newVal);

void printVetor(vetor* vet);

void freeVetor(vetor *vet);

int* zeroArray(int size);

// Element

typedef struct {
  int value;
  int reps;
  int step;
} element;

typedef struct {
  element* arr;
  int currSize;
  int size;
} elementArray;

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

int numberOfMaxSizeSubseq(elementArray* eArr, int max);

void printElementArray(elementArray* eArr);

//Main

int getCutNumber(char** prev, int* prevSize, char* buffer, short* ind);

int possibleCutNumber(char** prev, int* prevSize, char* buffer);

void parseInput(vetor* vet, char* buffer, char** prev, int* prevSize);

vetor* getVetorFromInput();

void runExercise1();

void exercise1(vetor* vet);






#endif