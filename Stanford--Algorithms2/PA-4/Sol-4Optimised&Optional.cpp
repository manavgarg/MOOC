// To compute the shortest shortest all pair path, djistra's algo is not needed. Computing Belllman-ford with a new source vertex is enough
// This solution speeds up the solution by a huge margin as we are not required to implement the entire Johnson Algorithm.
// Also, by implementing early exit of Bellman-Ford, the running time can be improved firther
// The running time for optional problem is 1.42 s and to PA4 is 0.05 seconds
// The running time is roughly 1.2 seconds for PA4 with only Bellman ford and without early exit
// Here the graphs g1 and g2 have negative edge cycle. Thus the algorithm is run on g3 and it outputs the result.
// With early Bellman Ford termination, the large graph exits after 30 iterations, g3 after 27 iterations.
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int main (){

ifstream in("large.txt");
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

int res=32000;
int terminate=nodes+1;
for(int i=1;i<=nodes;i++){
  for(int j=0;j<=nodes;j++){
	 int l1 = bford[i-1][j];
	 for(int k=0;k<adj_inv[j].size();k+=2){
		if(bford[i-1][adj_inv[j][k]] + adj_inv[j][k+1] < l1){ l1 = bford[i-1][adj_inv[j][k]] + adj_inv[j][k+1];}
	 }
	 if(res>l1){res=l1;}
	 bford[i].push_back(l1);}

 if(bford[i] == bford[i-1]){terminate =i;break;}
}  	 	

//check for negative edge cycle
int neg_edge_cycle=0;
if(terminate == nodes+1){
 if( bford[nodes-1] != bford[nodes]){ neg_edge_cycle=1;}
}

if(!neg_edge_cycle){
 cout<<res<<" "<<terminate<<endl;}
else { cout<<"Neg Edge Cycle Exists";}

in.close();

return 0;
}
// The answer to PA4 is -19
// The answer of the optional exercise is -6
