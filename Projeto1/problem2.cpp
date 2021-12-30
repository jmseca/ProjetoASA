#include <map>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

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
  vetor* vet1;
  vetor* vet2;
  map<int,char>* mp;
} Global;

class myList {
  public:
    int value;
    myList* next;

    myList(int val){
      value = val;
      next = NULL;
    }

    void deleteL(myList* prev){
      prev->next = this->next;
      free(this);
    }
};

class myListHead {
  public:
    myList* first;
    myList* last;

    myListHead(){
      first = NULL; last = NULL;
    }

    myListHead(int value){
      myList mL = myList(value);
      first = new myList(value);
      last = first;
    }

    void addToList(int value){
      if (first == NULL){
        myListHead(value);
      } else {
        last->next = new myList(value);
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


vetor* initVetor(){
   vetor *vet = (vetor*) malloc(sizeof(vetor));
   vet->arr = (int*) malloc(sizeof(int)*50);
   vet->size = 50;
   vet->currSize = 0;
   return vet;
}

/*Global stuff*/
Global* initGlobalEx1(){
  Global* global = (Global*) malloc(sizeof(Global));
  global->vet1 = initVetor();
  global->vet2 = NULL;
  global->mp = new map<int,char>;
  //global->mp = (map<int,char>*) malloc(sizeof(map<int,char>));
  return global;
}


int main(){
  char errorHandler;
  myListHead mLH = myListHead(3);
  mLH.addToList(4);
  mLH.addToList(6);
  mLH.addToList(7);
  mLH.addToList(8);
  mLH.addToList(5);
  mLH.print();
  int a = mLH.pop(&errorHandler);
  if (errorHandler){
    printf("morreu\n");
  }
  mLH.print();
  a = mLH.pop(&errorHandler);
  if (errorHandler){
    printf("morreu\n");
  }
  mLH.print();
  



  return 0;
}
