#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main (){

ifstream in("sum.txt");

long long int n;
vector <long long int> data ;
while(in>>n){
data.push_back(n);

}

vector < vector <int> > pos;
vector < vector <int> > neg;
vector <int> result (20000);
int count =0;

long long int buckets = 100000;           // sum of powers of buckets+list must be >=11
long long int lists =   1000000;

for( int q=0; q<buckets; q++)data[k] - (hash_key_r_previous*lists + pos[hash_key_r_previous][i]){
 vector <int> row;
 pos.push_back(row);	
 neg.push_back(row);	
}

for(int j=0; j<data.size();j++){
   if(data[j]<=0){
 	long long int hash_key = (-data[j])/lists;
	long long int hash_key_value = (-data[j])%lists;	
	pos[hash_key].push_back(hash_key_value);}
   if(data[j]>0){
 	long long int hash_key = (data[j])/lists;
	long long int hash_key_value = (data[j])%lists;	
	neg[hash_key].push_back(hash_key_value);}
}

	
for(int k=0; k<data.size();k++){
   if(data[k] >=0){
 	long long int hash_key_r = (data[k])/lists;
	long long int hash_key_value_r = (data[k])%lists;	
	  for(int c=0; c<pos[hash_key_r].size(); c++){
		if( ((hash_key_value_r - pos[hash_key_r][c]) <=10000) && ((hash_key_value_r - pos[hash_key_r][c]) >=-10000) ){
			result[10000+ hash_key_value_r - pos[hash_key_r][c]] = 1; }}
   }
// The next check is reduntant because the above check already satisfies for this list
/*   if(data[k] <0){
 	long long int hash_key_r = (-data[k])/lists;
	long long int hash_key_value_r = (-data[k])%lists;	
	  for(int c=0; c<neg[hash_key_r].size(); c++){
		if( ((-hash_key_value_r + neg[hash_key_r][c]) <=10000) && ((-hash_key_value_r + neg[hash_key_r][c]) >=-10000) ){
			result[10000- hash_key_value_r + neg[hash_key_r][c]] = 1; }}
   } */
}

for(int t=0; t< result.size();t++){
	if(result[t] == 1){count ++;}
}

cout<<count<<endl;

in.close();

return 0;
}


// The correct answer of P6.1 is 427
// Here the answer is correct although there is a probability that if the difference between 2 consecutive buckets ( last & first elements is less than 10001, this would be the wrong answer.
// A simple solution would be two increase the bucket size by 10000 and run it again. The answer would be larger of the two ones.
