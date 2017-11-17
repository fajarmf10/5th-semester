#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))
/*
Fajar Maulana Firdaus

Terdapat sebuah array bilangan bulat dimana masing-masing elemen mewakili jumlah langkah maksimal yang dapat
dibuat dari elemen tersebut. Tuliskan fungsi untuk mengembalikan jumlah minimum lompatan untuk mencapai akhir
array (mulai dari elemen pertama). Misal: Jika sebuah elemen adalah 0, maka tidak dapat bergerak melalui elemen
itu. Jika sebuah alemen ke i isinya 2, maka dia mempunyai 2 pilihan langkah, yaitu melangkah keelemen i+1, atau melangkah ke elemen i+2

Misal:

Array tersebut adalah: {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9}
Maka jumlah minimum lompatan adalah: 3
Dengan hassil rekontruksinya adalah 1􇐃
*/


int main(){
	int a[1000], k=0;
	int history[100] = { 0 };
	int i;
	int j=0;
	int count=0;
	
	while(scanf("%d", &i)!=EOF){
		a[j] = i;
		j++;
	}
	for(i=0; i<j;i++){
		if(j==0) printf("Tidak bisa melompat\n");
		else{
			if(a[i] > j) printf("Jumlah minimum lompatan adalah : %d\n", count);
			else{
				history[k] = a[i];
				i += a[i];
				count++;
				k++;
			}
		}
	}
	int size = my_sizeof(history)/my_sizeof(history[0]);
	printf("Jumlah minimum lompatan adalah : %d\n", count);
	printf("Dengan hasil rekonstruksinya adalah ");
	for(i=0; i<size; i++){
		if(history[i] != 0){
			printf("%d ", history[i]);
		};
	}
	getch();
	
}

