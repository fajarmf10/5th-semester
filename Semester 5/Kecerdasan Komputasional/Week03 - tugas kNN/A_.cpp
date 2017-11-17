#include<stdio.h>
#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<string.h>
#include <algorithm>
#include<string>
#include<sstream>
#include<math.h>
using namespace std;

struct hasil_struct
{
	int label;
	double nilai;
};

bool acompare(hasil_struct lhs, hasil_struct rhs) { return lhs.nilai > rhs.nilai; }
double data[4602][58];
struct hasil_struct hasildata[3069]={0};

int main()
{
	ifstream file("spambase.data");
	int i=1;
	double accuracy=0;
	string line;
	int k;
	
	cout<<"Fetching Data ..."<<endl;
	while(getline(file, line)){   
	   	stringstream ss(line);
	   	int j=0;
	    while(getline(ss, line, ',')){
	        istringstream iss(line);			
			iss >> data[i][j];			
			j++;
	   	}	   		 	
	   	i++;
	   	if(i==4602)break;  
	}
	cout<<endl;
	int q;
	while(1)
	{
	cout<<"Masukkan Jumlah K anda (masukan 0 untuk selesai):";
			cin>>k;
			if(k==0)break;
	for (q=3069; q<=4061; q++)
	{
		double vektor[4602];
		for(int i=1;i<4602;i++)
		{
		double result=0;
		for(int j=0;j<57;j++)
			{
				result += (data[i][j]*data[i][j]);
			}
			vektor[i]=sqrt(result);
		}
		for(int i=1;i<3069;i++)
		{
			hasildata[i].label=i;
			int result=0;
			for(int j=0;j<58;j++)
			{
				result += (data[i][j] * data[q][j]);
			}
			hasildata[i].nilai = result / (vektor[i]*vektor[q]);
		}
		sort(hasildata, hasildata+3069, acompare);
			int spam=0,tidak=0;
			for(int i=0;i<k;i++)
			{
				
				if(data[hasildata[i].label][57]==1)spam++;
				else if(data[hasildata[i].label][57]==0)tidak++;
			}			
			if(spam>tidak){
				if(data[q][57]==1)accuracy++;
			}
			else{
			if(data[q][57]==0)accuracy++;
		}
	}
		cout<<endl;
		double x;
		x=(accuracy/1533)*100;
		cout<<"Akurasi(k="<<k<<"): "<<x<<"%"<<endl;
		accuracy=0;
		system("pause");
		system("cls");		
	}
	return 0;
}

