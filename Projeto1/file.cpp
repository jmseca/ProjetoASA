#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unordered_map>

using namespace std;

#define VETOR_BASE_SIZE 50
#define BUFFER_SIZE 128

// CLASSES ============================

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

    char sameValueSameStep(element e2){
      return (this->step == e2.step) && (this->value == e2.value);
    }

    int elementComparator(element e2){
      int out = e2.value - this->value;
      return !out ? 1 : out;
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

// Global: Stores data structures that will receive input data
typedef struct {
  myVetor* vet1;
  myVetor* vet2;
  unordered_map<int,char>* mp;
  unordered_map<int, myListHead<int>* >* vetorMap;
} Global;

// needed
void parseInput(Global* global, char* buffer, char** prev, int* prevSize, int* prevValue);

/**
 * @brief Inits Global struct for exercise1
 * 
 * @return pointer to Global created 
 */
Global* initGlobalEx1(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet1 = new myVetor();
  global->vet2 = NULL;
  global->vetorMap = NULL;
  global->mp = NULL;
  return global;
}

/**
 * @brief Inits Global struct for exercise2
 * 
 * @return Global* 
 */
Global* initGlobalEx2Part1(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet1 = NULL;
  global->vet2 = new myVetor();
  global->mp = new unordered_map<int,char>;
  global->vetorMap = NULL;
  return global;
}

/**
 * @brief Checks if 'global' is for exercise1
 * 
 * @param global 
 * @return 1 -> true, 0 -> false 
 */
char isExercise1(Global* global){
  return global->mp==NULL;
}

/**
 * @brief Checks if 'global' is for exercise2
 * 
 * @param global 
 * @return 1 -> true, 0 -> false 
 */
char isExercise2Part1(Global* global){
  return global->vet1==NULL;
}

/**
 * @brief Inits an elementArray
 * 
 * @param siz 
 * @return pointer to elementArray created
 */
elementArray* initElementArray(int siz){
  elementArray* eArr = (elementArray*) malloc(sizeof(elementArray));
  element* newArr = (element*) malloc(sizeof(element)*siz);
  eArr->arr = newArr;
  eArr->currSize=0;
  eArr->size = siz;
  return eArr;
} 

/**
 * @brief Returns the final X value in exercise 1
 * 
 * @param eArr 
 */
int getElementArrayMaxStep(elementArray* eArr){
  int size = eArr->currSize;
  return !size ? 0: eArr->arr[(size-1)].step +1;
}

/**
 * @brief binary search of element in an elementArray
 * 
 * @param array
 * @param s start limit of the search
 * @param e end limit of the search
 * @param find 
 * @return Index where 'find' should be at
 */
int elementBinarySearch(elementArray* array, int s, int e, element find) {
  int m,comp;
  if ( (e==-1) || find.value > array->arr[e].value){
    return e+1;
  }
  m = (s + e)/2;
  comp = find.elementComparator(array->arr[m]);
  if (!comp)
    return m;
  else if (comp<0)  
    return elementBinarySearch(array, m+1, e, find);
  else
    return elementBinarySearch(array, s, m-1, find);
}


/**
 * @brief Defines Y for given element
 * 
 * @param eArr 
 * @param ind 
 * @param elem 
 */
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

/**
 * @brief Checks if there are unuseful elements in the elementArray, starting at index 'ind'
 * 
 * @param eArr 
 * @param elem 
 * @param ind 
 * @return Number of elements that need to be removed
 */
int removeIfNecessary(elementArray* eArr, element elem, int ind){
  int removing=0;
  if (ind != eArr->currSize && eArr->currSize!=0){
    while ( (eArr->arr[ind].step < elem.step) && (ind < eArr->currSize)){
      removing++;
      ind++;
    }
    if (!removing && elem.sameValueSameStep(eArr->arr[ind])){
      eArr->arr[ind].special += elem.special;
      return -1;
    }
    eArr->currSize -= removing==1 ? 1 : 0;
    return removing;
  } else {
    return 1;
  }
}

/**
 * @brief Shifts all the elements in the elementArray 1 position
 * to the right, starting on index 'ind'
 * 
 * @param eArr 
 * @param ind 
 */
void shiftRightElementArray(elementArray* eArr,int ind){
  int size = eArr->currSize;
  while (size>ind){
    eArr->arr[size] = eArr->arr[size-1];
    size--;
  }
}

/**
 * @brief Shifts all the elements in the elementArray 'jump' position
 * to the right, starting on index 'ind'
 * 
 * @param eArr 
 * @param ind 
 * @param jump 
 */
void shiftLefElementArray(elementArray* eArr, int ind, int jump){
  int oldInd;
  ind++;
  while ((oldInd = ind+jump)<(eArr->currSize)){
    eArr->arr[ind]=eArr->arr[oldInd];
    ind++;
  }
  eArr->currSize-=(jump+1);
}

/**
 * @brief Adds an element to the elementArray at index 'ind'
 * 
 * @param eArr 
 * @param elem 
 * @param ind 
 */
void addToElementArray(elementArray* eArr, element elem, int ind){
  eArr->arr[ind] = elem;
  eArr->currSize++;
}

/**
 * @brief Decides if an element should be added to the elementArray. If added,
 * checks if there are elements to be removed and adjusts the elementArray. 
 * 
 * @param eArr 
 * @param elem 
 * @param ind 
 */
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

/**
 * @brief Sets the element Reps (Y) and Step (X), considering the values 
 * with index < 'ind'
 * 
 * @param eArr 
 * @param elem 
 * @param ind index where element can be placed
 */
void setElementRepsAndStep(elementArray* eArr, element* elem, int ind){
  elem->step = !ind ? 0 : eArr->arr[ind-1].step +1; 
  setElementReps(eArr,ind,elem);
}

/**
 * @brief Iterates through 'vet' and returns the final elementArray
 * 
 * @param vet Sequence received from input (Exercise1)
 * @param eArrSize 
 * @return elementArray* 
 */
elementArray* getFinishedElementArray(myVetor* vet,int eArrSize){
  int ind,binInd;
  elementArray* elementArr = initElementArray(eArrSize);
  for (ind=0;ind<eArrSize;ind++){
    element elem = element( vet->get(ind) );
    binInd = elementBinarySearch(elementArr,0,elementArr->currSize-1,elem);
    setElementRepsAndStep(elementArr,&elem,binInd);
    handleAddToElementArray(elementArr, elem, binInd);
  }
  return elementArr;
}

/**
 * @brief Returns the number of max size subsequences (Y)
 * 
 * @param eArr elementArray after iterating through Exercise1 subsequence 
 * @param max max size of a subsequence (X)
 * @return long int
 */
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

/**
 * @brief Stores user input in 'global'
 * 
 * @param global 
 */
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

/**
 * @brief fgets may cut a number in half, checks if it has happened
 * 
 * @param prev stores the string of the cut number
 * @param prevSize size of prev string (!= size of number string)
 * @param buffer 
 * @return index where cut number starts in buffer
 */
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

/**
 * @brief Responsible for joining a number, cut in half by fgets
 * 
 * @param prev contains the string of the cut number from last fgets
 * @param prevSize size of prev
 * @param buffer 
 * @param ind 
 * @return the number cut in half
 */
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

/**
 * @brief Adds a new value to the respective vector, depending on
 * which exercise and part too
 * 
 * @param global 
 * @param i new value
 * @param prevValue previously added value
 */
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


/**
 * @brief Parses the input received in 'buffer'
 * 
 * @param global 
 * @param buffer 
 * @param prev contains the string of the cut number from last fgets
 * @param prevSize prev size
 * @param prevValue Last value added to a vector
 */
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

/**
 * @brief Iterates through the Subsequence
 * and finds and prints the wanted values, X and Y
 * 
 * @param vet exercise1 Subsequence
 */
void exercise1(myVetor* vet){
  long int max=0,hMany;
  elementArray* elementArr = getFinishedElementArray(vet,vet->currSize);
  max = getElementArrayMaxStep(elementArr);
  hMany = numberOfMaxSizeSubseq(elementArr,max);
  printf("%ld %ld\n",max,hMany);
}

/**
 * @brief Starts Running Exercise1
 * 
 */
void runExercise1(){
  Global* global = initGlobalEx1();
  storeUserInput(global);
  exercise1(global->vet1);
}


// EXERCISE 2 =========================

/**
 * @brief Filters first subsequence (V1) and transforms it into a Hash Table
 * 
 * @param global 
 */
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

/**
 * @brief Variable chenges while running firstSearchInElemList, 
 * when there hasn't been found an element whose value is greater or equal 
 * to the one studying
 * 
 * @param currElem current element while looping in the element List
 * @param prevElem previous element while looping in the element List
 * @param bestStep 
 * @param elemStep 
 * @param elem element studying
 */
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

/**
 * @brief If there are unwanted elements in the element List 'currElem',
 * deletes them
 * 
 * @param currElem 
 */
void deleteElements(myList<element>* currElem){
  element elem = currElem->value;
  myList<element>* aux;
  while ( ((currElem->next)!=NULL) && (elem.deletes(currElem->next->value))){
    aux = currElem->next;
    currElem->next = aux ->next;
    free(aux);
  }
}

/**
 * @brief Check if 'elem' should be added in the element List
 * 
 * @param myElist element List
 * @param prevElem 
 * @param elem element studying
 * @param elemStep element step if added
 * @param bestStep best possible step found
 * @param done 
 * @param control controls the function flow
 * @return 0 -> not added, element step -> added
 */
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

/**
 * @brief checks if new element can substitute same element in element List
 * 
 * @param currElem 
 * @param elemStep 
 * @param bestStep 
 * @param done 
 * @return 0 -> not added, element step -> added
 */
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

/**
 * @brief searches for a place for 'elem' in the element List
 * 
 * @param myElemList element List
 * @param elem 
 * @param done 
 * @param bestStep 
 * @return int 
 */
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

/**
 * @brief Checks if 'val' should be added to the element List and how many times, 
 * depending on the index's of the value in V1
 * 
 * @param myElemList element List
 * @param val 
 * @param valInds index's of the value in V1
 * @return maxStep found (Z)
 */
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

/**
 * @brief Iterates through the Subsequences
 * and finds and prints the wanted value, Z
 * 
 * @param vet Second Subsequence (V2)
 * @param vetMap First Subsequence (V1)
 */
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


/**
 * @brief Starts running exercise 2
 * 
 * @return char 
 */
void runExercise2(){
  Global* global = initGlobalEx2Part1();
  storeUserInput(global);
  global->vet1 = new myVetor();
  storeUserInput(global);
  filterFirstArray(global);
  exercise2(global->vet1,global->vetorMap);
}


// MAIN ===============================
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
    runExercise1();
  } else {
    runExercise2();
  }
  return 0;
}
