// Improved version using Gosper's hack reduced the time on Adi Macbook to 2m 45 seconds.
// The end vertex calls were removed from the main. The different final vertex calculations now made from the function itself.
// This reduces wastage by a lot.

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <math.h>

using namespace std;

vector < vector <float> > arr (16777216, vector <float> (24));
vector < vector <float> > dis (26, vector <float> (26));

void combo_recur (int nodes,unsigned long &last, unsigned long first){

    unsigned long y,c,next;

     while (first != last){
       y = first & -first;
       c = first + y;
       next = (((first ^ c) >> 2)/y) | c;
  
       bitset <24> hold = first;

        vector <int> val;
	      vector <int> ter;
        for(int i=0;i<24;i++){
  	    if(hold[i]==1){ val.push_back(i+2);}
	      else { ter.push_back(i+2);}
         }

        for(int t=0;t<ter.size();t++){
      	bitset <24> temp =hold;
	      int j = ter[t];     
        float lowest = 32000; 
        for(int i=0;i<val.size();i++){
  	    if(arr[first][val[i]-2] + dis[j][val[i]] <=lowest){ lowest = arr[first][val[i]-2] + dis[j][val[i]];}
  	    }
      	temp[j-2] =1;
  	    arr[temp.to_ulong()][j-2] = lowest;
       }

	
       first = next;   
     }

     if (first == last){
        bitset <24> hold = first;
        vector <int> val;
	      vector <int> ter;
        for(int i=0;i<24;i++){
      	if(hold[i]==1){ val.push_back(i+2);}
	      else { ter.push_back(i+2);}
         }

        for(int t=0;t<ter.size();t++){
	      bitset <24> temp =hold;
	      int j = ter[t];     
        float lowest = 32000; 
        for(int i=0;i<val.size();i++){
  	    if(arr[first][val[i]-2] + dis[j][val[i]] <=lowest){ lowest = arr[first][val[i]-2] + dis[j][val[i]];}
      	}
  	    temp[j-2] =1;
  	    arr[temp.to_ulong()][j-2] = lowest;
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
 unsigned long last = sizes[nodes-1-g];
 unsigned long first = sizes2[g-1]; 
 combo_recur(nodes,last,first); 
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
