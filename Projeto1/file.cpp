#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unordered_map>


#include <vector>
#include <bits/stdc++.h>


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

template<class T>
class myList {
  public:
    T value;
    myList* next;

    myList(T val){
      value = val;
      next = NULL;
    }

    myList* deleteL(myList* prev){
      prev->next = this->next;
      free(this);
      return prev->next;
    }
};

template<class T>
class myListHead {
  public:
    myList<T>* first;
    myList<T>* last;

    myListHead(){
      first = NULL; last = NULL;
    }

    myListHead(T value){
      first = new myList<T>(value);
      last = first;
    }

    void pushBack(T val){
      if (first == NULL){
        first = new myList<T>(val);
        last = first;
      } else {
        last->next = new myList<T>(val);
        last = last->next;
      }
    }

    void insertWithOrder(T val){
      myList<T>* newL = new myList<T>(val);
      myList<T>* curr = first;
      myList<T>* prev = first;
      if (first==NULL){
        first = newL;
      } else {
        curr = curr->next;
        while (curr!=NULL){
          if ((curr->value - val) > 0){
            break;
          }
          prev = curr;
          curr = curr->next;
        }
        prev->next = newL;
        newL->next = curr;
      }
    }
    


    T pop(char* errorHandler){
      *errorHandler = 0;
      if (first!=NULL){
        T out =  first->value;
        first = first->next;
        return out;
      } else {
        *errorHandler = 1;
        return 0;
      }
    }

    void print(){
      myList<T>* nextL = first;
      while (nextL!=NULL){
        printf("%d->",nextL->value);
        nextL = nextL->next;
      } printf("\n");
    }
};

typedef struct {
  vetor* vet1;
  vetor* vet2;
  unordered_map<int,char>* mp;
  unordered_map<int, myListHead<int>* >* vetorMap;
} Global;


/*.h stuff*/

element initNullElement();

elementArray* initElementArray(int size);

int elementComparator(element e1, element e2);

int elementBinarySearch(elementArray* array, int s, int e, element find);

int removeIfNecessary(elementArray* eArr, element elem, int ind, char exercise);

void shiftRightElementArray(elementArray* eArr,int ind);

void shiftLefElementArray(elementArray* eArr, int ind, int jump);

void handleAddToElementArray(elementArray* eArr, element elem, int ind, char exercise);

void addToElementArray(elementArray* eArr, element elem, int ind);

int getElementArrayMaxValue(elementArray* eArr);

void setElementReps(elementArray* eArr,int ind, element* elem);

void setElementRepsAndStep(elementArray* eArr, element* elem, int ind);

long int numberOfMaxSizeSubseq(elementArray* eArr, int max);

void printElementArray(elementArray* eArr);

int getIndWithSameValue(vetor* vet, int value, int start);

/* Main */

int getCutNumber(char** prev, int* prevSize, char* buffer, short* ind);

int possibleCutNumber(char** prev, int* prevSize, char* buffer);

void parseInput(Global* global, char* buffer, char** prev, int* prevSize, int* prevValue);

void storeUserInput(Global* global);

short runExercise1();

void exercise1(vetor* vet);


void printMap(unordered_map<int, myListHead<int>* > *bom){
  vector<int> keys;
  int mapSize = bom->size();
  int ind,key;
  keys.reserve(mapSize);
  for(auto kv : *bom) {
    keys.push_back(kv.first);
  }
  sort(keys.begin(), keys.end(), greater<int>());
  for (ind=0;ind<mapSize;ind++){
    key = keys[ind];
    printf("%d: ",key);
    (*bom)[key]->print();
  }
}

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
  global->vet1 = initVetor();
  global->vet2 = NULL;
  global->vetorMap = NULL;
  global->mp = NULL;
  return global;
}

Global* initGlobalEx2Part1(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet1 = NULL;
  global->vet2 = initVetor();
  global->mp = new unordered_map<int,char>;
  global->vetorMap = NULL;
  return global;
}

char isExercise1(Global* global){
  return global->mp==NULL;
}

char isExercise2Part1(Global* global){
  return global->vet1==NULL;
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

elementArray* getFinishedElementArray(vetor* vet,int eArrSize){
  int ind,binInd;
  elementArray* elementArr = initElementArray(eArrSize);
  for (ind=0;ind<eArrSize;ind++){
    element elem = newElementWithValue(getVetorValue(vet,ind));
    binInd = elementBinarySearch(elementArr,0,elementArr->currSize-1,elem);
    setElementRepsAndStep(elementArr,&elem,binInd);
    handleAddToElementArray(elementArr, elem, binInd,1);
  }
  return elementArr;
}

void handleAddToElementArray(elementArray* eArr, element elem, int ind, char exercise){
  int removed = removeIfNecessary(eArr,elem,ind, exercise);
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

int isValidElement(elementArray* eArr, element* elem, int vetInd, char* success){
  int binInd,auxInd,baseStep;
  binInd = elementBinarySearch(eArr,0,eArr->currSize-1,*elem);
  if (!binInd){
    *success = 1;
    elem->step = 0;
  } else {
    *success = 0;
    auxInd = binInd-1;
    baseStep = eArr->arr[auxInd].step;
    while (auxInd>=0 && eArr->arr[auxInd].step==baseStep){
      if (eArr->arr[auxInd].special < vetInd){
        *success=1;
        elem->step = eArr->arr[(binInd-1)].step+1;
        break;
      }
      auxInd--;
    }
  }
  elem->special = vetInd;
  return binInd;
}


elementArray* getFinishedSecondElementArray(myListHead<int>* mLH, vetor* vet, int eArrSize){
  int value,vetInd,binInd;
  char errorHandler,success;
  elementArray* eArr = initElementArray(eArrSize);
  element elem;
  while (mLH->first!=NULL){
    vetInd=-1;
    value = mLH->pop(&errorHandler); /*errorHandler wont be needed*/
    elem = newElementWithValue(value);
    success = 0;
    while (!success){
      vetInd = getIndWithSameValue(vet,value,++vetInd);
      if (vetInd<0) { break; }
      binInd = isValidElement(eArr,&elem,vetInd,&success);

    }
    if (vetInd>=0){
      handleAddToElementArray(eArr,elem,binInd,2);
    }
  }
  return eArr;
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


int removeIfNecessary(elementArray* eArr, element elem, int ind, char exercise){
  int removing=0;
  if (ind != eArr->currSize && eArr->currSize!=0){
    while ( (eArr->arr[ind].step < elem.step) && (ind < eArr->currSize)){
      removing++;
      ind++;
    }
    if (!removing && elementSameValueSameStep(elem,eArr->arr[ind])){
      eArr->arr[ind].special += exercise==1 ? elem.special : 0;
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

void addToVetorByExercise(Global* global,int i,int* prevValue){
  if (isExercise1(global)){
    addToVetor(global->vet1,i);
  } else if (isExercise2Part1(global)){ 
    if  ((( i!=(*prevValue) || !(global->vet2->currSize) ))){
        addToVetor(global->vet2,i);
        global->mp->insert({i,0});
        *prevValue = i;
      } 
  }
  else if ((global->mp->find(i) != global->mp->end())){
    if (((i!=(*prevValue) || !(global->vet1->currSize)))){
      addToVetor(global->vet1,i);
      (*(global->mp))[i] = 1;
      *prevValue = i;
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
    addToVetorByExercise(global,i,prevValue);
    free(*prev);
    *prev=NULL;
  }
  if ((c=buffer[BUFFER_SIZE-2])!=' ' && c!='\0'){
    stop = possibleCutNumber(prev,prevSize,buffer); 
  }
  while (ind<stop && (c=buffer[ind])!='\0' && c!='\n'){
    if (c!=' ' && !read){
      i = atoi(&buffer[ind]);
      addToVetorByExercise(global,i,prevValue);
      read=1;
    }
    if (c==' ') {read = 0;}
    ind++;
  }
}

short runExercise1(){
  Global* global = initGlobalEx1();
  storeUserInput(global);
  exercise1(global->vet1);
  return 0;
}


void filterFirstArray(Global* global){
  vetor* vet = global->vet2;
  int size2 = vet->currSize;
  int val,prevValue;
  int ind, insertInd=0;
  char found=0;
  unordered_map<int, myListHead<int>* >* vetMap = new unordered_map<int, myListHead<int>* >;
  for (ind=0;ind<size2;ind++){
    val = getVetorValue(vet,ind);
    if ((*(global->mp))[val] && (!found || prevValue!=val)){
      if (vetMap->find(val) == vetMap->end()){
        (*vetMap)[val] = new myListHead<int>();
      }
      (*vetMap)[val]->pushBack(insertInd);
      prevValue = val;
      found=1;
      insertInd++;
    } 
  }
  freeVetor(vet);
  global->vet2=NULL;
  global->vetorMap = vetMap;
}

int getIndWithSameValue(vetor* vet, int value, int start){
  int size = vet->currSize;
  if (start >= size){
    return -1;
  }
  for (;start<size;start++){
    if (vet->arr[start] == value){
      return start;
    }
  }
  return -2; /*Erro grave*/
}


void exercise2(vetor* vet, unordered_map<int,myListHead<int>* >* vetMap){
  long int max = 0;
  //int size = vetMap->size();
  //elementArray* eArr = getFinishedSecondElementArray(mLH,vet,size);
  //max = getElementArrayMaxValue(eArr);
  printf("%ld\n",max);
}



char runExercise2(){
  Global* global = initGlobalEx2Part1();
  storeUserInput(global);
  printf("Vetor1-Beta:\n");
  printVetor(global->vet2);
  global->vet1 = initVetor();
  storeUserInput(global);
  filterFirstArray(global);
  printf("\nVetor2:\n");
  printVetor(global->vet1);
  printf("Vetor1:\n");
  printMap(global->vetorMap);
  //exercise2(global->vet1,global->vetorMap);
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
  elementArray* elementArr = getFinishedElementArray(vet,vet->currSize);
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
