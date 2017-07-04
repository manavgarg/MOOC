#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

unsigned long long int counter =0;

void quicksort(int n[], int a, int start){

   if(a == 1 | a == 0 | a == -1){return ;}
 
   int swap;
   int middle;
   if (a%2 != 0)
       { middle = start + (a/2);  }
   if (a%2 == 0)
       { middle = start + (a/2) -1;  }
   int median;
    if( ((n[start] > n[middle]) && (n[start] < n[start + a -1])) | ((n[start] < n[middle]) && (n[start] > n[start + a -1])))
         median = start; 
    if( ((n[middle] > n[start]) && (n[middle] < n[start + a -1])) | ((n[middle] < n[start]) && (n[middle] > n[start + a -1])))
         median = middle; 
    if( ((n[start+a-1] > n[middle]) && (n[start+a-1] < n[start])) | ((n[start+a-1] < n[middle]) && (n[start+a-1] > n[start])))
         median = start+a-1; 
   swap = n[median];
   n[median] = n[start];;
   n[start] = swap;          
   int pivot = start;
   int temp;
   int p = start+1;   


   for(int i=1; i <a;i++){
  	if(n[start + i] > n[pivot]){ }
	if (n[start + i] < n[pivot]){
 	    temp = n[start+i];
	    n[start+i] = n[p]; 		  	
	    n[p] = temp;
  	    p++;}
	}	
   int temp2; 	
	temp2 = n[pivot];
	n[pivot] = n[p-1];
	n[p-1] = temp2; 

   int size1,size2;
   size1 = p - start -1;
   size2 = start + a -p ;		

	quicksort(n, size1,start);
     //   cout << "size 1:"<<size1;
	quicksort(n, size2,p);
      //  cout << "size 2:"<<size2;
	counter = counter + (a-1) ;

       return ;
 }

int main (){

ifstream in("QuickSort.txt");
int number;
int n[10000];
int i =0;
while (in>>number){
         n[i] = number;
	 i++;
	}

in.close();

int size = 10000;
int start =0;

for(int q=0; q<size; q++){
cout << n[q]<<endl;
}

quicksort(n,size,start);

cout <<"The  count ="<<counter<<endl;
//cout <<"The output"<<endl;

//for(int o=0; o<size; o++){
//cout << n[o]<<endl;
//}

return 0;
}

// Answer P2, Q3 is 138382




