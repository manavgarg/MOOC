// Implemented using heaps ( min and max)
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void MinInsert(vector <int> &min ,int v){
     	
     min.push_back(v);
     int l=min.size() -1;	
	while(l>0){
	 if( min[l] < min[(l-1)/2]){
		int temp;
		temp = min[l];
		min[l] = min[(l-1)/2];
		min[(l-1)/2] = temp;
		l=(l-1)/2;}
	 else {break;}
	}
}

void MaxInsert(vector <int> &max ,int v){
     	
     max.push_back(v);
     int l=max.size() -1;	
	while(l>0){
	 if( max[l] > max[(l-1)/2]){
		int temp;
		temp = max[l];
		max[l] = max[(l-1)/2];
		max[(l-1)/2] = temp;
		l=(l-1)/2;}
	 else {break;}
	}
}

void delete_swap_min(vector <int> &min , int start){
	int f = ((min.size()-1)/2);
	while(start<f){
	     int first,second;
	     first = 2*start +1;
	     second = 2*start +2;
	     if((min[start] <= min[first]) && (min[start] <= min[second])) { break;} 					
	     if(min[first] <= min[second]){
		int temp;
		temp = min[start];
		min[start] = min[first];
		min[first] = temp;
		start = first;	}
	     else {
		int temp;
		temp = min[start];
		min[start] = min[second];
		min[second] = temp;
		start = second;	}
	}
}	

void delete_swap_max(vector <int> &max , int start){
	int f = ((max.size()-1)/2);
	while(start<f){
	     int first,second;
	     first = 2*start +1;
	     second = 2*start +2;
	     if((max[start] >= max[first]) && (max[start] >= max[second])) { break;} 					
	     if(max[first] >= max[second]){
		int temp;
		temp = max[start];
		max[start] = max[first];
		max[first] = temp;
		start = first;	}
	     else {
		int temp;
		temp = max[start];
		max[start] = max[second];
		max[second] = temp;
		start = second;	}
	}
}	

int ExtractMin(vector <int> &min){
	int vertex = min[0];
	int size = min.size();
	min[0] = min[size-1];
	min.resize(size-1);
	size = min.size();
	int start=0;

	delete_swap_min(min,start);
	return vertex;
}

int ExtractMax(vector <int> &max){
	int vertex = max[0];
	int size = max.size();
	max[0] = max[size-1];
	max.resize(size-1);
	size = max.size();
	int start=0;

	delete_swap_max(max,start);
	return vertex;
}					  	

int main (){

ifstream in("Median.txt");
int n;
vector <int> numbers;
while(in>>n){
  numbers.push_back(n);}

vector <int> min ;
vector <int> max ;
vector <int> median ;

for(int i=0;i<numbers.size();i++){
 int v = numbers[i]; int minv =10001; int maxv =-1;
 if(min.size() !=0){minv = min[0] ;}
 if(max.size() !=0){maxv = max[0] ;}
 
 if(v<=maxv){ MaxInsert(max,v);}
 else if(v>=minv){ MinInsert(min,v);} 
 else if (min.size() < max.size()){ MinInsert(min,v);}
 else { MaxInsert(max,v);}

 int y=min.size(); int z=max.size();	 
 if(y-z>1){ 
    int r1 = ExtractMin(min);
    MaxInsert(max,r1);
 }
	
 if(z-y>1){ 
    int r2 = ExtractMax(max);
    MinInsert(min,r2);
 }
 if(min.size() > max.size()){ median.push_back(min[0]);}
 else {median.push_back(max[0]);}
}

long long int sum = 0;

for(int j=0; j< median.size(); j++){
   sum+= median[j];
//   cout<<median[j]<<endl;	
}

cout << sum<<endl;


in.close();

return 0;
}
// The sum of medians is 46831213, The answer to PA-6.2 is 1213
