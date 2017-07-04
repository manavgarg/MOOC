#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

unsigned long long int counter =0;

void mergesort(int n[], int a, int start){

   if(a == 1){return ;}
  	int size1,size2; 
	if(a%2 ==0 ){
	   size1 = a/2;
	   size2 = a/2;}
	else {
	   size1 = a/2;
	   size2 = a/2 + 1;}
  
 
           mergesort(n,size1,start);
	   mergesort(n,size2,(start+size1));

	int n1[size1], n2[size2];
	for(int i=0;i<size1;i++){
	     n1[i] = n[start+i];}
	for(int j=0;j<size2;j++){
	     n2[j] = n[start+size1+j];}

   //Merge algo
      int l = 0;
      int m = 0;
      for(int k=start; k<start +a; k++){
	 
	 if(l == size1){
	    n[k] = n2[m];
	    m++;    }
	 else if( m == size2){
	    n[k] =n1[l];  
		l++;}	    
         else if(n1[l] < n2[m]){
	       n[k] = n1[l]; 
               l++; }
	 else { n[k] = n2[m] ;
		counter = counter + size1 -l;
       //        cout << counter<<endl;
		m++;}
        }

        return ;

 }

int main (){

ifstream in("IntegerArray.txt");
int number;
int n[100000];
int i =0;
while (in>>number){
         n[i] = number;
	 i++;
	}

in.close();

//cout <<array[2]<<endl;
int size = 100000;
int start =0;

for(int q=0; q<size; q++){
cout << n[q]<<endl;
}

mergesort(n,size,start);

cout <<"The  count ="<<counter<<endl;

for(int o=0; o<size; o++){
//cout << n[o]<<endl;
}

return 0;
}


// Answer for problem 1 is 2407905288




