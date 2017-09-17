#include <stdio.h>

int Fibo(int n);

int main(){
	unsigned long long int hasil;
	int n;
	
	printf("Masukkan nilai n >  ");
	scanf("%d", &n);
	hasil = Fibo(n);
	printf("Hasilnya adalah %lld", hasil);
	return 0;
}

int Fibo(int n){
	int a=0;
	long long b=1;
	while (n-- > 1){
		int t = a;
		a = b;
		b += t;
	}
	return b;
}

