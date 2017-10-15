#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int n; 
    scanf("%d",&n);
    int arr[n];
    for(int arr_i = 0; arr_i < n; arr_i++){
       scanf("%d",&arr[arr_i]);
    }
    
    float a, b, c; a = b = c = 0;
    
    for(int i=0; i<n;i++){
    	if(arr[i]>0) a++;
    	else if(arr[i]<0) b++;
    	else c++;
	}
	
	printf("%.6f\n", a/(float)n);
	printf("%.6f\n", b/(float)n);
	printf("%.6f\n", c/(float)n);
    
    return 0;
}

