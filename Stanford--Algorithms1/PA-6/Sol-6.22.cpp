// Implementation of Median Maintainance using Binary search Tree (own algo : algo not good compared to used in course)
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct node {
	int data;
	int count;
	struct node* left;
	struct node* right;
	};

void IncRightTree(struct node* head){
	head->count++;
	if(head->left != NULL){IncRightTree(head->left);}	
	if(head->right != NULL){IncRightTree(head->right);}
	}	



struct node* Insert( int data, struct node* head){
	if((data > head->data) && (head->right ==NULL)){
	struct node * element = NULL;
	element = (struct node*)malloc(sizeof(struct node));
	element->data = data;
	element->left = NULL;
	element->right = NULL;
	element->count = head->count +1;
	head->right = element;
	}
	else if((data < head->data) && (head->left ==NULL)){
	struct node * element = NULL;
	element = (struct node*)malloc(sizeof(struct node));
	element->data = data;
	element->left = NULL;
	element->right = NULL;
	element->count = head->count;
	head->left = element;
	head->count++;
	if(head->right != NULL){IncRightTree(head->right);}
	}
	else if((data > head->data)){
	      Insert(data,head->right);
	      		
	}
	else if((data < head->data)){
	      head->count++;
	      if(head->right != NULL){IncRightTree(head->right);}		
	      Insert(data,head->left);	
	}
	return head; }

void MedianSearch(struct node* head, int search, vector <int> &median){
	if(head->count == search){ median.push_back(head->data);}
	else if(head->count > search){ MedianSearch(head->left,search,median);}
	else { MedianSearch(head->right,search,median);}
	}

//printnd function is used to print the values of the tree : used only for debug
void printnd(struct node* head){
	cout<<head->data<<" "<<head->count<<endl;
	if(head->left != NULL){ printnd(head->left);}
	if(head->right != NULL){ printnd(head->right);}
	}
	
int main (){

ifstream in("Median.txt");
int n;
vector <int> numbers;
while(in>>n){
  numbers.push_back(n);}

vector <int> median;
struct node * head = NULL;
head = (struct node*)malloc(sizeof(struct node));
head->left = NULL;
head->right = NULL;
head->data = numbers[0];
head->count =1;
median.push_back(head->data);	

for(int i=1; i<numbers.size();i++){
	head = Insert(numbers[i],head);	
	int elements = i+1;
	int search;
	if(elements%2 == 0){ search = elements/2;}
	else { search = (elements/2) +1;}
	MedianSearch(head,search,median);
}

long long int sum =0;


for(int j=0;j<median.size();j++){
	sum+=median[j];}

cout<<sum<<endl;

//printnd(head);

in.close();

return 0;
}
// The sum of medians is 46831213, The answer to PA-6.2 is 1213

/* The basic algo is as follows:

   ->  If there is a left insert, add the left node with count value equal to parent count. Increment parent count by 1. Also increment all nodes in the right tree of parent by 1 using IncRightTree
   ->  If there is a right insert, add the right node with count value equal to parent count +1.
   ->  If there is left traversal, increment parent node by 1. Also, increment all nodes in the right tree of parent by 1 using IncRightTree
   ->  If there is right traversal, than no action required.	*/		
