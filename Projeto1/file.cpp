#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unordered_map>

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
  long int special; /*reps -> P1, ind -> P2*/
  long int step;
} element;

typedef struct {
  element* arr;
  long int currSize;
  long int size;
} elementArray;

class myList {
  public:
    int value;
    myList* next;

    myList(int val){
      value = val;
      next = NULL;
    }

    myList* deleteL(myList* prev){
      prev->next = this->next;
      free(this);
      return prev->next;
    }
};

class myListHead {
  public:
    myList* first;
    myList* last;

    myListHead(int value){
      first = new myList(value);
      last = first;
    }

    myListHead(){
      first = NULL; last = NULL;
    }

    void addToList(int val){
      if (first == NULL){
        first = new myList(val);
        last = first;
      } else {
        last->next = new myList(val);
        last = last->next;
      }
    }

    int pop(char* errorHandler){
      *errorHandler = 0;
      if (first!=NULL){
        int out =  first->value;
        first = first->next;
        return out;
      } else {
        *errorHandler = 1;
        return 0;
      }
    }

    void print(){
      myList* nextL = first;
      while (nextL!=NULL){
        printf("%d->",nextL->value);
        nextL = nextL->next;
      } printf("\n");
    }
};

typedef struct {
  vetor* vet;
  myListHead* mLH;
  unordered_map<int,char>* mp;
} Global;


/*.h stuff*/

element initNullElement();

elementArray* initElementArray(int size);

int elementComparator(element e1, element e2);

int elementBinarySearch(elementArray* array, int s, int e, element find);

int removeIfNecessary(elementArray* eArr, element elem, int ind);

void shiftRightElementArray(elementArray* eArr,int ind);

void shiftLefElementArray(elementArray* eArr, int ind, int jump);

void handleAddToElementArray(elementArray* eArr, element elem, int ind);

void addToElementArray(elementArray* eArr, element elem, int ind);

int getElementArrayMaxValue(elementArray* eArr);

void setElementReps(elementArray* eArr,int ind, element* elem);

void setElementRepsAndStep(elementArray* eArr, element* elem, int ind);

long int numberOfMaxSizeSubseq(elementArray* eArr, int max);

void printElementArray(elementArray* eArr);

/* Main */

int getCutNumber(char** prev, int* prevSize, char* buffer, short* ind);

int possibleCutNumber(char** prev, int* prevSize, char* buffer);

void parseInput(Global* global, char* buffer, char** prev, int* prevSize, int* prevValue);

void storeUserInput(Global* global);

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



Global* initGlobalEx1(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet = initVetor();
  global->mp = NULL;
  global->mLH = NULL;
  return global;
}

Global* initGlobalEx2Part1(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet = NULL;
  global->mp = new unordered_map<int,char>;
  global->mLH = new myListHead();
  return global;
}

char isExercise1(Global* global){
  return global->mp==NULL;
}

char isExercise2Part1(Global* global){
  return global->vet==NULL;
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
  newVal.special=0;
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
    printf("Value=%d\tReps=%ld\tSteps=%ld\n",eArr->arr[i].value,eArr->arr[i].special,eArr->arr[i].step);
    printf("|\n");
  }
}

elementArray* getFinishedElementArray(vetor* vet){
  int size = vet->currSize;
  int ind,binInd;
  elementArray* elementArr = initElementArray(size);
  for (ind=0;ind<size;ind++){
    element elem = newElementWithValue(getVetorValue(vet,ind));
    binInd = elementBinarySearch(elementArr,0,elementArr->currSize-1,elem);
    setElementRepsAndStep(elementArr,&elem,binInd);
    handleAddToElementArray(elementArr, elem, binInd);
  }
  return elementArr;
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
  printf("Value=%d\tReps=%ld\tSteps=%ld\n",elem.value,elem.special,elem.step);
}

void setElementReps(elementArray* eArr,int ind, element* elem){
  if (!ind){
    elem->special=1;
  } else {
    element indElement = eArr->arr[ind-1];
    while (((indElement.step + 1) == elem->step)){
      elem->special+=indElement.special;
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
      eArr->arr[ind].special+= elem.special;
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
    out += indElement.special;
    ind--;
    if (ind<0){
      break;
    }
    indElement = eArr->arr[ind];
  }
  return out;
}


void storeUserInput(Global* global){
  char* check;
  char buffer[BUFFER_SIZE];
  char finishedReading = 0;
  char** prev = (char**) malloc(sizeof(char*));
  int prevValue=0,prevSize=0;
  *prev = NULL;
  while (!finishedReading){
    buffer[BUFFER_SIZE-2]='\0';
    check=fgets(buffer,BUFFER_SIZE,stdin);
    if (check==NULL) { break; }
    if (buffer[BUFFER_SIZE-2]=='\0'){
      finishedReading = 1;
    }
    parseInput(global,buffer,prev,&prevSize,&prevValue);
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
    addToVetor(global->vet,i);
  } else if (isExercise2Part1(global)){
    global->mLH->addToList(i);
    global->mp->insert({i,0});
  } else {
    if (global->mp->find(i) != global->mp->end()){
      addToVetor(global->vet,i);
      (*(global->mp))[i] = 1;
    }
  }
}

void parseInput(Global* global, char* buffer, char** prev, int* prevSize, int* prevValue){
  char c;
  char read = 0;
  short ind = 0;
  int i;
  int stop = BUFFER_SIZE;
  if (*prev!=NULL){
    i = getCutNumber(prev,prevSize,buffer,&ind);
    if (i!=(*prevValue) || !(global->vet->currSize)){
      *prevValue = i;
      addToVetorByExercise(global,i);
    }
    free(*prev);
    *prev=NULL;
  }
  if ((c=buffer[BUFFER_SIZE-2])!=' ' && c!='\0'){
    stop = possibleCutNumber(prev,prevSize,buffer); 
  }
  while (ind<stop && (c=buffer[ind])!='\0' && c!='\n'){
    if (c!=' ' && !read){
      i = atoi(&buffer[ind]);
      if (i!=(*prevValue) || !(global->vet->currSize)){
        *prevValue = i;
        addToVetorByExercise(global,i);
      }
      read=1;
    }
    if (c==' ') {read = 0;}
    ind++;
  }
}

short runExercise1(){
  Global* global = initGlobalEx1();
  storeUserInput(global);
  exercise1(global->vet);
  return 0;
}


void filterFirstArray(Global* global){
  myList* myCurrList = global->mLH->first;
  while (myCurrList != NULL && !((*(global->mp))[myCurrList->value])){
    myCurrList = myCurrList->next;
    global->mLH->first = myCurrList;
  }
  if (myCurrList != NULL){
    int prevValue = myCurrList->value;
    myList* myPrevList = myCurrList;
    myCurrList = myCurrList->next;
    while (myCurrList!=NULL){
      if ( !((*(global->mp))[myCurrList->value]) || myCurrList->value==prevValue){
        myCurrList = myCurrList->deleteL(myPrevList);
      } else {
        prevValue = myCurrList->value;
        myPrevList = myCurrList;
        myCurrList = myCurrList->next;
      }
    }
  }
}

char runExercise2(){
  Global* global = initGlobalEx2Part1();
  storeUserInput(global);
  global->vet = initVetor();
  storeUserInput(global);
  filterFirstArray(global);
  global->mLH->print();
  //exercise2(global->mLH,global->vet);
  return 0;
}

void printReps(elementArray* eArr){ 
  int i, size = eArr->currSize;
  for (i=0;i<size;i++){
    printf("%d(s-%ld,r-%ld),",eArr->arr[i].value,eArr->arr[i].step,eArr->arr[i].special);
  } printf("\n");
}



void exercise1(vetor* vet){
  long int max=0,hMany;
  elementArray* elementArr = getFinishedElementArray(vet);
  max = getElementArrayMaxValue(elementArr);
  hMany = numberOfMaxSizeSubseq(elementArr,max);
  printf("%ld %ld\n",max,hMany);
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
