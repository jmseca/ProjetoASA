#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

#define VETOR_BASE_SIZE 50
#define BUFFER_SIZE 128
#define MAP_BASE_SIZE 50

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

typedef struct {
  vetor* vet1;
  vetor* vet2;
  map<int,char> *mp;
} Global;



/*.h stuff*/

element initNullElement();

elementArray* initElementArray(int size);

int elementComparator(element e1, element e2);

int elementBinarySearch(elementArray* array, int s, int e, element find);

int removeIfNecessary(elementArray* eArr, element elem, int ind);

void shiftRightElementArray(elementArray* eArr,int ind);

void shiftLefElementArray(elementArray* eArr, int ind, int jump);

void handleAddToElementArray(elementArray* eArr, int value);

void addToElementArray(elementArray* eArr, element elem, int ind);

int getElementArrayMaxValue(elementArray* eArr);

void setElementReps(elementArray* eArr,int ind, element* elem);

void setElementRepsAndStep(elementArray* eArr, element* elem, int ind);

long int numberOfMaxSizeSubseq(elementArray* eArr, int max);

void printElementArray(elementArray* eArr);

/* Main */

int getCutNumber(char** prev, int* prevSize, char* buffer, short* ind);

int possibleCutNumber(char** prev, int* prevSize, char* buffer);

void parseInput(Global* global, char* buffer, char** prev, int* prevSize);

void getVetorFromInput(Global* global, char exercise);

char runExercise1();

void exercise1(vetor* vet);

void exercise2(vetor* vet1, vetor* vet2);

/* VETOR */

vetor* initVetor(){
   vetor *vet = (vetor*) malloc(sizeof(vetor));
   vet->arr = (int*) malloc(sizeof(int)*VETOR_BASE_SIZE);
   vet->size = VETOR_BASE_SIZE;
   vet->currSize = 0;
   return vet;
}

void addToVetor(vetor *vet,int newVal){
   if (vet->size == vet->currSize){
      vet->size*=2;
      vet->arr = (int*) realloc(vet->arr,sizeof(int)*(vet->size));
   }
  vet->arr[vet->currSize] = newVal;
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
  element newVal;
  newVal.value = 0;
  return newVal;
}

element newElementWithValue(int val){
  element newVal;
  newVal.value = val;
  newVal.step=0;
  newVal.reps=0;
  return newVal;
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


/*Global stuff*/
Global* initGlobalEx1(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet1 = initVetor();
  global->vet2 = NULL;
  global->mp = NULL;
  return global;
}

Global* initGlobalEx2(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet1 = initVetor();
  global->vet2 = NULL;
  global->mp = new map<int,char>;
  return global;
}

Global* initGlobalVetor2(Global* global){
  global->vet2 = initVetor();
  return global;
}


char isExercise1(Global* global){
  return global->mp == NULL;
}

char isExercise2Part1(Global* global){
  return global->vet2 == NULL;
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


void handleAddToElementArray(elementArray* eArr, element elem, int ind){
  int removed = removeIfNecessary(eArr,elem,ind);
  if (removed!=-1){
    if (!removed){
      shiftRightElementArray(eArr,ind);
    }
    addToElementArray(eArr,elem,ind);
    if (removed>1){
      shiftLefElementArray(eArr,ind,removed-1);
    }
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

void setElementRepsAndStep(elementArray* eArr, element* elem, int ind){
  elem->step = !ind ? 0 : eArr->arr[ind-1].step +1; 
  setElementReps(eArr,ind,elem);
}


int removeIfNecessary(elementArray* eArr, element elem, int ind){
  int removing=0;
  if (ind != eArr->currSize && eArr->currSize!=0){
    while ( (eArr->arr[ind].step < elem.step) && (ind < eArr->currSize)){
      removing++;
      ind++;
    }
    if (!removing && elementSameValueSameStep(elem,eArr->arr[ind])){
      eArr->arr[ind].reps+= elem.reps;
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


void getVetorFromInput(Global* global,char exercise){
  char* check;
  char buffer[BUFFER_SIZE];
  char finishedReading = 0;
  char** prev = (char**) malloc(sizeof(char*));
  int prevSize=0;
  *prev = NULL;
  while (!finishedReading){
    buffer[BUFFER_SIZE-2]='\0';
    check=fgets(buffer,BUFFER_SIZE,stdin);
    if (check==NULL) { break; }
    if (buffer[BUFFER_SIZE-2]=='\0'){
      finishedReading = 1;
    }
    parseInput(global,buffer,prev,&prevSize);
  }
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

void addToVetorByExercise(Global* global,int i){
  if (isExercise1(global)){
    addToVetor(global->vet1,i);
  } else if (isExercise2Part1(global)){
    addToVetor(global->vet1,i);
    global->mp->insert({i,0});
  } else {
    if (global->mp->find(i) != global->mp->end()){
      addToVetor(global->vet2,i);
    }
  }
}


void parseInput(Global* global, char* buffer, char** prev, int* prevSize){
  char c;
  char read = 0;
  short ind = 0;
  int i;
  int stop = BUFFER_SIZE;
  if (*prev!=NULL){
    i = getCutNumber(prev,prevSize,buffer,&ind);
    addToVetorByExercise(global,i);
    free(*prev);
    *prev=NULL;
  }
  if ((c=buffer[BUFFER_SIZE-2])!=' ' && c!='\0'){
    stop = possibleCutNumber(prev,prevSize,buffer); 
  }
  while (ind<stop && (c=buffer[ind])!='\0' && c!='\n'){
    if (c!=' ' && !read){
      i = atoi(&buffer[ind]);
      addToVetorByExercise(global,i);
      read=1;
    }
    if (c==' ') {read = 0;}
    ind++;
  }
}

char runExercise1(){
  Global* global = initGlobalEx1();
  getVetorFromInput(global,1);

  exercise1(global->vet1);
  return 0;
}

char runExercise2(){
  Global* global = initGlobalEx2();
  getVetorFromInput(global,2);
  global->vet2 = initVetor();
  getVetorFromInput(global,2);

  exercise2(global->vet1,global->vet2);
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

elementArray* getFinishedElementArray(vetor* vet){
  int size = vet->currSize;
  int ind,binInd;
  elementArray* elementArr = initElementArray(size);
  for (ind=0;ind<size;ind++){
    element elem = newElementWithValue(getVetorValue(vet,ind));
    binInd = elementBinarySearch(elementArr,0,elementArr->currSize-1,elem);
    setElementRepsAndStep(elementArr,&elem,ind);
    handleAddToElementArray(elementArr, elem, binInd);
  }
  return elementArr;
}

elementArray* getFinishedSecondElementArray(elementArray* eArr2 ,vetor* vet1){
  int size1 = vet1->currSize;
  int ind,binInd,binInd2;
  elementArray* eArr1 = initElementArray(size1);
  for (ind=0;ind<size1;ind++){
    element elem = newElementWithValue(getVetorValue(vet1,ind));
    binInd = elementBinarySearch(eArr1,0,eArr1->currSize-1,elem);
    setElementRepsAndStep(eArr1,&elem,binInd);
    binInd2 = elementBinarySearch(eArr2,0,eArr2->currSize-1,elem);
    if (elementSameValueSameStep(eArr2->arr[binInd2],elem)){
      handleAddToElementArray(eArr1, elem, binInd);
    } 
  }
  return eArr1;
  
}

void exercise1(vetor* vet){
  long int max=0,hMany;
  elementArray* elementArr = getFinishedElementArray(vet);
  max = getElementArrayMaxValue(elementArr);
  hMany = numberOfMaxSizeSubseq(elementArr,max);
  printf("%ld %ld\n",max,hMany);
}

void exercise2(vetor* vet1, vetor* vet2){
  long int maxSize;
  vetor* vetAux;
  elementArray *eArr1,*eArr2;
  if (vet2->currSize > vet1->currSize){
    vetAux = vet2;
    vet2 = vet1;
    vet1 = vetAux;
  }
  eArr2 = getFinishedElementArray(vet2);
  eArr1 = getFinishedSecondElementArray(eArr2,vet1);
  maxSize = getElementArrayMaxValue(eArr1);
  printf("%ld\n",maxSize);
}


int main(){
  short check;
  int exercise;
  do {
    check=scanf("%d\n",&exercise);
    if (check!=1){
      return -1;
    }
  } while (exercise!=1 && exercise!=2);
  if (exercise==1){
    if(runExercise1()==-1){
      return -1;
    }
  } else {
    if( runExercise2()==-1 ){
      return -1;
    }
  }
  return 0;
}
