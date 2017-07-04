#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

unsigned long long int counter =0;

int mincut(vector < vector<int> > &edges , vector <int> &nodes){
	
	if(nodes.size() == 2){
       		return edges.size();}


	int no_edges = edges.size();
	int num = rand() % (no_edges);
	int nd1 = edges[num][0];
	int nd2 = edges[num][1];
     //    cout <<num <<endl;
	for( int i=0;i < edges.size();i++){
		if ( edges[i][0] ==  nd2){
			edges[i][0] = nd1;}

		if ( edges[i][1] ==  nd2){
			edges[i][1] = nd1;}
	}
 
	for (int j=0; j< edges.size();j++){
		if ( edges[j][0] == edges[j][1]){
		     edges.erase(edges.begin()+j);
		     j--;
			   }
		}

	for (int k=0; k< nodes.size();k++){
		if ( nd2 == nodes[k]){
		       nodes.erase(nodes.begin()+k);}
		  }


	return mincut(edges,nodes);
	}                              

int main (){

ifstream in("kargerMinCut.txt");
int number;
vector < vector<int> > values;
int i =0;
string line;
for(int h=0; h<200;h++){
	vector <int> row;
	values.push_back(row);}
int total=0;
while (getline(in,line)){
	stringstream stream(line);
	int j=0;
	int n;
         while (stream >>n){
	    values[i].push_back(n);
	    j++;  
		total++;   
	}
	i++;
}

cout << total <<endl;

vector <int> nodes;
vector < vector <int> > edges (total-200);

int edge_row =0;
for (int w=0; w<values.size();w++){
	int e =1;
	for (e; e<values[w].size();e++){
	         edges[edge_row].push_back(values[w][0]);
		 edges[edge_row].push_back(values[w][e]);
	         edge_row++;
	    }
        }

for (int q= 0 ; q<values.size();q++){
	nodes.push_back(values[q][0]);}

// To sort edges  
for (int r =0; r <edges.size(); r++){
	if (edges[r][1] < edges[r][0]){
		int temp = edges[r][1];
		edges[r][1] = edges[r][0];
		edges[r][0] = temp;
	}
}           

// To remove duplicates (edges present in the initial list)
 sort(edges.begin(),edges.end());     
 edges.erase(unique(edges.begin(),edges.end()),edges.end());      

int cuts;
int lowest = 2517;

for(int times=0; times < 400; times++){
vector <int> nodes1;
vector < vector <int> > edges1 ((total-200)/2);
edges1 = edges;
nodes1 = nodes;
//cout<<"end"<<times;

cuts = mincut(edges1,nodes1);
//cout <<cuts<<endl;
if (cuts < lowest) lowest = cuts;}
// To display the nodes
/*for (int y =0; y<nodes.size();y++){
	   cout << nodes[y] <<endl;}     
*/

// To display the edges ( 2x times the number i.e. with duplicates
/*for( int k=0; k<edges.size(); k++){
	cout << edges[k][0] <<" " ;	
	cout << edges[k][1];	
	cout << endl ;}  */
cout <<lowest<<endl;
   

in.close();



return 0;
}


//P3: The answer is 17
// The number of iterations can be changed to 400 to get the correct answer. Acc to lectures, you are supposed to run till 40000, but the limit can be changed to 400.



