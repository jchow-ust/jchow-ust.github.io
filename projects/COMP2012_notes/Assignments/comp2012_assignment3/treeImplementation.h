//this is one of the two files that you need to submit

using namespace std;
//you are NOT allowed to include additional libraries yourself

//you do NOT need to include "tree.h" in this file
//this is NOT a cpp file, but simply a part of "tree.h"
//see the bottom of tree.h for explanation
//just write your tree implementation here right away

// Author: Chow Hau Cheung Jasper
// SID: 20589533
// ITSC: hcjchow (email: hcjchow@connect.ust.hk)
// Date: May 4 2020

template <typename T> // muy importante - include template header in every file used AND function definition thereafter
Tree<T>::Tree(const Tree<T>&another){
	if (another.isEmpty()){
		return;
	}
	root = new Node<T>(*(another.root));
}

template <typename T>
Tree<T>::~Tree(){
	delete root;
}

template <typename T>
const Tree<T>& Tree<T>::operator=(const Tree<T>& another){
	if (this!=&another){
		root = new Node<T> (*(another.root));
	}
	return (*this);
}

template <typename T>
Tree<T>* Tree<T>::find(const T& data){
	if (root==nullptr){// base case, empty tree
		return nullptr;
	}
	if (root->data != data){// if not this case, we return the tree itself
		Tree <T> * temp = nullptr;
		for (int i=0; i<root->childCount; i++){
			// if NOT found in all its subtrees, and is not the root, then DNE in the tree
			temp = root->children[i].find(data); // recursive call
			if (temp!=nullptr){
				return temp;
			}
		}
		return nullptr;
	}
	else{
		return this;
	}
}

// the const version - COMPLETE testing
template <typename T>
const Tree<T>* Tree<T>::find(const T& data) const{
	if (root==nullptr){// base case, empty tree
		return nullptr;
	}
	int found_index = -1;
	if (root->data != data){// if not this case, we return the tree itself
		for (int i=0; i<root->childCount; i++){
			if (root->children[i].find(data)!=nullptr){// recursive call
				found_index = i; break;
			}
		}
		if (found_index==-1){// not found in any child's subtree
			return nullptr;
		}
		return const_cast<const Tree<T>*>(root->children[found_index].find(data));
	}
	else{
		return this; // turn this pointer into a const
	}
}

template <typename T>
int Tree<T>::getDepth(const T& data) const{
	int count=-1;
	if (root==nullptr){// empty tree
		return -1;
	}
	if (root->data != data){
		for (int i=0; i<root->childCount; i++){
			// if NOT found in all its subtrees, and is not the root, then DNE in the tree
			count = root->children[i].getDepth(data); // recursive call
			if (count!=-1){
				break;
			}
		}
		if (count==-1){ // not found in any subtree case
			return -1;
		}
		return (count+1);
	}
	else{
		return 0;
	}
}


template <typename T>
// amount of descendants you have is amount of descendants each child has + amount of children you have
int Tree<T>::getDescendantCount(const T& data) const{
	if (find(data)==nullptr){// not in our tree
		return -1;
	}
	if (root==nullptr){// empty tree
		return -1;
	}
	return find(data)->getDescendantCount(); // must not be -1
}


template <typename T>
int Tree<T>::getDescendantCount() const{
	int c = 0;
	for (int i=0; i<root->childCount; i++){
		c += root->children[i].getDescendantCount(); // recursive call to find number of descendants for each child
	}
	c += root->childCount; // number of direct children
	return c;
}

template <typename T>
bool Tree<T>::addRoot(const T& data){
	if (find(data)!=nullptr){// already exists in tree
		return false;
	}
	if (root==nullptr){// make root if empty tree
		root = new Node<T> (data);
	}
	else{// if not empty, make a new tree object with the old root
		Tree<T> newtree;
		newtree.root = root;
		// no need to delete since newtree has a pointer to it now
		root = new Node<T> (data);
		root->childCount++; root->children=new Tree[1];
		root->children[0] = newtree;
	}
	return true;
}


template <typename T>
bool Tree<T>::addChild(const T& parentData, const T& childData){
	Tree<T>* parent = find(parentData);
	if (find(childData)!=nullptr || parent==nullptr){
		return false;
	}

	// allocate new dynamic array
	Tree<T> * newchildren = new Tree<T> [parent->root->childCount+1];
	for (int i=0; i<parent->root->childCount; i++){
		newchildren[i]=parent->root->children[i];
	}
	// make new tree with root value childData

	Tree<T> newtree;
	newtree.root = new Node<T> (childData);
	newchildren[parent->root->childCount]=newtree; // last element in 'children' array points to this new tree
	parent->root->childCount++;
	delete [](parent->root->children); // deallocate old 'children' array
	parent->root->children = newchildren;

	return true;

}

