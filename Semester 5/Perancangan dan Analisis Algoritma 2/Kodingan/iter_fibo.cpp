#include <stdio.h>
#include <time.h>

/*
*
*	Fibonacci using Iteration
*	15/09/2017
*
*/

int main(){
	int n;
	long long f[101];
	f[1]=1;
	f[2]=1;
	
	printf("Masukkan nilai n >  ");
	scanf("%d",&n);
	for(int i=3; i<= n; i++){
		f[i]=f[i-1]+f[i-2];
	}
	printf("Hasilnya %lld\n", f[n]);
	return 0;
}
