#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;

class myVerticeList {
  public:
    vertice* value;
    myVerticeList* next;

    myVerticeList(vertice* val){
      value = val;
      next = NULL;
    }

    myVerticeList* deleteL(myVerticeList* prev){
      prev->next = this->next;
      free(this);
      return prev->next;
    }
};

class myVerticeListHead {
  public:
    myVerticeList* first;
    myVerticeList* last;

    myVerticeListHead(){
      first = NULL; last = NULL;
    }

    myVerticeListHead(vertice* value){
      first = new myVerticeList(value);
      last = first;
    }

    void pushBack(vertice* val){
      if (first == NULL){
        first = new myVerticeList(val);
        last = first;
      } else {
        last->next = new myVerticeList(val);
        last = last->next;
      }
    }
};

class vertice {
    private:
        int _value;
        myVerticeListHead* _son;

    vertice(int value){
        this->_value = value;
        this->_son = new myVerticeListHead();
    }

    void addSon(vertice* newSon){
        this->_son->pushBack(newSon);
    }
};

