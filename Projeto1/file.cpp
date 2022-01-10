#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unordered_map>

using namespace std;

#define VETOR_BASE_SIZE 50
#define BUFFER_SIZE 128

// CLASSES ============================

/**
 * myVetor: vetor de inteiros
 *  - arr: array com os inteiros
 *  - size: tamanho disponival na array
 *  - currSize: espaco ocupado na array
 */
class myVetor {
  public:
    long int size;
    long int currSize;
    int* arr;

  myVetor(){
    this->arr = (int*) malloc(sizeof(int)*VETOR_BASE_SIZE);
    this->size = VETOR_BASE_SIZE;
    this->currSize = 0;
  }

  int get(int pos){
    return this->arr[pos];
  }

  void add(int newVal){
   if (this->size == this->currSize){
      this->size*=2;
      this->arr = (int*) realloc(this->arr,sizeof(int)*(this->size));
   }
  this->arr[this->currSize] = newVal;
  this->currSize++;
  }

  void freeArr(){
    free(this->arr);
  }
};


class element {
  public:
    int value;
    long int special; /*Y -> P1, indices -> P2*/
    int step; /*X -> P1, Z -> P2*/

    element(int val){
      value = val;
      step = 0;
      special = 0;
    }

    element(){
      element(0);
    }

    element(int val, int stp, int spcl){
      value = val;
      step = stp;
      special = spcl;
    }

    char deletes(element e2){
      if(this->step >= e2.step){
        return (e2.step + (this->special - e2.special -1)) <= this->step;
      } else {
        return 0;
      }
    }

    void print(){
      printf("{val->%d, step->%d, special->%ld}\n",value,step,special);
    }
};

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
    
};


// STRUCTS ============================

typedef struct {
  element* arr;
  long int currSize;
  long int size;
} elementArray;


typedef struct {
  myVetor* vet1;
  myVetor* vet2;
  unordered_map<int,char>* mp;
  unordered_map<int, myListHead<int>* >* vetorMap;
} Global;

// needed
void parseInput(Global* global, char* buffer, char** prev, int* prevSize, int* prevValue);

Global* initGlobalEx1(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet1 = new myVetor();
  global->vet2 = NULL;
  global->vetorMap = NULL;
  global->mp = NULL;
  return global;
}

Global* initGlobalEx2Part1(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet1 = NULL;
  global->vet2 = new myVetor();
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


/* Defines Y for given element*/
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

void setElementRepsAndStep(elementArray* eArr, element* elem, int ind){
  elem->step = !ind ? 0 : eArr->arr[ind-1].step +1; 
  setElementReps(eArr,ind,elem);
}

elementArray* getFinishedElementArray(myVetor* vet,int eArrSize){
  int ind,binInd;
  elementArray* elementArr = initElementArray(eArrSize);
  for (ind=0;ind<eArrSize;ind++){
    element elem = element( vet->get(ind) );
    binInd = elementBinarySearch(elementArr,0,elementArr->currSize-1,elem);
    setElementRepsAndStep(elementArr,&elem,binInd);
    handleAddToElementArray(elementArr, elem, binInd,1);
  }
  return elementArr;
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

/*responsible for joining a number, cut in half by fgets*/
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

/*fgets may cut a number in half, checks if it has happened*/
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
    global->vet1->add(i);
  } else if (isExercise2Part1(global)){ 
    if  ((( i!=(*prevValue) || !(global->vet2->currSize) ))){
        global->vet2->add(i);
        global->mp->insert({i,0});
        *prevValue = i;
      } 
  }
  else if ((global->mp->find(i) != global->mp->end())){
    if (((i!=(*prevValue) || !(global->vet1->currSize)))){
      global->vet1->add(i);
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

void exercise1(myVetor* vet){
  long int max=0,hMany;
  elementArray* elementArr = getFinishedElementArray(vet,vet->currSize);
  max = getElementArrayMaxValue(elementArr);
  hMany = numberOfMaxSizeSubseq(elementArr,max);
  printf("%ld %ld\n",max,hMany);
}

short runExercise1(){
  Global* global = initGlobalEx1();
  storeUserInput(global);
  exercise1(global->vet1);
  return 0;
}

/*Filters V1 and transforms it into a Hash Table*/
void filterFirstArray(Global* global){
  myVetor* vet = global->vet2;
  int size2 = vet->currSize;
  int val,prevValue;
  int ind, insertInd=0;
  char found=0;
  unordered_map<int, myListHead<int>* >* vetMap = new unordered_map<int, myListHead<int>* >;
  for (ind=0;ind<size2;ind++){
    val = vet->get(ind);
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
  vet->freeArr();
  free(vet);
  global->vet2=NULL;
  global->vetorMap = vetMap;
}


void firstSearchUpdate(myList<element>* currElem, myList<element>* prevElem,
int* bestStep, int* elemStep, element elem)
{
  int currStep = currElem->value.step;
  int currInd = currElem->value.special;
  if ((*bestStep)<=currStep){
    *bestStep = currStep+1;
  }
  if ((currStep>=(*elemStep)) && (currInd<elem.special)){
    *elemStep = currStep+1;
  }
}

void deleteElements(myList<element>* currElem){
  element elem = currElem->value;
  myList<element>* aux;
  while ( ((currElem->next)!=NULL) && (elem.deletes(currElem->next->value))){
    aux = currElem->next;
    currElem->next = aux ->next;
    free(aux);
  }
}

int checkInsertInElemList(myListHead<element>* myElist, myList<element>* prevElem,
element elem, int elemStep, int* bestStep, char* done, char control)
{
  *done = elemStep==(*bestStep);
  elem.step = elemStep;
  myList<element>* newL = new myList<element>(elem);
  if (!control){
    if (prevElem==NULL){
      myElist->first = newL;
      newL->next = NULL;
    } else {
      newL->next = prevElem;
      myElist->first = newL;
    }
  } else if (!((prevElem->value).deletes(elem))){
    newL->next = prevElem->next;
    prevElem->next = newL;
    deleteElements(newL);
    return elem.step;
  } else {
    free(newL);
  }
  return 0;
}

int checkSubstitutionInElemList(myList<element>* currElem, int elemStep,
int* bestStep, char* done)
{
  *done = (*bestStep) == elemStep;
  if (currElem->value.step < elemStep){
    currElem->value.step = elemStep;
    deleteElements(currElem);
    return elemStep;
  }
  return 0;
}

int firstSearchInElemList(myListHead<element>* myElemList, element elem, char* done,
int* bestStep)
{
  char control=0;
  int currInd,currValue,elemStep = 0;
  myList<element>* prevElem = myElemList->first;
  myList<element>* currElem = myElemList->first;
  while (currElem!=NULL){
    currValue=currElem->value.value;
    if (currValue < elem.value){
      firstSearchUpdate(currElem,prevElem,bestStep,&elemStep,elem);
      prevElem = currElem; currElem = currElem->next;
      control = 1;
    } else if (currValue > elem.value) { break; }
    else {
      currInd = currElem->value.special;
      if (currInd < elem.special){
        prevElem = currElem; currElem = currElem->next; control=1;
      } else if (currInd > elem.special) { break; }
      else {
        return checkSubstitutionInElemList(currElem,elemStep,bestStep,done);
      }
    }
  }
  return checkInsertInElemList(myElemList,prevElem,elem,elemStep,bestStep,done,control);
}

int handleInsertInElemList(myListHead<element>* myElemList, int val, myList<int>* valInds){
  int bestStep=0;
  int maxStep=-1,auxStep=-1;
  char done=0;
  while (!done && valInds!=NULL){
    element elem = element(val,-1,valInds->value);
    auxStep=firstSearchInElemList(myElemList,elem,&done,&bestStep);
    maxStep = auxStep>maxStep ? auxStep : maxStep;
    valInds = valInds->next;
  }
  return maxStep;
}


void exercise2(myVetor* vet, unordered_map<int,myListHead<int>* >* vetMap){
  int maxAux=-1,max = 0;
  int i, val, size = vet->currSize;
  myListHead<element>* myElemList = new myListHead<element>();
  myList<int>* valInds;
  for (i=0;i<size;i++){
    val = vet->get(i);
    valInds = (*vetMap)[val]->first;
    maxAux = handleInsertInElemList(myElemList,val,valInds);
    max = max<maxAux ? maxAux : max;
  }
  printf("%d\n",++max);
}



char runExercise2(){
  Global* global = initGlobalEx2Part1();
  storeUserInput(global);
  global->vet1 = new myVetor();
  storeUserInput(global);
  filterFirstArray(global);
  exercise2(global->vet1,global->vetorMap);
  return 0;
}


// MAIN ===============================
int main(){
  clock_t initClock = clock();
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
  clock_t timeClock = clock() - initClock;
  printf("%ld\n",timeClock);
  return 0;
}
