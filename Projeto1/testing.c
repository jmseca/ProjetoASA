#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAP_BASE_SIZE 50

typedef struct {
  int value;
  short reps;
  short step;
} element;

typedef struct {
  element* arr;
  int currSize;
} elementArray;

typedef struct {
  char occ;
  int value;
} mapElement;

typedef struct {
  mapElement* mapArr;
  int size;
} myMap;

myMap* initMyMap(){
  myMap* map = (myMap*) malloc(sizeof(myMap));
  map->mapArr = (mapElement*) malloc(sizeof(mapElement)*MAP_BASE_SIZE);
  int i;
  for (i=0;i<MAP_BASE_SIZE;i++){
    map->mapArr[i].occ=0; //free
  }
  map->size=MAP_BASE_SIZE;
}

int myHashFunction(myMap* map, int value){
  return value % map->size;
}

char addToMap(myMap* map, int val){
  int ind = myHashFunction(map,val);
  if (map->mapArr[ind].occ=0){
    map->mapArr[ind].value=val;
  } else {
    return -1; 
  }
  return 0;
}

void rebuildMap(myMap* map){
  myMap* newMap = initMyMap();
  char err;
  int i,val;
  for (i=0;i<map->size;i++){
    if ((val=map->mapArr[i].occ)==1){
      if(addToMap(newMap,val)==-1){
        //freeMap(newMap);
        
      };
    }
  }
}


int binarySearch(int* array, int s, int e, int find) {
  int m,comp;
  if ( (e==-1) || find > array[e]){
    return e+1;
  }
  m = (s + e)/2;
  comp = array[m]-find;
  if (!comp)
    return m;
  else if (comp<0)  
    return binarySearch(array, m+1, e, find);
  else
    return binarySearch(array, s, m-1, find);
}


int main(){
  int* a = (int*) malloc(sizeof(int));
  int* b = (int*) malloc(sizeof(int));
  int* c = (int*) malloc(sizeof(int));
  *a = 2;
  *b = 3;
  printf("a = %d, b = %d\n",*a,*b);
  c = a;
  a = b;
  b = c;


  printf("a = %d, b = %d\n",*a,*b);
  


  return 0;
}