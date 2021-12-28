#include <stdio.h>


int main(){
	int a = 0;
	long int b=0;
	while (a!=1){
		b++;
		a-=1;
	}

	printf("%ld\n",b);


	return 0;
}
