// Implementing it on naive solution takes 3 minutes 17 seconds
// Implementing using hash maps and sorting the input data wrt to weight improves the time to 22 seconds.
// The solution without hash-maps takes only 0.72 seconds. The solution instantaites a vector with the knapsize entries. For each W, a row is declared only if needed
// In this implementation with sorting of input data, the no of cols actually needed is only 5422. In this case without sorting the time is 1.2 seconds.

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <tr1/unordered_map>
using namespace std;

bool sortFunc( const vector<long>& p1,
               const vector<long>& p2 ) {
 return p1[1] < p2[1];
}

long knapsackbig(vector < vector<long> > &values, vector < vector<long> > &dp, vector<long> &use, long row, long col){
	long ind = col-values[row][1];	
	if(use[col] == -1){
	   vector <long> temp(2001);
           dp.push_back(temp);
	   long size = dp.size()-1;	
	   use[col] = size;
	   fill(dp[size].begin(),dp[size].end(),-1);}		
	   	 		 		
	if(row==0){
	  dp[use[col]][row]=0;
	  return dp[use[col]][row]; 
	  } 	
	 
	  if(ind <0){
	  	if(dp[use[col]][row-1] != -1){
		    dp[use[col]][row] = dp[use[col]][row-1];}   	
		else {
		    dp[use[col]][row] = knapsackbig(values,dp,use,row-1,col);}  
	  }
	 
	  else{  
		if(use[ind] == -1){
	   	   vector <long> temp(2001);
           	   dp.push_back(temp);
	           long size = dp.size()-1;
	           use[ind] = size;
	           fill(dp[size].begin(),dp[size].end(),-1);}		

		long val1, val2;
	  	if(dp[use[col]][row-1] != -1){
		    val1 = dp[use[col]][row-1];}   	
		else {
		    val1 = knapsackbig(values,dp,use,row-1,col);}  
	  	      	 	
	  	if(dp[use[ind]][row-1] != -1){
		    val2 = dp[use[ind]][row-1];}   	
		else {
		    val2 = knapsackbig(values,dp,use,row-1,ind);}  
       	        
		if(val1 >= val2 + values[row][0]){
		    dp[use[col]][row] = val1;}
	        else { 
		    dp[use[col]][row] = val2 + values[row][0];}	
	  }

	return dp[use[col]][row]; 
}

int main (){

ifstream in("knapsack_big.txt");
long size,number;
in>>size>>number;
vector < vector<long> > values;
vector < vector<long> > dp;
vector <long> use (size+1);
fill(use.begin(),use.end(),-1);
use[0]=0;
vector <long> init(2001);
dp.push_back(init);
fill(dp[0].begin(),dp[0].end(),0); 
for(int k=0; k<=number;k++){
  vector <long> row;
  values.push_back(row);}

values[0].push_back(0);
values[0].push_back(0);
for(int k=0; k<number;k++){
  long temp, temp1;
  in>>temp>>temp1;	
  values[k+1].push_back(temp);
  values[k+1].push_back(temp1);}

sort(values.begin(),values.end(), sortFunc);
long result;
long row=number;
long col=size;
result = knapsackbig(values,dp,use,row,col);
cout<<result<<endl<<dp.size()<<endl;

return 0;
}

//The solution to PA3.2 is 4243395

