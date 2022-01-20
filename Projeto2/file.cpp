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
        char visitedTimes;
        vector<vertice* >* son;

    vertice(int value){
        this->value = value;
        this->son = NULL;
        this->vColor = notVisited;
        this->visitedTimes = 0;
    }

    void addSon(vertice* newSon){
        if (this->son == NULL){
            this->son = new vector<vertice*>;
        this->son->push_back(newSon); 
        } 
    }
};




vertice* getVerticesAndEdges(vertice* arr, int edgesNum){
  int v1,v2;
  for (int i=0; i<edgesNum; i++){
    scanf("%d%d\n",&v1,&v2);
    v1--; v2--;
    if (arr[v1].value==(-1)) { arr[v1].value = (v1+1); }
    if (arr[v2].value==(-1)) { arr[v2].value = (v2+1); }
    arr[v2].addSon(&(arr[v1]));
  }
  return arr;
}

vertice* storeUserInput(int* verticeNum){
    int v1Val, v2Val;
    int edgesNum;
    vertice* arr;
    scanf("%d%d\n",&v1Val,&v2Val);
    scanf("%d%d\n",verticeNum,&edgesNum);
    arr = (vertice*) malloc(sizeof(vertice)*(*verticeNum));
    for (int i=0;i<(*verticeNum);i++){
      arr[i].value = -1;
    }
    return getVerticesAndEdges(arr,edgesNum);
}


char visit(vertice* vert){
  if (vert->visitedTimes == 2 || vert->vColor == visitedNow){
    return -1;
  }
  vert->visitedTimes++;
  if (vert->vColor != visitedBefore){ 
    vert->vColor = visitedNow;
    vector<vertice*>* sons = vert->son;
    int ind = 0;
    for (vector<vertice*>::iterator it = sons->begin(); it !=sons->end(); ++it,++ind){
      visit(sons->at(ind));
    }
    vert->vColor = visitedBefore;
  }
  return 0;
}


char checkValidGraph(vertice* graph, int verticeNum){
  vertice* v;
  for (int i=0;i<verticeNum;i++){
    v = &graph[i];
    if (v->vColor != visitedBefore){
      if (visit(&graph[i])==-1){
        return -1;
      }
    }
  }
  return 0;
}







int main(){
  // StoreUserInput
  int numVertices;
  vertice* graph = storeUserInput(&numVertices);
  //TODO: passar isto para uma estrutura com vertice* + int numVertices
  // CheckValidTree
  if (checkValidGraph(graph,numVertices)==-1){
    printf("0\n");
  } else {
    printf("hello\n");
  } 
  return 0;
}
