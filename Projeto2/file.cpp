#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <set>

using namespace std;


/* e se em vez de usar ponteiros nos vertices ligados, e se eu
 colocasse int's que corresponderiam ao indice na motherArray? (seria uma solucao, caso
tenha memorylimit, diminuia para metade do espaco ocupado pelos ponteiros, mas preciava de saber o indice 
de um vertice sempre que o analisava)*/

/* No caso de grafos com muitos vertices isolados, o meu algoritmo nao e eficiente, uma vez que guarda os 
vertices todos, e nao precisava. Por isso se tiver TLE, esta pode ser uma hipotese*/



class Vertice {
  public:
    int value;
    /* color
    DFS: 0->notVisited, 1->visitedNow, 2->visitedBefore
    BFS1: d[v]
    */
    int color;
    int bfs2Dist;
    vector<Vertice* >* son;

  Vertice(int value){
    this->value = value;
    this->son = NULL;
    this->color = 0;
    this->bfs2Dist = -1;
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

  char dfsIsVisitedNow(){
    return this->color == 1;
  }

  void dfsSetVisitedNow(){
    this->color = 1;
  }

  char dfsIsVisitedBefore(){
    return this->color == 2;
  } 

  void dfsSetVisitedBefore(){
    this->color = 2;
  }

  void bfs1SetDistance(int newDistance){
    this->color = newDistance;
  }

  int bfs1GetDistance(){
    return this->color;
  }

  void bfs2SetDistance(int newDistance){
    this->bfs2Dist = newDistance;
  }

  int bfs2GetDistance(){
    return this->bfs2Dist;
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

  Vertice* getVertice(int vertIndex){
    return &(this->vertices[vertIndex]);
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

  char dfsVerticeIsVisitedBefore(int vertIndex){
    return this->vertices[vertIndex].color == 2;
  }

  char visitVertice(int vertIndex){
    return visit(&(this->vertices[vertIndex]));
  }

  void bfsInit(){
    for (int i=0;i<this->verticesNum;i++){
      this->vertices[i].color = -1;
    }
  }
};

typedef struct {
  Vertice* vert;
  int distance;
} VerticeWithDistance;





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
  if (vert->dfsIsVisitedNow()){
    return -1;
  }
  if ( !(vert->dfsIsVisitedBefore()) ){ 
    vert->dfsSetVisitedNow();
    if (vert->son != NULL){
      for (vector<Vertice*>::iterator it = vert->son->begin(); it !=vert->son->end(); ++it){
        if (visit(*it)==-1) { return -1; }
      }
    }
    vert->dfsSetVisitedBefore();
  }
  return 0;
}


char checkValidGraph(Graph* graph){
  for (int i=0;i<(graph->verticesNum);i++){
    if (( !(graph->dfsVerticeIsVisitedBefore(i)) && (graph->visitVertice(i)==-1)))
      return -1;
  }
  return 0;
}


void bfsVertice1(Graph* graph, int vertIndex){
  Vertice* vert = graph->getVertice(vertIndex);
  queue<Vertice* > vertQueue;
  int distance;
  vertQueue.push(vert);
  vert->bfs1SetDistance(0);
  while (!vertQueue.empty()){
    vert = vertQueue.front();
    vertQueue.pop();
    distance = (vert->bfs1GetDistance() + 1);
    if (vert->son != NULL){
      for (vector<Vertice*>::iterator it = vert->son->begin(); it !=vert->son->end(); ++it){
        if ((*it)->bfs1GetDistance() < 0){
          (*it)->bfs1SetDistance(distance);
          vertQueue.push(*it);
        }
      }
    }
  }

}

void bfsVertice2(Graph* graph, int vertIndex, set<int>* closestAncestors){
  Vertice* vert = graph->getVertice(vertIndex);
  queue<Vertice* > vertQueue;
  int distance, vertMinDistance, minDistance = 1;
  vertQueue.push(vert);
  vert->bfs2SetDistance(0);
  while (!vertQueue.empty()){
    vert = vertQueue.front();
    vertQueue.pop();
    distance = (vert->bfs2GetDistance() + 1);
    if (vert->son != NULL){
      for (vector<Vertice*>::iterator it = vert->son->begin(); it !=vert->son->end(); ++it){
        if ((*it)->bfs2GetDistance() < 0){
          (*it)->bfs2SetDistance(distance);
          vertQueue.push(*it);
        }
        if ((*it)->bfs1GetDistance()>0){
          vertMinDistance = (*it)->bfs2GetDistance() > (*it)->bfs1GetDistance() 
            ? (*it)->bfs1GetDistance() 
            : (*it)->bfs2GetDistance();

          if (vertMinDistance < minDistance){
            minDistance = vertMinDistance;
            closestAncestors->clear();
            closestAncestors->insert((*it)->value);
          } else if (vertMinDistance == minDistance){
            closestAncestors->insert((*it)->value);
          }
        }
      }
    }
  }

}


void printClosestAncestors(set<int>* closestAncestors){
  if (closestAncestors->empty()){
    printf("-\n");
  } else {
    for (set<int>::iterator itr = closestAncestors->begin(); itr != closestAncestors->end(); itr++) {
      printf("%d ",*itr);
    }
    printf("\n");
  }
}


void computeAndShowClosestAncestors(Graph* graph, int valueV1, int valueV2){
  set<int>* closestAncestores = new set<int>;
  graph->bfsInit();
  bfsVertice1(graph, --valueV1);
  bfsVertice2(graph, --valueV2, closestAncestores);
  printClosestAncestors(closestAncestores);

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
