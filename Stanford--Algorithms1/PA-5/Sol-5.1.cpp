//Straightforward implementation (without heaps)

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main (){

ifstream in("dijkstraData.txt");
int number;
int number1;
vector < vector<int> > values1; 
vector < vector<int> > values2; 
string line;
string hold;
int temp;

for(int k=0; k<201;k++){
  vector <int> row;
  values1.push_back(row);	
  values2.push_back(row);	
}

int i=0;
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
int total =0;

for ( i=1; i<201; i++){
	for(int j=0; j<values1[i].size() ; j++)
		total++;	
}

vector < vector<int> > edges;
for(int l=0; l<3734;l++){
  vector <int> row1;
  edges.push_back(row1);	
}


int y=0;
for ( i=1; i<201; i++){
	for(int j=0; j<values1[i].size() ; j++)
	{	edges[y].push_back(i);
		edges[y].push_back(values1[i][j]);
		j++;
		edges[y].push_back(values1[i][j]);
		y++;
	}	
}

int f,g;
for( f=0;f< edges.size();f++){
	if(edges[f][0] > edges[f][1]){
	int temp;
	temp = edges[f][1];
	edges[f][1] = edges[f][0];
	edges[f][0] = temp;}
}

sort(edges.begin(),edges.end());     
edges.erase(unique(edges.begin(),edges.end()),edges.end());     
/*
for( f=0;f< edges.size();f++){
	for(g=0; g<edges[f].size();g++){
		cout<<edges[f][g]<<" ";}
	cout<<"\n";
}*/

vector <int> check (201);
vector <int> min (201);
check[1] = 1;
min[1] = 0;
int counter = 1;

while(counter <201){

int lowest = 1000000;
int hold;

for( int q=0; q<edges.size();q++){
  if ( ((check[edges[q][0]] == 1) && (check[edges[q][1]] == 0)) || ((check[edges[q][0]] == 0) && (check[edges[q][1]] == 1))){
       if(check[edges[q][0]] == 1){	
	if (edges[q][2] + min[edges[q][0]] <= lowest){
		lowest = edges[q][2] + min[edges[q][0]];
		hold = q;}}
       else if(check[edges[q][1]] == 1){	
	if (edges[q][2] + min[edges[q][1]] <= lowest){
		lowest = edges[q][2] + min[edges[q][1]];
		hold = q;}}
	
	}
	}
  if(lowest == 1000000){break;}

  if( check[edges[hold][0]] == 0){
      min[edges[hold][0]] = lowest ;
      check[edges[hold][0]] = 1 ; counter++;}
   else if (check[edges[hold][1]] == 0){
      min[edges[hold][1]] = lowest ;
      check[edges[hold][1]] = 1 ; counter++;}
}

cout<<min[7]<<",";
cout<<min[37]<<",";
cout<<min[59]<<",";
cout<<min[82]<<",";
cout<<min[99]<<",";
cout<<min[115]<<",";
cout<<min[133]<<",";
cout<<min[165]<<",";
cout<<min[188]<<",";
cout<<min[197];

in.close();

return 0;
}

//Answer PA-5:   2599,2610,2947,2052,2367,2399,2029,2442,2505,3068  
