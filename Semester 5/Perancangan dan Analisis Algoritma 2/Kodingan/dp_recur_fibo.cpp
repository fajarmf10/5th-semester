#include <stdio.h>
#include <time.h>

/*
*
*	Fibonacci using Dynamic Programming
*	15/09/2017
*
*/

long long int Fibo(int n);
long long int f[101];

int main(){
	int n;
	
	printf("Masukkan nilai n >  ");
	scanf("%d", &n);
	printf("Hasilnya adalah %lld\n", Fibo(n));
	return 0;
}

long long int Fibo(int n){
	if(n == 2 || n == 1) return 1;
	if(f[n] > 0) return f[n];
	return (f[n] = Fibo(n-1)+Fibo(n-2));
}

