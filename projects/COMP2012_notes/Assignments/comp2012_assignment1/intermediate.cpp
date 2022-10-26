/*
 * intermediate.cpp
 *
 *  Created on: 15 Mar 2020
 *      Author: jchow
 */


#include <iostream>
#include "table.h"
#include "intermediate.h"
#include <string>

Intermediate::Intermediate(const Table & table) {
	// friend class allows private members to be accessed
	// entry is a pointer to string

	attrs = table.attrs;
	numAttrs = table.numAttrs;

	// head points to the first element of table.entries
	// since initialization requires all entries

	if (table.numEntries>0){
		head = new EntryNode;
		head->entry = table.entries[0];
		head->next = nullptr; head->prev = nullptr;
		tail = head;
	}
	else{
		head = nullptr;
		tail = nullptr;
	}


	// join elements of the linked list
	// start with making a new EntryNode, having its previous point to the previous node
	// and its next point to nullptr
	// then the previousnode->next is set to this new node
	// and advance previousnode to be this new node
	for (int i=1; i<table.numEntries; i++){
		EntryNode * newNode = new EntryNode;
		newNode->entry = table.entries[i];
		newNode->prev = tail;
		newNode->next = nullptr;
		tail->next = newNode;
		tail = newNode;
	}
	// at the end tail points to the last node in the linked list
	// that node's prev points to penultimate node and its next points to nullptr
};

Intermediate::~Intermediate() {
	// destructor

	// no need to get rid of statically allocated data members 'attrs' and 'numAttrs'

	EntryNode* temp = head;
	// returns all memory to heap
	while (head != nullptr){
		temp = head->next;
		delete head;
		head = temp;
	}
	// at the end head should be nullptr
	tail = nullptr;
};


// DONE
Intermediate& Intermediate::where(const string &attr, enum compare mode, const string &value) {

	// get index of the attribute. if DNE just return the unchanged object
	int attributeIndex = -1;
	for (int i=0; i<numAttrs; i++){
		if (attrs[i]==attr){ // found valid attribute
			attributeIndex = i;
		}
	}
	if (attributeIndex==-1){
		return (*this);
	}

	int z;
	EntryNode*temp = head;
	EntryNode*dummy = nullptr;
	while (temp!=nullptr){
		if (mode==CONTAINS){
			z = temp->entry[attributeIndex].find(value);
		}
		else if (mode==EQ){
			z = (temp->entry[attributeIndex])==value;
		}
		if ((z==-1 && mode==CONTAINS) || (z==0 && mode==EQ)){// couldn't find it, so remove from linked list
			// if temp is the first node in the linked list, make head pointer point to temp->next
			// however if temp is the only item in the linked list just delete it and reset head and tail pointers
			if (head==temp){
				if (head->next==nullptr){
					delete head;
					head = nullptr;
					tail = nullptr;
				}
				else{
					// make head->prev point to nullptr now so we don't have dangling pointer
					// then delete the old head
					head = head->next;
					head->prev = nullptr;
					dummy = temp;
					temp = temp->next;
					delete dummy;
				}
			}
			// if temp is the last node (else if guarantees temp->prev is not nullptr)
			else if (tail==temp){
				tail = temp->prev;
				tail->next = nullptr;
				dummy = temp;
				temp = temp->next;
				delete dummy;
			}
			// if temp is not first nor last node
			else{
				if (temp->next != nullptr){
					temp->next->prev = temp->prev;
				}
				if (temp->prev != nullptr){
					temp->prev->next = temp->next;
				}
				dummy = temp;
				temp = temp->next;
				delete dummy;
			}
		}
		else{
			temp = temp->next;
		}
	}
	return (*this);
};


Intermediate& Intermediate::orderBy(const string &attr, enum order order){
	// get index of the attribute. if DNE just return the unchanged object
	int attributeIndex = -1;
	for (int i=0; i<numAttrs; i++){
		if (attrs[i]==attr){ // found valid attribute
			attributeIndex = i;
		}
	}
	if (attributeIndex==-1){
		return (*this);
	}

	// bubble sort
	EntryNode*temp = head;
	EntryNode*temp2 = nullptr;
	EntryNode*temp3 = nullptr; // linked list element after temp2, if it exists
	EntryNode*temp4 = nullptr; // linked list element before temp1, if it exists

	// deals with case where there is only one element
	// compares current element with next element, if out of order, swap
	// if cse = current and math = next, and ("math").compare("cse") is >0 since "m" > "c", out of order if DESCENDING
	int swapped = 1;
	while (swapped != 0){
		temp = head;
		temp2 = nullptr;
		temp3 = nullptr;
		temp4 = nullptr;
		swapped = 0;
		while (temp!=nullptr){
			if (temp->next != nullptr){ // only need to do comparisons if there exists another element
				if ((temp->next->entry[attributeIndex].compare(temp->entry[attributeIndex])<0 && order==ASCENDING) ||
						(temp->next->entry[attributeIndex].compare(temp->entry[attributeIndex])>0 && order==DESCENDING)
						){

					// swaps the two entries
					temp2 = temp->next;
					temp3 = temp->next->next;
					temp4 = temp->prev;
					temp2->next = temp;
					temp->prev = temp2;
					temp2->prev = temp4;
					temp->next = temp3;

					// swapping last two elements of the list
					if (temp3 != nullptr){
						temp3->prev = temp;
					}
					else{
						tail = temp;
					}

					// swapping first two elements
					if (temp4 != nullptr){
						temp4->next = temp2;
					}
					else{
						head = temp2;
					}
					temp2=nullptr;
					temp3=nullptr;
					temp4=nullptr;

					swapped++;
				}
			}
			temp = temp->next;
		}
	}
	return (*this);
};

// DONE
Intermediate& Intermediate::limit(unsigned int limit){

	EntryNode*temp = head;
	EntryNode* garbage = nullptr;
	EntryNode* garbage2 = nullptr;
	// return empty intermediate
	if (limit==0){
		while (temp!=nullptr){
			garbage = temp;
			temp = temp->next;
			delete garbage;
		}
		head = nullptr;
		tail = nullptr;
		return (*this);
	}

	for (int i=0; i<limit-1; i++){
		 // covers the case for a value of limit larger than number of entries
		if (temp==nullptr){
			break;
		}
		temp = temp->next;
	}
	if (temp!=nullptr){
		tail = temp; // update tail
		garbage = temp->next;
		tail->next = nullptr;
	}

	// delete the part of the linked list we want to truncate
	while (garbage!=nullptr){
		garbage2 = garbage;
		garbage = garbage->next;
		delete garbage2;
	}
	return (*this);
};


void Intermediate::update(const string &attr, const string &new_value) const{

	// get index of the attribute. if DNE just return
	int attributeIndex = -1;
	for (int i=0; i<numAttrs; i++){
		if (attrs[i]==attr){ // found valid attribute
			attributeIndex = i;
		}
	}
	if (attributeIndex==-1){
		return;
	}

	EntryNode*temp = head;
	while (temp!=nullptr){
		temp->entry[attributeIndex] = new_value;
		temp = temp->next;
	}
};

void Intermediate::select(const string *attrs, int numAttrs) const{
	// has no attributes
	if (this->numAttrs==0){
		return;
	}

	// print all entries
	if (attrs==nullptr){

		// create dynamic array to store maximum length of each column
		int * maxlengths = new int [this->numAttrs];

		for (int i=0; i<this->numAttrs; i++){
			maxlengths[i]=this->attrs[i].length();
		}
		// find final maximum length in each column
		EntryNode*temp = head;
		while (temp!=nullptr){
			for (int i=0; i<this->numAttrs; i++){
				if (temp->entry==nullptr){// if no entries don't update maxlength

				}
				else if (temp->entry[i].length()>maxlengths[i]){
					maxlengths[i]=temp->entry[i].length();
				}
			}
			temp = temp->next;
		}

		// print attributes, they MUST exist
		for (int i=0; i<this->numAttrs; i++){
			string s = _left_pad_until(this->attrs[i], maxlengths[i]);
			// don't add this if last attr
			if (i!=(this->numAttrs)-1){
				cout << s << " | ";
			}
			else{
				cout << s;
			}
		}
		cout << endl;

		// print entries if they exist
		temp = head;
		while (temp!=nullptr){
			for (int i=0; i<this->numAttrs; i++){
				string s = _left_pad_until(temp->entry[i], maxlengths[i]);
				// don't add this if last attr
				if (i!=(this->numAttrs)-1){
					cout << s << " | ";
				}
				else{
					cout << s;
				}
			}
			cout << endl;
			temp = temp->next;
		}

		delete []maxlengths;
	}
	else{// print a specified order of entries
		// "Dept" "Sem" "Code" "Name" "Credits"
		// attrs = "Name" "Code" "Sem"
		// maxlengths = [4, 4, 3]
		// toprint = [3, 2, 1]
		int * maxlengths = new int [numAttrs];
		int * toprint = new int [numAttrs];
		for (int i=0; i<numAttrs; i++){
			maxlengths[i]=attrs[i].length();
			// since the attributes to print exist, find their index and push it to the array 'toprint'
			for (int j=0; j<this->numAttrs; j++){
				if (attrs[i] == this->attrs[j]){
					toprint[i] = j;
				}
			}
		}
		// find the final maximum length by looking through entries, if they exist
		EntryNode*temp = head;
		while (temp!=nullptr){
			// look through array toprint
			// for each attribute's index, does the value of each entry for that corresponding attribute exceed the maximum? if yes update
			for (int i=0; i<numAttrs; i++){
				if (temp->entry==nullptr){// if no entries don't update maxlength

				}
				else if (temp->entry[toprint[i]].length()>maxlengths[i]){
					maxlengths[i]=temp->entry[toprint[i]].length();
				}
			}
			temp = temp->next;
		}

		// print attributes, they MUST exist
		for (int i=0; i<numAttrs; i++){
			string s = _left_pad_until(this->attrs[toprint[i]], maxlengths[i]);
			// don't add this if last attr
			if (i!=numAttrs-1){
				cout << s << " | ";
			}
			else{
				cout << s;
			}
		}
		cout << endl;

		// print entries if they exist
		temp = head;
		while (temp!=nullptr){
			for (int i=0; i<numAttrs; i++){
				string s = _left_pad_until(temp->entry[toprint[i]], maxlengths[i]);
				// don't add this if last attr
				if (i!=numAttrs-1){
					cout << s << " | ";
				}
				else{
					cout << s;
				}
			}
			cout << endl;
			temp = temp->next;
		}
		delete []toprint;
		delete []maxlengths;
	}
};

