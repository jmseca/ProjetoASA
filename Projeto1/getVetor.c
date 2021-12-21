// Vai ser apagado, é só para fazer a função getVetor


#include <stdlib.h>
#include <stdio.h>


int main(){
  char buffer[5];
  fgets(buffer,5,stdin);
  for (int i=0;i<5;i++){
    printf("%c-",buffer[i]);
  }
  int a = atoi(buffer);
  printf("->>>>>%d\n",a);
  return 0;
}
