// This is the implementation of all pair shortest path using Johnson's algorithm
// The running time is roughly 8.6 seconds
// Here the graphs g1 and g2 have negative edge cycle. Thus the algorithm is run on g3 and it outputs the result.
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


void heapInsert( vector <int> &heap, vector <long> &min , vector <long> &node_heap_pos, int u){
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

void delete_swap(vector <int> &heap, vector <long> &min , vector <long> &node_heap_pos, int start){
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

int heap_delete_balancing_bubbleup(vector <int> &heap, vector <long>&min , vector <long> &node_heap_pos, int start){
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

int ExtractMin( vector <int> &heap, vector <long> &min , vector < vector <int> > &values, vector <long> &node_heap_pos){
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
		   if(min[value] > min[vertex] + values[vertex][i+1]){	  	
       	           min[value] = min[vertex] + values[vertex][i+1];}
	           heapInsert(heap,min,node_heap_pos,value);  

    	        }
        }
	return vertex;		 
}


int main (){

ifstream in("g3.txt");
long nodes;
long edges;
in>>nodes>>edges;
vector < vector<int> > adj (nodes+1);
vector < vector<int> > adj_inv (nodes+1);

int t;
while(in>>t){ int h,l;
	in >>h>>l;;
	adj[t].push_back(h);
	adj_inv[h].push_back(t);
	adj[t].push_back(l);
	adj_inv[h].push_back(l);
	}

for(int i=1;i<=nodes;i++){
adj[0].push_back(i);
adj[0].push_back(0);
adj_inv[i].push_back(0);
adj_inv[i].push_back(0);}

vector < vector<int> > bford (nodes+1);

// Bellman-Ford on the vertices using the extra zero vertex as the source
bford[0].push_back(0);
for(int i=0;i<nodes;i++){
	bford[0].push_back(20000);}

for(int i=1;i<=nodes;i++){
  for(int j=0;j<=nodes;j++){
	 int l1 = bford[i-1][j];
	 for(int k=0;k<adj_inv[j].size();k+=2){
		if(bford[i-1][adj_inv[j][k]] + adj_inv[j][k+1] < l1){ l1 = bford[i-1][adj_inv[j][k]] + adj_inv[j][k+1];}
	 }
	 bford[i].push_back(l1);}
}  	 	

//check for negative edge cycle
int neg_edge_cycle=0;
if( bford[nodes-1] != bford[nodes]){ neg_edge_cycle=1;}
//cout<<neg_edge_cycle;
// The code is terminated if the output is 1 else the shortest path is computed


// Updating the path lengths in the graph with non-negative values
for(int i=1;i<=nodes;i++){
   for(int j=0;j<adj[i].size();j+=2){
	adj[i][j+1] = adj[i][j+1] + bford[nodes-1][i] - bford[nodes-1][adj[i][j]];}
   }	


// Implementing Djitsra's shortest path on all the n vertices iteratively to compute the all pair shortest paths.

vector < vector<long> > minf(nodes+1);

for(int d1 = 1;d1 <=nodes;d1++){

  vector <int> heap;
  vector <long> min(nodes+1);
  vector <long> node_heap_pos(nodes+1);
  node_heap_pos[d1] = 1000000;
  min[d1]=0;
  for(int u =1 ;u<=nodes;u++){
      int dis = 1000000;	
      for(int i =0; i<adj[d1].size();i+=2){
    	  if(u == adj[d1][i]){dis = adj[d1][i+1];break;}} 	
	  if (u!=d1){ min[u] = dis;
          heapInsert(heap,min,node_heap_pos,u);	}
  }

  int no = nodes-2; int temp3;
  while(no>0)
     { temp3 = ExtractMin(heap,min,adj,node_heap_pos);no--;}
  
  minf[d1] = min;

}

int res = 32000;

for(int i=1;i<minf.size();i++){
  for(int j=1;j<minf[i].size();j++){
	if(i!=j){
	    minf[i][j] = minf[i][j] -bford[nodes-1][i] + bford[nodes-1][j];
	    if(minf[i][j] <res){ res = minf[i][j];}

	}
  }
}
cout<<res<<endl;

in.close();

return 0;
}
// The answer to PA4 is -19
