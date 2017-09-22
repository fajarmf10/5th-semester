#include <stdio.h>

/*
*
*	Cut Rod implementing the Top-down
*	 approach of Dynamic Programming
*
*		Fajar Maulana Firdaus
*
*/


int Rek(int n);
int Maks(int hasil, int P);

int P[100] = {0,1,5,8,9,10,17,17,20,24,30};
int temp[100];

int main(){
	int n;
	for(int i=11; i<=100; i++){
		P[i] = P[i-1] + 1;
	}
	printf("Masukkan panjang besi baja >  ");
	scanf("%d", &n);
	
//	for(i)
	
	printf("%lld", Rek(n));
//	printf(tuingtuing);
}

int Rek(int n){
	if(temp[n]>0) return temp[n];
	else if(n==0) return 0;
	else{
		long long int hasil = 0;
		for(int i=1; i<=n; i++){
			hasil = Maks(hasil, P[i] + Rek(n-i));
		}
		temp[n] = hasil;
		return temp[n];
		
	}
}

int Maks(int hasil, int P){
	if(hasil>P) return hasil;
	else if(hasil<P) return P;
	else return hasil;
}
