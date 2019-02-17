#include "node.h"

void Node::addOne(Node* one){
	this->ones.push_back(one);
}
void Node::addZero(Node* zero){
	this->zeros.push_back(zero);
}
Node::Node(int state, bool start, bool accept){
	this->start=start;
	this->accept=accept;
	this->state=state;
}
Node::Node(){
}
