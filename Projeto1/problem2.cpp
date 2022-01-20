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

    myListHead(T value){
      first = new myList<T>(value);
      last = first;
    }

    myListHead(){
      first = NULL; last = NULL;
    }

    void addToList(T val){
      if (first == NULL){
        first = new myList<T>(val);
        last = first;
      } else {
        last->next = new myList<T>(val);
        last = last->next;
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

    /*void print(){
      myList* nextL = first;
      while (nextL!=NULL){
        printf("%d->",nextL->value);
        nextL = nextL->next;
      } printf("\n");
    }*/
};



int main(){
  element e1;
  e1.step=0;e1.reps=0;e1.value=2;
  myListHead<element>* mLH1 = new myListHead<element>(e1);
  myListHead<int>* mLH2 = new myListHead<int>(3);


  return 0;
}
