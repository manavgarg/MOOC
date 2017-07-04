// Implemented using vectors. Takes 454 seconds for the PA to output the result
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <math.h>
#include <tr1/unordered_map>
using namespace std;

//void combo_also_print(int nodes, int r , int start , int j, vector <int> &val, vector <vector <float> > &dis, float (&arr)[131072][24]){
void combo_also_print(int nodes, int r , int start , int j, vector <int> &val, vector <vector <float> > &dis, vector <vector <float> >&arr){
  if(r==0){
     float lowest = 32000; 
     bitset <24> s;
     for(int k=0;k<val.size();k++){
	s[val[k]-2] = 1;
	}

     for(int i=0;i<val.size();i++){
	if(arr[s.to_ulong()][val[i]-2] + dis[j][val[i]] <=lowest){ lowest = arr[s.to_ulong()][val[i]-2] + dis[j][val[i]];}
	}	  
	
	s[j-2] =1;
	arr[s.to_ulong()][j-2] = lowest;
     return; 
  }

  for(int i=start;i<=nodes-r+1;i++){
     if(i==j){continue;}
     vector <int> loop;
     loop = val;
     loop.push_back(i);
     combo_also_print(nodes,r-1,i+1,j,loop,dis,arr);}
}

//void combo_recur (int nodes, int r, int start, int j, vector <vector <float> > &dis, float (&arr)[131072][24]){
void combo_recur (int nodes, int r, int start, int j, vector <vector <float> > &dis, vector <vector <float> > &arr){
  for(int i=start;i<=nodes-r+1;i++){
     if(i==j){continue;}
     vector <int> val ;
     val.push_back(i);
     combo_also_print(nodes,r-1,i+1,j,val,dis,arr);}
}

int main (){

ifstream in("tsp.txt");
int nodes;
in>>nodes;

//unsigned long long ind1 = pow(static_cast<double>(2),nodes-1);
//cout <<ind1;
//const int index = nodes-1;
//float arr [131072][24];
vector < vector <float> > arr (16777216, vector <float> (24));

vector < vector <float> >vertex (nodes+1);
for(int i=1;i<=nodes;i++){
float a,b;
in>>a>>b;
vertex[i].push_back(a);
vertex[i].push_back(b);}

vector < vector <float> > dis (nodes+1, vector <float> (nodes+1));
for(int i=1;i<=nodes;i++){
  for(int j=i;j<=nodes;j++){
	if(j==i){dis[i][j] =0;}
	else {
	      float temp1,temp2,res;
	      temp1 = pow((vertex[i][0]-vertex[j][0]),2);		
	      temp2 = pow((vertex[i][1]-vertex[j][1]),2);		
	      res= sqrt(temp1+temp2);
	      dis[i][j] = res;
	      dis[j][i] = res;	
	     }
   }
}

for(int i=2;i<=nodes;i++){
  bitset <24> s;
  s[i-2] =1; 
  arr[s.to_ulong()][i-2] = dis[1][i];
}		



for(int g=1;g<nodes-1;g++){
  for(int j=2;j<=nodes;j++){
    combo_recur(nodes,g,2,j,dis,arr);
  }
}

float result = 32000;
bitset <24> last;
last.set();
for(int i=2;i<=nodes;i++){
   arr[last.to_ulong()][i-2] = arr[last.to_ulong()][i-2] + dis[1][i];
   if(arr[last.to_ulong()][i-2] <= result){ result = arr[last.to_ulong()][i-2];}
}
cout<<result<<endl;  

in.close();
return 0;
}

// Sol is 26442 in 454 seconds
