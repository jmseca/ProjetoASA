#include <map>
#include <vector>
#include <cstdio>

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


int main(){

    map<int,int> mp;
    mp.insert(pair<int,int>(2,2));

    mp.find(2);

    return 0;
}