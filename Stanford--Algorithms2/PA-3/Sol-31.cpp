#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main (){

ifstream in("knapsack1.txt");
long long size,number;
in>>size>>number;
vector < vector<long long> > values;
for(int k=0; k<=number;k++){
  vector <long long> row;
  values.push_back(row);}

values[0].push_back(0);
values[0].push_back(0);
for(int k=0; k<number;k++){
  long long temp, temp1;
  in>>temp>>temp1;	
  values[k+1].push_back(temp);
  values[k+1].push_back(temp1);}

vector < vector<long long> > dp;
for(int k=0; k<=number;k++){
  vector <long long> row;
  dp.push_back(row);}

for(int k=0; k<=size;k++){
  dp[0].push_back(0);}

for(int i=1;i<=number;i++){
   for(int j=0;j<=size;j++){
	if(j-values[i][1] <0){
	   dp[i].push_back(dp[i-1][j]);}
	else{
	   if(dp[i-1][j] >= dp[i-1][j-values[i][1]]+ values[i][0]){
		dp[i].push_back(dp[i-1][j]);}
	   else { dp[i].push_back(dp[i-1][j-values[i][1]] + values[i][0]);}	 	
	}
   } 	
}

cout<<dp[number][size]<<endl;

return 0;
}
//The answer to PA3.1 is 2493893
