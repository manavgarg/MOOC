#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int main (){

ifstream in("jobs.txt");
int number,number1;
in>>number;
vector < vector<int> > values;  
//cout<<number;
number1=number;
for(int k=0; k<number;k++){
  vector <int> row;
  values.push_back(row);}	
int i=0;
while(number1--){ int w,l;
	in >> w>>l;;
	values[i].push_back(w-l);
	values[i].push_back(w);
	values[i].push_back(l);
	i++;}

sort(values.begin(),values.end());

long long int output=0, length=0;
for(int i=values.size()-1;i>=0;i--){
  length+=values[i][2];
  output+=(values[i][1]*length);}
 cout<<output;

in.close();

return 0;
}

// The Answer to PA1.1 is 69119377652
