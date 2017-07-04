// Implemented it using Gosper's hack. Also, the recursive version is giving segmentation fault. Hence implemented it iteratively inside the combo_recur function.
// Also, the real times reported till now for all the programming assignments till now were on Intel's unix server. On Adi's Mac the real time reported was between 9.5 and 11 minutues. Also, on the same Mac, the time taken by the previous version (Sol-P54.cpp) is roughly 12-15 minutes. So this implementation reports a slghtly better performance.

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <math.h>
//#include <map>
using namespace std;

vector < vector <float> > arr (16777216, vector <float> (24));
vector < vector <float> > dis (26, vector <float> (26));

void combo_recur (int nodes, int j,unsigned long &last, unsigned long first){

     unsigned long y,c,next;

     while (first != last){
       y = first & -first;
       c = first + y;
       next = (((first ^ c) >> 2)/y) | c;
  
       bitset <24> hold = first;

       if(hold[j-2] != 1){
        vector <int> val;
        for(int i=0;i<24;i++){
  	if(hold[i]==1){ val.push_back(i+2);}
         }	     
        float lowest = 32000; 
        for(int i=0;i<val.size();i++){
  	if(arr[first][val[i]-2] + dis[j][val[i]] <=lowest){ lowest = arr[first][val[i]-2] + dis[j][val[i]];}
  	}
  	hold[j-2] =1;
  	arr[hold.to_ulong()][j-2] = lowest;
       }	
       first = next;   
     }

     if (first == last){
        bitset <24> hold = first;

        if(hold[j-2] != 1){
        vector <int> val;
        for(int i=0;i<24;i++){
  	if(hold[i]==1){ val.push_back(i+2);}
         }	     
        float lowest = 32000; 
        for(int i=0;i<val.size();i++){
  	if(arr[first][val[i]-2] + dis[j][val[i]] <=lowest){ lowest = arr[first][val[i]-2] + dis[j][val[i]];}
  	}
  	hold[j-2] =1;
  	arr[hold.to_ulong()][j-2] = lowest;
        }	
     }

}

int main (){

ifstream in("tsp.txt");
int nodes;
in>>nodes;

vector <unsigned long> sizes(nodes-1);
for(int i=nodes-2;i>=1;i--){
if(i==nodes-2){ sizes[i] = pow(static_cast<double>(2),i);}
else { sizes[i] = sizes[i+1] + pow(static_cast<double>(2),i);}
}

vector <unsigned long> sizes2(nodes-1);
for(int i=0;i<nodes-1;i++){
if(i==0){ sizes2[i] = pow(static_cast<double>(2),i);}
else { sizes2[i] = sizes2[i-1] + pow(static_cast<double>(2),i);}
}

vector < vector <float> >vertex (nodes+1);
for(int i=1;i<=nodes;i++){
float a,b;
in>>a>>b;
vertex[i].push_back(a);
vertex[i].push_back(b);}

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
 unsigned long last = sizes[nodes-1-g]; //cout<<last<< " "<<endl;
 unsigned long first = sizes2[g-1]; 
  for(int j=2;j<=nodes;j++){
    combo_recur(nodes,j,last,first); //cout<<g<<":"<<j<<endl;
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

// The output is 26442.7
