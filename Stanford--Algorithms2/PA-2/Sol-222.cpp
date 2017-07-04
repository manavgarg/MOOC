//Flow:
// Use unordered_map to store the node keys. The value is whether the node has been visited or not (bool)
// 300 XTOR patterns are generated for all sum of hamming distances 1 and 2
// BFS is run from the  first map value and each node is checked for 300 patterns.
// The no of clusters are the total connected components
// Running time is better than previous implementation. It is 8.54 seconds

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <deque>
#include <map>
#include <tr1/unordered_map>
using namespace std;

int main (){

ifstream in("clustering_big.txt");
int number, bits;
in >>number>>bits;

vector < bitset<24> > nodes;

std::tr1::unordered_map <unsigned long , bool> m;
string line;
while (getline(in,line)){
	bitset <24> row;
	stringstream stream(line);
	int j=0;
	bool n;
         while (stream >>n){
	    row[j]=n;j++;
	}
   if(m.find(row.to_ulong()) == m.end()){	
   m[row.to_ulong()]=0;
   nodes.push_back(row);
   }	
   }
/*********************************Generating XOR Patterns***********************************/
vector < bitset<24> > xors;
for(int i=0;i<=300;i++){
bitset <24> row;
xors.push_back(row);}

for(int i=0;i<bits;i++){
  for(int j=0;j<bits;j++){
      if(i == j){xors[i][j]=1;}   
      else {xors[i][j] =0;}   
  }
}	

int num=bits;
for(int i=0;i<bits;i++){
 for(int k=i+1;k<bits;k++){
  for(int j=0;j<bits;j++){
      if(i == j || k==j){xors[num][j]=1;}   
      else {xors[num][j]=0;}   
  }
  num++;	
 }
}

/*********************************** BFS ****************************************************/

long long int clusters=0;
 for (std::tr1::unordered_map<unsigned long,bool>::iterator it=m.begin(); it!=m.end(); ++it){
  if(it->second != 1){ 
	it->second = 1;
	clusters++;
    	deque < unsigned long > cc;
	cc.push_back(it->first);
	bitset <24> j= cc.front();
	   while(cc.size()){cc.pop_front();
		for(int k=0;k<xors.size();k++){
		       bitset <24> check_xor;	      
      		       check_xor = j^xors[k]; 
	      	       int temp;
      			if (m.find(check_xor.to_ulong()) != m.end()){ 
				if (m[check_xor.to_ulong()] !=1){ cc.push_back(check_xor.to_ulong());m[check_xor.to_ulong()]=1;}
				}
			}
			 if(cc.size()!=0){j=cc.front();}
			}
		 	
   }
}
cout<<clusters<<endl;


in.close();

return 0;
}

// The correct answer to PA2.2 is 6118
