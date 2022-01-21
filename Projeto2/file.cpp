#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;


/* e se em vez de usar ponteiros nos vertices ligados, e se eu
 colocasse int's que corresponderiam ao indice na motherArray? (seria uma solucao, caso
tenha memorylimit, diminuia para metade do espaco ocupado pelos ponteiros, mas preciava de saber o indice 
de um vertice sempre que o analisava)*/

enum color {
  notVisited,
  visitedNow,
  visitedBefore,
};

class vertice {
  public:
    int value;
    color vColor;
    vector<vertice* >* son;

  vertice(int value){
    this->value = value;
    this->son = NULL;
    this->vColor = notVisited;
  }

  char addSon(vertice* newSon){
    if (this->son == NULL){
        this->son = new vector<vertice*>;
    } else if (this->son->size() == 2){
      return -1;
    }
    this->son->push_back(newSon);  
    return 0;
  }
};




vertice* getVerticesAndEdges(vertice* arr, int edgesNum, char* errorHandler){
  int v1,v2;
  for (int i=0; i<edgesNum; i++){
    if (scanf("%d%d",&v1,&v2)==-1)
      return NULL;
    v1--; v2--;
    if (arr[v2].addSon(&(arr[v1])) == -1){
      *errorHandler=1;
      return NULL;
    }
  }
  return arr;
}

vertice* storeUserInput(int* verticeNum, char* errorHandler){
  *errorHandler = 0;
  int edgesNum;
  vertice* arr;
  if (scanf("%d%d",verticeNum,&edgesNum)==-1)
    return NULL;
  arr = (vertice*) malloc(sizeof(vertice)*(*verticeNum));
  for (int i=0;i<(*verticeNum);i++){
    arr[i] = vertice((i+1));
  }
  return getVerticesAndEdges(arr,edgesNum, errorHandler);
}


char visit(vertice* vert){
  if (vert->vColor == visitedNow){
    return -1;
  }
  if (vert->vColor != visitedBefore){ 
    vert->vColor = visitedNow;
    if (vert->son != NULL){
      for (vector<vertice*>::iterator it = vert->son->begin(); it !=vert->son->end(); ++it){
        if (visit(*it)==-1) { return -1; }
      }
    }
    vert->vColor = visitedBefore;
  }
  return 0;
}


char checkValidGraph(vertice* graph, int verticeNum){
  vertice* v;
  for (int i=0;i<verticeNum;i++){
    v = &graph[i];
    if ((v->vColor != visitedBefore) && (visit(&graph[i])==-1))
      return -1;
  }
  return 0;
}







int main(){
  // StoreUserInput
  int numVertices;
  char errorHandler;
  int valueV1, valueV2;
  if (scanf("%d%d",&valueV1,&valueV2)==-1)
    return -1;
  vertice* graph = storeUserInput(&numVertices,&errorHandler);
  if (errorHandler){
    printf("0\n");
  }
  if (graph == NULL){
    return -1;
  }
  //TODO: passar isto para uma estrutura com vertice* + int numVertices
  // CheckValidTree
  if (checkValidGraph(graph,numVertices)==-1){
    printf("0\n");
  } else {
    printf("hello\n");
  } 
  return 0;
}
