// This is a better solution of PA1.3 usinh heaps with corrrect implementation of node lookup position.
// Instead of iterating thru the elements of heap, a vector (node_heap_pos) is maintained which contains the correct position of nodes in the heap.
// Also, for this implementation the start vertex is first instead of the last as in the previous solution
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
void heapInsert( vector <int> &heap, vector <int> &min , vector <int> &node_heap_pos, int u){
     heap.push_back(u);
     int l=heap.size() -1;
     node_heap_pos[u] =l;	
	while(l>0){
	 if( min[heap[l]] < min[heap[(l-1)/2]]){
		int temp;
		node_heap_pos[heap[l]]= (l-1)/2;
		node_heap_pos[heap[(l-1)/2]]= l;
		temp = heap[l];
		heap[l] = heap[(l-1)/2];
		heap[(l-1)/2] = temp;
		l=(l-1)/2;}
	 else {break;}
	}
}

void delete_swap(vector <int> &heap, vector <int> &min , vector <int> &node_heap_pos, int start){
	int f = ((heap.size()-1)/2);
	while(start<f){
	     int first,second;
	     first = 2*start +1;
	     second = 2*start +2;
	     if((min[heap[start]] <= min[heap[first]]) && (min[heap[start]] <= min[heap[second]])) { break;} 					
	     if(min[heap[first]] <= min[heap[second]]){
		int temp;
		node_heap_pos[heap[start]] =first;
		node_heap_pos[heap[first]] =start;
		temp = heap[start];
		heap[start] = heap[first];
		heap[first] = temp;
		start = first;	}
	     else {
		int temp;
		node_heap_pos[heap[start]] =second;
		node_heap_pos[heap[second]] =start;
		temp = heap[start];
		heap[start] = heap[second];
		heap[second] = temp;
		start = second;	}
	}
}

int heap_delete_balancing_bubbleup(vector <int> &heap, vector <int>&min , vector <int> &node_heap_pos, int start){
	int l=start;
	while(l>0){
	 if( min[heap[l]] < min[heap[(l-1)/2]]){
		int temp;
		node_heap_pos[heap[l]]= (l-1)/2;
		node_heap_pos[heap[(l-1)/2]]= l;
		temp = heap[l];
		heap[l] = heap[(l-1)/2];
		heap[(l-1)/2] = temp;
		l=(l-1)/2;}
	 else {break;}
	}
	return l;
}

int ExtractMin( vector <int> &heap, vector <int> &min , vector < vector <int> > &values, vector <int> &node_heap_pos){
	int vertex = heap[0];
	node_heap_pos[vertex]=1000000;
	int size = heap.size();
	heap[0] = heap[size-1];
	node_heap_pos[heap[size-1]]=0;
	heap.resize(size-1);
	int l=0;
	delete_swap(heap,min,node_heap_pos,l);


	for(int i=0; i<values[vertex].size();i+=2){
	    int hold = 1000000;	
		hold= node_heap_pos[values[vertex][i]];
	        int index = hold;
		int value;
	        if(index != 1000000){
	           value = heap[hold];
		   node_heap_pos[heap[heap.size()-1]]=index;
	           heap[index] = heap[heap.size()-1];
	           heap.resize(heap.size()-1);

		   index = heap_delete_balancing_bubbleup(heap,min,node_heap_pos,index);
		   delete_swap(heap,min,node_heap_pos,index);   
		   if(min[value] > values[vertex][i+1]){	  	
       	           min[value] = values[vertex][i+1];}
	           heapInsert(heap,min,node_heap_pos,value);  

    	        }
        }
	return vertex;		 
}				  	
	

int main (){

ifstream in("edges.txt");
int nodes,edges,edges1;
in>>nodes>>edges;
vector < vector<int> > values;  
edges1=edges;
 
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
vector <int> node_heap_pos(nodes+1);
node_heap_pos[1] = 1000000;

for(int u =2 ;u<=nodes;u++){
     int dis = 1000000;	
     for(int i =0; i<values[1].size();i+=2){
	 if(u == values[1][i]){dis = values[1][i+1];break;}} 	
	 min[u] = dis;
     heapInsert(heap,min,node_heap_pos,u);	
}

int no = nodes-1; int temp3;
while(no>0)
    { temp3 = ExtractMin(heap,min,values,node_heap_pos);no--;}

long long int sum=0;
for(int i=2;i<=min.size()-1;i++){
    sum+=min[i];}	
cout<<sum<<endl;

in.close();
return 0;
}

// The answer of PA1.3 is -3612829
