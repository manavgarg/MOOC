//Implemented using Maps. Is working for 18 set data, taking a huge time for the given input values


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <tr1/unordered_map>
using namespace std;

std::tr1::unordered_map <string, double> m;
void combo_also_print(int nodes, int r , int start , int j, vector <int> &val, vector <vector <long double> > &dis){
  if(r==0){
     long double lowest = 32000; 
     for(int i=0;i<val.size();i++){
        stringstream s;
         if(val.size() != 1){for(int k=0;k<val.size();k++){
	   if(k==i){continue;} 
	   s<<val[k]<<"+";
	   }
	   }
	   s<<val[i];
	   if(m[s.str()] + dis[j][val[i]] <=lowest){ lowest = m[s.str()] + dis[j][val[i]];}
	}	  
	
     stringstream final; 	
     for(int i=0;i<val.size();i++){
	final<<val[i]<<"+";
	}
	final<<j;
	m[final.str()] = lowest;
     return; 
  }

  for(int i=start;i<=nodes-r+1;i++){
     if(i==j){continue;}
     vector <int> loop;
     loop = val;
     loop.push_back(i);
      combo_also_print(nodes,r-1,i+1,j,loop,dis);}
}

void combo_recur (int nodes, int r, int start, int j, vector <vector <long double> > &dis){
  for(int i=start;i<=nodes-r+1;i++){
     if(i==j){continue;}
     vector <int> val ;
     val.push_back(i);
     combo_also_print(nodes,r-1,i+1,j,val,dis);}
}

int main (){

ifstream in("tsp2.txt");
long nodes;
in>>nodes;

vector < vector <long double> >vertex (nodes+1);
for(int i=1;i<=nodes;i++){
long double a,b;
in>>a>>b;
vertex[i].push_back(a);
vertex[i].push_back(b);}

vector < vector <long double> > dis (nodes+1, vector <long double> (nodes+1));
for(int i=1;i<=nodes;i++){
  for(int j=i;j<=nodes;j++){
	if(j==i){dis[i][j] =0;}
	else {
	      long double temp1,temp2,res;
	      temp1 = pow((vertex[i][0]-vertex[j][0]),2);		
	      temp2 = pow((vertex[i][1]-vertex[j][1]),2);		
	      res= sqrt(temp1+temp2);
	      dis[i][j] = res;
	      dis[j][i] = res;	
	     }
   }
}

for(int i=2;i<=nodes;i++){
  stringstream u;
  u<<i;
  m[u.str()] = dis[1][i];
}		



for(int g=1;g<nodes-1;g++){
  for(int j=2;j<=nodes;j++){
    combo_recur(nodes,g,2,j,dis);
  }
}

long double result = 32000;
for(int i=2;i<=nodes;i++){
   stringstream last;	
   for(int j=2;j<=nodes;j++){
	if(i==j){continue;}
	last <<j<<"+";
	}
   last<<i;
   m[last.str()] = m[last.str()] + dis[1][i];
   if(m[last.str()] <= result){ result = m[last.str()];}
   //cout<<last.str()<<" "<<m[last.str()]<<endl;		
}
//for(std::tr1::unordered_map <string, double> ::iterator it = m.begin(); it != m.end(); ++it) {
//  cout <<it->first<<" "<<m[it->first]<<"\n";
//}
cout<<result<<endl;  	

//for(int i=1;i<=nodes;i++){
//for(int j=1;j<=nodes;j++){
//cout<<dis[i][j]<< " ";}cout<<endl;}

in.close();
return 0;
}
