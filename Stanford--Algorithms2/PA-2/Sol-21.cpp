// The question is to find the min distance from the remaining edges when there are only 4 clusters left
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main (){

ifstream in("clustering1.txt");
int number;
in>>number;
vector < vector<int> > edges;
int v;
while(in>>v){ int w,l;
	in >>w>>l;;
        vector <int> row;
	edges.push_back(row);
	edges[edges.size()-1].push_back(l);
	edges[edges.size()-1].push_back(v);
	edges[edges.size()-1].push_back(w);
	}

sort(edges.begin(),edges.end());

vector < vector <int> > nodes;
for(int k=0; k<=number;k++){
  vector <int> row;
  nodes.push_back(row);}

for(int k=1; k<=number;k++){
  nodes[k].push_back(k);}

vector <int> vertices;
for(int k=0; k<=number;k++){
  vertices.push_back(k);}

int control =0;
int dis;
for(int j=0; j<edges.size(); j++){
    if(control > number-5){ 
	if (vertices[edges[j][1]] != vertices[edges[j][2]]){
	  dis = edges[j][0];break;	
	}
      }
    else {int t1 = vertices[edges[j][1]];
    int t2 = vertices[edges[j][2]];
      if (t1 != t2){
        if(nodes[t1].size() >= nodes[t2].size()){
	    for(int i=0;i < nodes[t2].size();i++){
                vertices[nodes[t2][i]] = vertices[nodes[t1][0]];
		nodes[t1].push_back(nodes[t2][i]);} }
        else {
	    for(int i=0;i < nodes[t1].size();i++){
                vertices[nodes[t1][i]] = vertices[nodes[t2][0]];
		nodes[t2].push_back(nodes[t1][i]);} }
		
	control++;
	} }
    }

cout<<dis<<endl;
in.close();

return 0;
}
// The answer to PA2.1 is 106
