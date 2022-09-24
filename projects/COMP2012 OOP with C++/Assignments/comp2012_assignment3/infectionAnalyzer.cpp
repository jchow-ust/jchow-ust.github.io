//this is one of the two files that you need to submit

#include "infectionAnalyzer.h"
#include <fstream> //for reading file
#include <queue> //you may use STL queue
#include <algorithm> //you may use STL algorithm
using namespace std;
//you are NOT allowed to include additional libraries yourself

// Author: Chow Hau Cheung Jasper
// SID: 20589533
// ITSC: hcjchow (email: hcjchow@connect.ust.hk)
// Date: May 4 2020

// destructor
InfectionAnalyzer::~InfectionAnalyzer(){
	// deallocate memory for all trees in the vector 'trees'
	vector<Tree<string>*>::iterator it;
	for (it = trees.begin(); it != trees.end(); it++){
		delete *it;
	}
}

bool InfectionAnalyzer::loadInfectionFile(const string filename){
	trees.clear();
	fstream infectfile (("%s.txt",filename));  // %s is placeholder for string
	if (infectfile.is_open()){
		string a; // let a be the infector and b be the infectee TODO
		string b;
		//Tree<string> * newtree = nullptr;
		while (infectfile >> a >> b){// reads in each line of 'infectfile' and saves it to string variable 'line'
			// first search for the infector and infectee in existing trees

			vector<Tree<string>*>::iterator b_location; // only used in merge case
			Tree<string>* fake_a = nullptr; Tree<string>* fake_b = nullptr;

			for (vector<Tree<string>*>::iterator it = trees.begin(); it != trees.end(); ++it){

				if ((*it)->find(a)!=nullptr){// found a somewhere in our vector, store the pointer to the tree with a as root in fake_a
					fake_a = *it;
				}
				if ((*it)->find(b)!=nullptr){// found b somewhere in our vector, store the pointer to the tree with b as root in fake_b
					fake_b = *it; b_location = it;
				}
			}

			// if both DNE, make new tree and push it to vector 'trees'
			if (fake_a == nullptr && fake_b == nullptr){
				Tree<string>*newtree = new Tree<string>;
				newtree->addRoot(a);
				newtree->addChild(a,b);
				trees.push_back(newtree); // push the pointer
			}
			// if infector exists but not infectee, add infectee as child
			else if (fake_a != nullptr && fake_b == nullptr){
				fake_a->addChild(a,b);
			}
			// if infectee exists but not infector, add infector as root
			else if (fake_a == nullptr && fake_b != nullptr){
				fake_b->addRoot(a);
			}
			// if both exist, merge
			// sample (A->(B, C, D->(E, F)) ... G->H->I and (C, G) is our pair, add infectee G as child of infector C.
			// since merge is always valid, we cannot have had C->H for instance.
			// Claim: (Pf by contradiction) the child subtree must have been the root of some other tree. Suppose not. then there exists some node which has two parents. not OK.
			// by that logic, infectee must be the root of some subtree. we can make C have an additional child, which is G.
			// then remove tree infectee inhabits (tree GHI) from vector 'trees'.
			else if (fake_a != nullptr && fake_b != nullptr){

				fake_a->addChild(a,b);
				(fake_a->find(b))->root = fake_b->root; // guaranteed to not be nullptr
				// above line essentially finds pointer to the tree with the parent that now also contains node with the child data
				// and uses copy constructor to copy the two nodes (and subsequently all descendants of the child node)

				trees.erase(b_location); // removes the child tree from our vector of trees (since it has been merged with the parent)
			}
		}
		infectfile.close();
		return true;
	}
	return false; // bad format, file cant be loaded
}

//return true if the specified name can be found in any of the infection trees
//return false otherwise
bool InfectionAnalyzer::isInfected(const string name) const{
	bool result = false;
	for (int i=0; i<trees.size(); i++){
		if (trees[i]->find(name)!=nullptr){
			result = true; break;
		}
	}
	return result;
}

//check all trees, and find the node with the specified name, and return the name of its parent
string InfectionAnalyzer::getInfectionSource(const string name) const{
	if (isInfected(name)==false){
		return "NA";
	}
	for (int i=0; i<trees.size(); i++){
		if (trees[i]->root->data==name){
			return "ZERO"; // is root node of a tree
		}
	}

	string infectionParent;
	queue <Tree <string>*> people;
	if (trees.size()==0){ // return empty string
		return infectionParent;
	}
	for (int i=0; i<trees.size(); i++){
		people.push(trees[i]);
	}

	while (people.empty()==false){
		Tree<string>*currtree = people.front();
		for (int i=0; i<currtree->root->childCount; i++){
			if (currtree->root->children[i].root->data==name){
				infectionParent = currtree->root->data; break; // found the desired name in one of its descendants
			}
			people.push(&(currtree->root->children[i])); // add each of its descendants to vector
		}
		people.pop(); // pop first element from queue
	}
	return infectionParent;
}

//return the depth of the node with the specified name
//if the specified name is not found at all in all trees, return -1
int InfectionAnalyzer::getInfectionGeneration(const string name) const{
	int ret = -1;
	for (int i=0; i<trees.size(); i++){
		if (trees[i]->getDepth(name)!=-1){ // if not found in anything, will still return -1
			ret = trees[i]->getDepth(name); break;
		}
	}
	return ret;
}

// helper function to sort infection power pairs
bool sortrule(const pair<string, int>&a, const pair<string, int>&b){
	if (a.second > b.second){// descending order
		return true;
	}
	else if (a.second < b.second){
		return false;
	}
	else{
		// equal so sort by string name in ascending order
		return (a.first < b.first);
	}
}

const vector<pair<string, int>>& InfectionAnalyzer::getInfectionPowerVector(){

	infectionPowerVector.clear(); // clear iPV at beginning
	queue <Tree <string>*> people;
	if (trees.size()==0){ // return empty vector
		return infectionPowerVector;
	}
	for (int i=0; i<trees.size(); i++){
		people.push(trees[i]);
	}

	// COMP3711 BFS squad
	while (people.empty()==false){
		Tree<string>*currtree = people.front();
		string currdata = currtree->root->data;
		int dcount = currtree->getDescendantCount(currdata);
		infectionPowerVector.push_back(make_pair(currdata, dcount)); // push descendant count to the power vector
		for (int i=0; i<currtree->root->childCount; i++){
			people.push(&(currtree->root->children[i])); // add each of its descendants to vector
		}
		people.pop(); // pop first element from queue
	}
	// sort iPV by num of descendants
	sort(infectionPowerVector.begin(), infectionPowerVector.end(), sortrule);
	return infectionPowerVector;
}


