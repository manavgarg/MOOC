//Flow:
// Use map to store the node keys. The value is whether the node has been visited or not (bool)
// 300 XTOR patterns are generated for all sum of hamming distances 1 and 2
// BFS is run from the  first map value and each node is checked for 300 patterns.
// The no of clusters are the total connected components
// Running time is more than the improved version of unordered_map due to extra time in sorting implementation. It is 45.64 seconds

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

struct Comparer {
    bool operator() (const bitset<24> &b1, const bitset<24> &b2) const {
        return b1.to_ulong() < b2.to_ulong();
    }
};

int main (){

ifstream in("clustering_big.txt");
int number, bits;
in >>number>>bits;

vector < bitset<24> > nodes;

map <bitset<24> , bool, Comparer> m;
string line;
while (getline(in,line)){
	bitset <24> row;
	stringstream stream(line);
	int j=0;
	bool n;
         while (stream >>n){
	    row[j]=n;j++;
	}
   if(m.find(row) == m.end()){	
   m[row]=0;
   nodes.push_back(row);
   }	
   }
/*********************************Generating XOR Patterns********************************/
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

/******************************************************************************************/

long long int clusters=0;
 for (map<bitset<24>,bool>::iterator it=m.begin(); it!=m.end(); ++it)
  if(m[nodes[i]] != 1){ 
	m[nodes[i]] = 1;
	clusters++;
    	deque < bitset<24> > cc;
	cc.push_back(nodes[i]);
	bitset <24> j= cc.front();
	   while(cc.size()){cc.pop_front();
		for(int k=0;k<xors.size();k++){
		       bitset <24> check_xor;	      
      		       check_xor = j^xors[k]; 
	      	       int temp;
      			if (m.find(check_xor) != m.end()){ 
				if (m[check_xor] !=1){ cc.push_back(check_xor);m[check_xor]=1;}
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
