// The 2-SAT problem is solved by reducing it to find the strongly connected components.
// Solution is heavily borrowed from the Kosaraju's 2 part soln as written in course 1
// Here for every 2-SAT clause, 2 edged are added. For every variable, 2 vertex are added.
// The edges for a clause (x  or y) are - {~x->y} & {~y->x}
// Here for 6 differnt txt files, only the three values are changed in the initialisation of check_r, check_f & finish_count. These are twice the no of vertices
// The time taken for the largest txt file (2sat6.txt) is approximately 14 secs

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int finish_time =1;
int exit_status =1;
vector <int> check_r(2000001); 
vector <int> check_f(2000001); 
vector <long> finish_count(2000001);    // holds the node value based on the finish_time which is the vector index

void dfs_reverse( long r, vector < vector<long> > &values2){
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

void dfs_forward( long track, vector < vector<long> > &values1, long f, long vertices){
	if ( check_f[track] != 0){ return ;}
	if ( check_f[track] == 0){ 
	check_f[track] =f;
	if(track > vertices){ if(check_f[track -vertices] == f) {exit_status=0;} }
	if(track <= vertices){ if(check_f[track + vertices] == f) {exit_status=0;} }

	for (int y=0; y <values1[track].size(); y++){
		dfs_forward(values1[track][y] , values1,f, vertices);}
	check_f[track] =f;
	return;
	}
	}


int main (){

ifstream in("2sat6.txt");
long vertices;
long number;
long number1;
long e1;
long e2;

vector < vector<long> > val_first;  // holds the edges based on index of the original graph
vector < vector<long> > val_rev;  // holds the edges based on index of the reversed graph

in>>vertices;


for(int k=0; k<=2*vertices;k++){
  vector <long> row;
  val_first.push_back(row);	
  val_rev.push_back(row);	
  }



while(in >> number){
	in >> number1;
	if(number <0){
	  number = vertices + abs(number);	
	}
	
	if(number1 <0){
	  number1 = vertices + abs(number1);
	}
	if(number > vertices){ e1 = number -vertices;}
	else{ e1 = vertices + number;}
	if(number1 > vertices){ e2 = number1 -vertices;}
	else{ e2 = vertices + number1;}
	
	val_first[e1].push_back(number1);
	val_first[e2].push_back(number);
	val_rev[number1].push_back(e1);
	val_rev[number].push_back(e2);
	}

// Calling the First DFS loop on the reversed graph
for(long r=1; r<val_rev.size();r++){
dfs_reverse(r, val_rev);}


// Calling the second DFS loop based on finish time and calculting size of 5 largest SCC
for(long f = finish_time-1; f > 0; f--){
long track = finish_count[f];
dfs_forward(track, val_first,f,vertices);
}  

cout<<exit_status;
in.close();

return 0;
}

// The solution to PA-6 is 101100

