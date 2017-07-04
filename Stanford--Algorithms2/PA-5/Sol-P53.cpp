// Tried to optimise the second solution by resizing the array. However it takes more time 1077 seconds

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

//void combo_also_print(int nodes, int r , int start , int j, vector <int> &val, vector <vector <float> > &dis, float (&arr)[131072][17]){
void combo_also_print(int nodes, int r , int start , int j, vector <int> &val, bitset <24> &val1, vector <vector <float> > &dis, vector <vector <float> >&arr, vector <vector <float> >&barr){
  if(r==0){
     float lowest = 32000; 

     for(int i=0;i<val.size();i++){
	if(arr[val1.to_ulong()][val[i]-2] + dis[j][val[i]] <=lowest){ lowest = arr[val1.to_ulong()][val[i]-2] + dis[j][val[i]];}
	}	  
	
	val1[j-2] =1;
	barr[val1.to_ulong()][j-2] = lowest;
     return; 
  }

  for(int i=start;i<=nodes-r+1;i++){
     if(i==j){continue;}
     vector <int> loop;
     bitset <24> loop1;
     loop1 = val1;
     loop = val;
     loop.push_back(i);
     loop1[i-2]=1;	
     combo_also_print(nodes,r-1,i+1,j,loop,loop1,dis,arr,barr);}
}

//void combo_recur (int nodes, int r, int start, int j, vector <vector <float> > &dis, float (&arr)[131072][17]){
void combo_recur (int nodes, int r, int start, int j, vector <vector <float> > &dis, vector <vector <float> > &arr, vector <vector <float> >&barr){
  for(int i=start;i<=nodes-r+1;i++){
     if(i==j){continue;}
     bitset <24> val1;
     vector <int> val;
     val.push_back(i);		
     val1[i-2]=1;
     combo_also_print(nodes,r-1,i+1,j,val,val1,dis,arr,barr);}
}

int main (){

ifstream in("tsp.txt");
int nodes;
in>>nodes;

//unsigned long long ind1 = pow(static_cast<double>(2),nodes-1);
//cout <<ind1;
//const int index = nodes-1;
//float arr [131072][17];
vector <unsigned long> sizes(nodes+1);
for(int i=nodes;i>=1;i--){
if(i==nodes){ sizes[i] = pow(static_cast<double>(2),i);}
else { sizes[i] = sizes[i+1] + pow(static_cast<double>(2),i);}
}

vector < vector <float> > arr (sizes[nodes-1]+1, vector <float> (24));

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
vector < vector <float> > barr (sizes[nodes-1-g]+1, vector <float> (24));
  for(int j=2;j<=nodes;j++){
    combo_recur(nodes,g,2,j,dis,arr,barr);
  }
arr = barr;
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

// the correct answer is 26442 and takes 1077.20 sec
