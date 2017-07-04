#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

 int finish_time =1;
vector <int> check_r(875715); 
vector <int> check_f(875715); 
vector <int> finish_count(875715);    // holds the node value based on the finish_time which is the vector index

void dfs_reverse( int r, vector < vector<int> > &values2){
	if ( check_r[r] == 1){ return ;}
	
	if ( check_r[r] != 1){
	check_r[r] = 1;
	for (int z=0; z < values2[r].size(); z++){
	    dfs_reverse(values2[r][z] , values2);
	
		}
	finish_count[finish_time] = r;
	finish_time++;
	return;
	}	
	}

void dfs_forward( int f, vector < vector<int> > &values1, int &leader){
	if ( check_f[f] == 1){ return ;}
	if ( check_f[f] != 1){ 
	leader++;
	check_f[f] =1;
	for (int y=0; y <values1[f].size(); y++){
		dfs_forward(values1[f][y] , values1,leader);}
	check_f[f] =1;
	return;
	}
	}


int main (){

ifstream in("SCC.txt");
int number;
int number1;
vector < vector<int> > values1;  // holds the edges based on index of the original graph
vector < vector<int> > values2;  // holds the edges based on index of the reversed graph

for(int k=0; k<875715;k++){
  vector <int> row;
  values1.push_back(row);	
  values2.push_back(row);}	

int i=0;
while(in >> number){
	in >> number1;
	values1[number].push_back(number1);
	values2[number1].push_back(number);
	i++;}

// Calling the First DFS loop on the reversed graph
for(int r=1; r<values2.size();r++){
dfs_reverse(r, values2);}

vector <int> sizescc(5);
// Calling the second DFS loop based on finish time and calculting size of 5 largest SCC
for(int f = finish_time-1; f > 0; f--){
int track = finish_count[f];
int leader =0;
dfs_forward(track, values1, leader);
for( int b=0;b<5;b++){
if(leader >= sizescc[b]){
sizescc.insert(sizescc.begin()+b,leader);
break;}
}
sizescc.resize(5);
}  

for (int q =0; q<sizescc.size(); q++){
	cout <<"size : "<<sizescc[q]<<endl;}

in.close();

return 0;
}


// The answer of PA-4 is :  434821,968,459,313,211
