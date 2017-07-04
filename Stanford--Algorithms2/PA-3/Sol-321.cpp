// Implementing it on naive solution takes 3 minutes 17 seconds
// In this implementation it takes around 38 seconds
// Further sorting the input data wrt to weight improves the time to 22 seconds.
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

std::tr1::unordered_map <string , long> m;

bool sortFunc( const vector<long>& p1,
               const vector<long>& p2 ) {
 return p1[1] < p2[1];
}

long knapsackbig(vector < vector<long> > &values, long row, long col){
	stringstream ss1;
	ss1<<row<<"+"<<col;
	stringstream ss2;
	ss2<<row-1<<"+"<<col;
	stringstream ss3;
	ss3<<row-1<<"+"<<col-values[row][1];

	if(row==0){
	  m[ss1.str()] = 0;
	  return m[ss1.str()]; 
	  } 	
	
	  if(col-values[row][1] <0){
	  	if(m.find(ss2.str()) != m.end()){
		    m[ss1.str()] = m[ss2.str()];}   	
		else {
		    m[ss1.str()] = knapsackbig(values,row-1,col);}  
	  }

	  else{  
		long val1, val2;
	  	if(m.find(ss2.str()) != m.end()){
		    val1 = m[ss2.str()];}   	
		else {
		    val1 = knapsackbig(values,row-1,col);}  
	  	      	 	
	  	if(m.find(ss3.str()) != m.end()){
		    val2 = m[ss3.str()];}   	
		else {
		    val2 = knapsackbig(values,row-1,col-values[row][1]);}  
	  
       	        if(val1 >= val2 + values[row][0]){
		    m[ss1.str()] = val1;}
	        else { 
		m[ss1.str()] = val2 + values[row][0];}	
	  }

	return m[ss1.str()]; 
}

int main (){

ifstream in("knapsack_big.txt");
long size,number;
in>>size>>number;
vector < vector<long> > values;
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
result = knapsackbig(values,row,col);
cout<<result<<endl;

return 0;
}

//The solution to PA3.2 is 4243395

