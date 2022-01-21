#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;


/* e se em vez de usar ponteiros nos vertices ligados, e se eu
 colocasse int's que corresponderiam ao indice na motherArray? (seria uma solucao, caso
tenha memorylimit, diminuia para metade do espaco ocupado pelos ponteiros, mas preciava de saber o indice 
de um vertice sempre que o analisava)*/

enum Color {
  notVisited,
  visitedNow,
  visitedBefore,
};

class Vertice {
  public:
    int value;
    Color vColor;
    vector<Vertice* >* son;

  Vertice(int value){
    this->value = value;
    this->son = NULL;
    this->vColor = notVisited;
  }

  char addSon(Vertice* newSon){
    if (this->son == NULL){
        this->son = new vector<Vertice*>;
    } else if (this->son->size() == 2){
      return -1;
    }
    this->son->push_back(newSon);  
    return 0;
  }
};

char visit(Vertice* vert);

class Graph {
  public:
    Vertice* vertices;
    int verticesNum;
    int edgedNum;

  Graph(){
    this->verticesNum=0;
    this->edgedNum=0;
    this->vertices = NULL;
  }


  char getEdgeVertNumFormInput(){
    if (scanf("%d%d",&(this->verticesNum),&(this->edgedNum))==-1)
      return -1;
    return 0;
  }

  char addSonToVertice(int vertIndex, int sonIndex){
    return this->vertices[vertIndex].addSon(&(this->vertices[sonIndex]));
  }

  void initVertices(){
    this->vertices = (Vertice*) malloc(sizeof(Vertice)*(this->verticesNum));
    for (int i=0;i<(this->verticesNum);i++){
      this->vertices[i] = Vertice((i+1));
    }
  }

  Color getVerticeColor(int vertIndex){
    return this->vertices[vertIndex].vColor;
  }

  char visitVertice(int vertIndex){
    return visit(&(this->vertices[vertIndex]));
  }
};




Graph* getVerticesAndEdges(Graph* graph, char* errorHandler){
  int v1,v2;
  for (int i=0; i<(graph->edgedNum); i++){
    if (scanf("%d%d",&v1,&v2)==-1)
      return NULL;
    v1--; v2--;
    if (graph->addSonToVertice(v2,v1) == -1){
      *errorHandler=1;
      return NULL;
    }
  }
  return graph;
}

Graph* storeUserInput(int* verticeNum, char* errorHandler){
  *errorHandler = 0;
  Graph* graph = new Graph();
  if (graph->getEdgeVertNumFormInput()){
    return NULL;
  }
  graph->initVertices();
  return getVerticesAndEdges(graph, errorHandler);
}


char visit(Vertice* vert){ //TODO ponderar usar colocar isto na class dos vertices e ver se nao tenho MLE
  if (vert->vColor == visitedNow){
    return -1;
  }
  if (vert->vColor != visitedBefore){ 
    vert->vColor = visitedNow;
    if (vert->son != NULL){
      for (vector<Vertice*>::iterator it = vert->son->begin(); it !=vert->son->end(); ++it){
        if (visit(*it)==-1) { return -1; }
      }
    }
    vert->vColor = visitedBefore;
  }
  return 0;
}


char checkValidGraph(Graph* graph){
  for (int i=0;i<(graph->verticesNum);i++){
    if (( (graph->getVerticeColor(i)) != visitedBefore) && (graph->visitVertice(i)==-1))
      return -1;
  }
  return 0;
}




void computeAndShowClosestAncestors(Graph* graph, int valueV1, int valueV2){

}



int main(){
  // StoreUserInput
  int numVertices;
  char errorHandler;
  int valueV1, valueV2;
  if (scanf("%d%d",&valueV1,&valueV2)==-1)
    return -1;
  Graph* graph = storeUserInput(&numVertices,&errorHandler);
  if (errorHandler){
    printf("0\n");
  }
  if (graph == NULL){
    return -1;
  }
  //TODO: passar isto para uma estrutura com vertice* + int numVertices
  // CheckValidTree
  if (checkValidGraph(graph)==-1){
    printf("0\n");
  } else {
    computeAndShowClosestAncestors(graph,valueV1,valueV2);
  } 
  return 0;
}
