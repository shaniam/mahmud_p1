#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <fstream>
#include <cstddef>
#include <math.h>



using namespace std;
class Node{
	public:
		int state;
		vector<Node*> adjacents={}; 
		vector<Node*> ones={};
		vector<Node*> zeros={};
		bool start=false;
		bool accept=false;
		Node(int, bool, bool);
		Node();
		void addOne(Node*);
		void addZero(Node*);
};
class LinkedList{
	public:
		vector<Node*> nodes={};
		Node* head;
		LinkedList(){};	
};	


#endif
