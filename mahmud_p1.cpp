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
	Node* starter=NULL;
	while (getline(input, line)){
		istringstream iss(line);
		if (line.find("state")!=string::npos ){
			if(line.find("acceptstart")!=string::npos || (line.find("start")!=string::npos && line.find("accept")!=string::npos) ){
				iss >> first;
				iss >> states;
				state=stoi(states);
				add = new Node(state, true, true);
				starter=add;
			}
			else if(line.find("start")!=string::npos){
				iss >> first;
				iss >> states;
				state=stoi(states);
				add= new Node(state, true, false);
				starter=add;
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
			state2=stoi(states2);
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
				if(trans==1){
						begin->addOne(end);
					}
				else{
						begin->addZero(end);
				}
				}
				else{	
					begin=new Node(state1, false, false);
					lis.push_back(begin);
					if (trans==1){
							begin->addOne(begin);
						}
					else{
						begin->addZero(begin);
					}
				}
				/*if(trans==1){
					begin->addOne(end);
				}
				else{
					begin->addZero(end);
				}*/
			}


		}

	}
	for (auto x: lis){
		cerr << x->state << ": zeros: ";
		for (auto y: x->zeros){
			cerr << y->state << " ";
		}
		cerr << "\n " << x->state << ": ones";
		for (auto y :x->ones){
			cerr << y->state << " ";
		}
		cerr << endl;
	}
	string arg=argv[2];
	vector<pair<Node*, string>> path={};
	path.push_back(make_pair(starter, arg));
	bool flag=false;
	string left;
	int symbol;
	char sym;
	Node* curr=starter;
	for (int i=0; i<path.size(); i++){
		Node* curr=path[i].first;
		left=path[i].second;
		if(left==""){
			if(curr->accept==true){
				flag=true;
			}
		}
			else{
				sym=left[0];
				symbol=sym-'0';
				if (symbol==0){
					for (auto x: curr->zeros){
						path.push_back(make_pair(x, left.substr(1,left.length())));
					}
				}
				else{
					for (auto x: curr->ones){
						path.push_back(make_pair(x, left.substr(1, left.length())));
					}
				}
			}
		}
	for (auto x: path){
		cerr << x.first->state << endl;
	}

	#if 0
	string arg=argv[2];
	vector<pair<Node*, string>> path={};
	path.push_back(make_pair(starter, arg));
	bool flag=false;
	string left;
	int symbol;
	char sym;
	Node* curr=starter;
	for (int i=0; i<path.size(); i++){
		Node* curr=path[i].first;
		left=path[i].second;
		sym=left[0];
		symbol=sym-'0';
		cerr << symbol << endl;
		left=left.substr(1);
		if (symbol==0){
			for (auto x: curr->zeros){
				path.push_back(make_pair(x, left));
			}
		}
		else{
			for (auto x: curr->ones){
				path.push_back(make_pair(x, left));
			}
		}
	}
	bool acc=false;
	vector<Node*> accepts={};
	vector<Node*> rejects={};
	for (int i=0; i<path.size(); i++){
				cerr << path[i].first->state << endl;
			
	}
	if (acc=true){
		cerr << "accept ";
		for (auto x: accepts){
			cerr << x->state << " " ;
			}
		cerr << endl;
	}
	else{
		cerr << "reject ";
		for (auto x :rejects){
			cerr << x->state << " "; 
		}
		cerr << endl;
	}
	/*for (auto x : lis){
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
		}*/
	#endif
}
