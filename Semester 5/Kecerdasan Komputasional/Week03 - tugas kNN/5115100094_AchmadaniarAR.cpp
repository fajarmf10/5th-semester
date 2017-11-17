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
struct hasil_struct arr[3049]={0};
int main()
{
	cout<<"Selamat datang di program penghitung K-Nn dengan Cosine Similarity"<<endl<<endl;
	cout<<"About"<<endl;
	cout<<"Nama : Achmadaniar Anindya Rhosady"<<endl;
	cout<<"NRP : 5115100094"<<endl;
	cout<<"Kelas : KK F"<<endl<<endl;
	system("pause");
	system("cls");	
	ifstream file("spambase.data");	
	int i=1;
	string line;
	//Fetch data Training
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
	cout<<"Calculating vector data ..."<<endl;
	double vectordata[4602];
	for(int i=1;i<4602;i++)
	{
		double result=0;
		for(int j=0;j<57;j++)
		{
			result += (data[i][j]*data[i][j]);
		}
		vectordata[i]=sqrt(result);
	}
	cout<<endl;
	int testing;
	while(1)
	{
		cout<<"Pilih data yang akan di tes (3049-4601) ketik 0 untuk keluar"<<": ";
		cin>>testing;
		if(testing==0)break;
		if(testing<3049)continue;
		cout<<endl<<"Data Testing anda :"<<endl;
		for(int j=0;j<57;j++)
		{
			cout<<data[testing][j]<<" ";
		}
		cout<<endl<<endl;		
		cout<<"Calculating Cosine Similarity ...";
		for(int i=1;i<3049;i++)
		{
			arr[i].label=i;
			int result=0;
			for(int j=0;j<58;j++)
			{
				result += (data[i][j] * data[testing][j]);
			}
			arr[i].nilai = result / (vectordata[i]*vectordata[testing]);
		}		
		sort(arr, arr+3049, acompare);
		cout<<endl<<endl;
		int k;
		while(1)
		{
			cout<<"Masukkan Jumlah K anda (masukan 0 untuk selesai):";
			cin>>k;
			if(k==0)break;
			int spam=0,tidak=0;
			for(int i=0;i<k;i++)
			{
				cout<<"Data ke- "<<arr[i].label<<" dengan nilai cos similarity = "<<arr[i].nilai<<", spam/tidak(1/0) = "<<data[arr[i].label][57]<<endl;
				if(data[arr[i].label][57]==1)spam++;
				else if(data[arr[i].label][57]==0)tidak++;
			}			
			cout<<endl;
			cout<<"Maka dengan K= "<<k<<", dianggap sebagai ";
			if(spam>tidak)cout<<"SPAM"<<endl;
			else if(spam==tidak)cout<<"DRAW (SPAM dan TIDAK bernilai sama)"<<endl;
			else cout<<"TIDAK SPAM"<<endl<<endl;
		}		
		cout<<endl;
		system("pause");
		system("cls");		
	}
	cout<<endl<<"Terima Kasih Telah menggunakan Program Kami"<<endl;
	return 0;
}
