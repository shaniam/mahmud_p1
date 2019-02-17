#include "node.h"
#include <string>
#include <sstream>
#include <fstream>
Node* find(vector<Node*> &lis, int x){
	//int i=0;
	//cerr << x << endl;
	for (auto &b : lis){
		if(b->state==x){
			return b;
		}
	//	i++;
	}
	//cerr << "we out " << x << endl;
	return NULL;
}
int main(int argc, char* argv[]){
	ifstream input;
	input.open(argv[1]);
	string line;
	Node* add;
	string states;
	int state=0;
	bool start;
	bool accept;
	string first;
	string states1;
	string states2;
	string transs;
	int state1;
	int trans;
	int state2;
	vector<Node*> lis={};
	Node* begin=NULL;
	Node* end=NULL;
	while (getline(input, line)){
		istringstream iss(line);
		if (line.find("state")!=string::npos ){
			if(line.find("acceptstart")!=string::npos || (line.find("start")!=string::npos && line.find("accept")!=string::npos) ){
				iss >> first;
				iss >> states;
				state=stoi(states);
				add = new Node(state, true, true);
			}
			else if(line.find("start")!=string::npos){
				iss >> first;
				iss >> states;
				state=stoi(states);
				add= new Node(state, true, false);
			}
			else if(line.find("accept")!=string::npos){
				iss >> first;
				iss >> states;
				state=stoi(states);
				add = new Node(state, false, true);
			}
			lis.push_back(add);
		}
		else{
			iss >> first;
			iss >> states1;
			iss >> transs;
			iss >> states2;
			state1=stoi(states1);
			trans=stoi(transs);
			state2=stoi(states1);
			begin=find(lis, state1);
			end=find(lis,state2);
			if (begin!=NULL && end!=NULL){
				if(trans==1){
				begin->addOne(end);
				}
				else{
				begin->addZero(end);
				}
			}
			else if(begin!=NULL && end==NULL){
				end=new Node(state2, false, false);
				lis.push_back(end);
				if(trans==1){
					begin->addOne(end);
				}
				else{
				begin->addZero(end);
				}
			}
			else if(begin==NULL && end!=NULL){
				begin=new Node(state1, false, false);
				lis.push_back(begin);
				if (trans==1){
				begin->addOne(end);
				}
				else{
				begin->addZero(end);
				}
			}
			else if(begin==NULL && end==NULL){
				//cerr << "HELLO" << endl;
				if (state1!=state2){
				begin=new Node(state1, false, false);
				end=new Node(state2, false, false);
				
				lis.push_back(begin);
				lis.push_back(end);
				}
				else{	
				begin=new Node(state1, false, false);
				end=begin;
				lis.push_back(begin);
				}
				if(trans==1){
					begin->addOne(end);
				}
				else{
					begin->addZero(end);
				}
			}


		}

	}
	for (auto x : lis){
			cerr << x->state;
			if (x->start){
			cerr << "TRUE" ;
			}
			else{
			cerr << "FALSE" ;
			}
			if (x->accept){
			cerr << "TRUE" << endl;
			}
			else{
			cerr << "FALSE" << endl;
			}
		}

}
