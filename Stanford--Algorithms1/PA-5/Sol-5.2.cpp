// Solution to PA-5 using heaps

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void heapInsert( vector <int> &heap, vector <int> &min ,int u){
     	
     heap.push_back(u);
     int l=heap.size() -1;	
	while(l>0){
	 if( min[heap[l]] < min[heap[(l-1)/2]]){
		int temp;
		temp = heap[l];
		heap[l] = heap[(l-1)/2];
		heap[(l-1)/2] = temp;
		l=(l-1)/2;}
	 else {break;}
	}
}

void delete_swap(vector <int> &heap, vector <int> &min , int start){
	int f = ((heap.size()-2)/2);
	while(start<f){
	     int first,second;
	     first = 2*start +1;
	     second = 2*start +2;
	     if((min[heap[start]] <= min[heap[first]]) && (min[heap[start]] <= min[heap[second]])) { break;} 					
	     if(min[heap[first]] <= min[heap[second]]){
		int temp;
		temp = heap[start];
		heap[start] = heap[first];
		heap[first] = temp;
		start = first;	}
	     else {
		int temp;
		temp = heap[start];
		heap[start] = heap[second];
		heap[second] = temp;
		start = second;	}
	}
}	

int ExtractMin( vector <int> &heap, vector <int> &min , vector < vector <int> > &values1){
	int vertex = heap[0];
	int size = heap.size();
	heap[0] = heap[size-1];
	heap.resize(size-1);
	int l=0;
	delete_swap(heap,min,l);


	for(int i=0; i<values1[vertex].size();i+=2){
	    int hold = 1000000;	
		for(int j=0; j<heap.size();j++){
			if(values1[vertex][i] == heap[j]){ hold = j; break;}}
	        int index = hold;
		int value;
	        if(index != 1000000){
	           value = heap[hold];
	           heap[index] = heap[heap.size()-1];
	           heap.resize(heap.size()-1);

		   delete_swap(heap,min,index);   
		   if(min[value] > min[vertex] + values1[vertex][i+1]){	  	
       	           min[value] = min[vertex] + values1[vertex][i+1];}
	           heapInsert(heap,min,value);  

    	        }
        }
	return vertex;		 
}				  	
	
int main (){

ifstream in("dijkstraData.txt");
vector < vector<int> > values1; 
string line;
string hold;
int temp;

for(int k=0; k<201;k++){
  vector <int> row;
  values1.push_back(row);	
}

int key =1;
while(getline(in,line)){
	stringstream stream(line);
	stream >>key;
	while(getline(stream,hold,',')){
	 stringstream stream1(hold);
	  while(stream1 >>temp){
		values1[key].push_back(temp);
		}}
}

vector <int> heap;
vector <int> min (201);
min[1] =0;

for(int u =2 ;u<201;u++){
     int dis = 1000000;	
     for(int i =0; i<values1[1].size();i+=2){
	 if(u == values1[1][i]){dis = values1[1][i+1];break;}} 	
	 min[u] = dis;
     heapInsert(heap,min,u);	
}

int no =198; int temp1;
while(no>0)
    { temp1 = ExtractMin(heap,min,values1);no--;}
cout<<min[7]<<","<<min[37]<<","<<min[59]<<","<<min[82]<<","<<min[99]<<","<<min[115]<<","<<min[133]<<","<<min[165]<<","<<min[188]<<","<<min[197]<<endl;
in.close();

return 0;
}

//Answer PA-5:   2599,2610,2947,2052,2367,2399,2029,2442,2505,3068  

