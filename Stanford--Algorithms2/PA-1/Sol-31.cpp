// Added new heap function heap_delete_balancing_bubbleup. The previous implementation of heap was not fully correct.
// This change adds the bubbleup reqd while deleting in some cases before bubbling down.
// Also, the result is the same independent of the choice of the start vertex.
// The start vertex in this solution is the last node(500)
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
	int f = ((heap.size()-1)/2);
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

int heap_delete_balancing_bubbleup(vector <int> &heap, vector <int>&min ,int start){
	int l=start;
	while(l>0){
	 if( min[heap[l]] < min[heap[(l-1)/2]]){
		int temp;
		temp = heap[l];
		heap[l] = heap[(l-1)/2];
		heap[(l-1)/2] = temp;
		l=(l-1)/2;}
	 else {break;}
	}
	return l;
}

int ExtractMin( vector <int> &heap, vector <int> &min , vector < vector <int> > &values){
	int vertex = heap[0];
	int size = heap.size();
	heap[0] = heap[size-1];
	heap.resize(size-1);
	int l=0;
	delete_swap(heap,min,l);


	for(int i=0; i<values[vertex].size();i+=2){
	    int hold = 1000000;	
		for(int j=0; j<heap.size();j++){
			if(values[vertex][i] == heap[j]){ hold = j; break;}}
	        int index = hold;
		int value;
	        if(index != 1000000){
	           value = heap[hold];
	           heap[index] = heap[heap.size()-1];
	           heap.resize(heap.size()-1);

		   index = heap_delete_balancing_bubbleup(heap,min,index); 	
		   delete_swap(heap,min,index);   
		   if(min[value] > values[vertex][i+1]){	  	
       	           min[value] = values[vertex][i+1];}
	           heapInsert(heap,min,value);  

    	        }
        }
	return vertex;		 
}				  	
	

int main (){

ifstream in("edges.txt");
int nodes,edges;
in>>nodes>>edges;
vector < vector<int> > values;  
 
for(int k=0; k<=nodes;k++){
   vector <int> row;
   values.push_back(row);}

while(edges--){ int temp,temp1,temp2;
	in>>temp>>temp1>>temp2;
	values[temp].push_back(temp1);
	values[temp].push_back(temp2);
	values[temp1].push_back(temp);
	values[temp1].push_back(temp2);}
	
vector <int> heap;
vector <int> min(nodes+1);

for(int u =1 ;u<=nodes-1;u++){
     int dis = 1000000;	
     for(int i =0; i<values[nodes].size();i+=2){
	 if(u == values[nodes][i]){dis = values[nodes][i+1];break;}} 	
	 min[u] = dis;
     heapInsert(heap,min,u);	
}

int no = nodes-1; int temp3;
while(no>0)
    { temp3 = ExtractMin(heap,min,values);no--;}

long long int sum=0;
for(int i=nodes-1;i>0;i--){
    sum+=min[i];}	
cout<<sum<<endl;

in.close();
return 0;
}

// The answer of PA1.3 is -3612829
