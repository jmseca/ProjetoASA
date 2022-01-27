#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <set>

using namespace std;


class Vertice {
  public:
    int value;
    /* color
    DFS: 0->notVisited, 1->visitedNow, 2->visitedBefore
    BFS1: d[v]
    */
    int color;
    int bfs2Dist;
    char farCommonAncestor;
    vector<Vertice* >* son;

  Vertice(int value){
    this->value = value;
    this->son = NULL;
    this->color = 0;
    this->farCommonAncestor = 0;
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

  void setSonsAsFarCommonAncestors(){
    if (this->son != NULL){
      for (vector<Vertice*>::iterator it = this->son->begin(); it !=this->son->end(); ++it){
        (*it)->setAsFarCommonAncestor();
      }
    }
  }

  void setAsFarCommonAncestor(){
    if (!this->farCommonAncestor){
      this->farCommonAncestor = 1;
      this->setSonsAsFarCommonAncestors();
    }
  }

  char isFarCommonAncestor(){
    return this->farCommonAncestor;
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

  char verticeIsFarCommonAncestor(int vertIndex){
    return this->vertices[vertIndex].farCommonAncestor;
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


char visit(Vertice* vert){ 
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
  int distance;
  if (vert->bfs1GetDistance()>=0){
    closestAncestors->insert(vert->value);
  } else {
    vertQueue.push(vert);
    vert->bfs2SetDistance(0);
    while (!vertQueue.empty()){
      vert = vertQueue.front();
      vertQueue.pop();
      distance = (vert->bfs2GetDistance() + 1);
      if (vert->son != NULL){
        for (vector<Vertice*>::iterator it = vert->son->begin(); it !=vert->son->end(); ++it){
          if (!(*it)->isFarCommonAncestor()) {
            if ((*it)->bfs1GetDistance()>=0){
              if (!vert->farCommonAncestor){
                closestAncestors->insert((*it)->value);
                (*it)->setSonsAsFarCommonAncestors();
              }
            } else {
              (*it)->bfs2SetDistance(distance);
              vertQueue.push(*it);
            }
          }
        }
      }
    }
  }
}

void printClosestAncestors(Graph* graph, set<int>* closestAncestors){
  if (closestAncestors->empty()){
    printf("-\n");
  } else {
    for (set<int>::iterator itr = closestAncestors->begin(); itr != closestAncestors->end(); itr++) {
      if (!graph->verticeIsFarCommonAncestor(((*itr)-1)) ){
        printf("%d ",*itr);
      }
    }
    printf("\n");
  }
}


void computeAndShowClosestAncestors(Graph* graph, int valueV1, int valueV2){
  set<int>* closestAncestores = new set<int>;
  graph->bfsInit();
  bfsVertice1(graph, --valueV1);
  bfsVertice2(graph, --valueV2, closestAncestores);
  printClosestAncestors(graph, closestAncestores);

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
  // CheckValidTree
  if (checkValidGraph(graph)==-1){
    printf("0\n");
  } else {
    computeAndShowClosestAncestors(graph,valueV1,valueV2);
  } 

  return 0;
}
