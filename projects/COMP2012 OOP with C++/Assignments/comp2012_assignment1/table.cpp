/*
 * table.cpp
 *
 *  Created on: 15 Mar 2020
 *      Author: jchow
 */


#include <iostream>
#include "table.h"
#include "intermediate.h"
#include <string>

// default constructor, uses MIL
// DONE
Table::Table() : attrs(nullptr), entries(nullptr), numAttrs(0), numEntries(0){
};

// copy constructor, takes by reference an object of type Table
// DONE
Table::Table(const Table&another) : attrs(nullptr), entries(nullptr), numAttrs(0), numEntries(0){
	if (another.numAttrs>0){
		attrs = new string [another.numAttrs];
		for (int i=0; i<another.numAttrs; i++){
			attrs[i]=another.attrs[i];
		}
	}
	numAttrs = another.numAttrs;

	if (another.numEntries>0){
		entries = new string * [another.numEntries];
		for (int i=0; i<another.numEntries; i++){
			entries[i] = new string[numAttrs];
			for (int j=0; j<another.numAttrs; j++){
				entries[i][j]=another.entries[i][j];
			}
		}
	}
	numEntries = another.numEntries;
};

// destructor
// DONE
Table::~Table(){
	if (attrs!=nullptr){
		delete []attrs;
	}
	if (entries!=nullptr){
		for (int i=0; i<numEntries; i++){
			delete []entries[i];
		}
		delete []entries;
	}
}

bool Table::addAttribute(const string &attr, int index, const string &default_value){
	// index out of range
	if (index > numAttrs || index < -1){
		return false;
	}
	int realindex = index;
	if (index==-1){
		realindex=numAttrs;
	}
	if (attrs==nullptr){
		attrs = new string[1];
		attrs[0]=attr;
	}
	else{
		string* newattrs;
		newattrs = new string[numAttrs+1];
		int inserted = 0;
		for (int i=0; i<numAttrs+1; i++){
			if (i==realindex){
				newattrs[i] = attr;
				inserted = 1;
			}
			else{
				newattrs[i] = attrs[i-inserted];
			}
		}
		delete []attrs;
		attrs = newattrs;
	}
	numAttrs++; // update this data member

	// update existing entries, if they exist
	string**newentries = nullptr;
	if (numEntries>0){
		newentries = new string * [numEntries];
		for (int i=0; i<numEntries; i++){
			int entry_inserted=0;
			newentries[i] = new string [numAttrs];
			for (int j=0; j<numAttrs; j++){
				if (j==realindex){
					entry_inserted = 1;
					newentries[i][j]=default_value;
				}
				else{
					newentries[i][j]=entries[i][j-entry_inserted];
				}
			}
			delete [] entries[i]; // deallocate old 2d array
		}
		delete []entries;
		entries = newentries;
	}
	return true;
};

bool Table::addEntry(const string entry[], int index){
	// index out of range
	if (index > numEntries || index < -1){
		return false;
	}
	int realindex = index;
	if (index==-1){
		realindex=numEntries;
	}
	if (entries==nullptr){
		entries = new string * [1];
		if (numAttrs!=0){
			entries[0] = new string [numAttrs];
			for (int i=0; i<numAttrs; i++){
				entries[0][i] = entry[i];
			}
		}
	}
	else{
		string** newentries;
		newentries = new string * [numEntries+1];
		int inserted = 0;
		for (int i=0; i<numEntries+1; i++){
			newentries[i] = new string [numAttrs];
			if (i==realindex){
				for (int j=0; j<numAttrs; j++){
					newentries[i][j]=entry[j];
				}
				inserted = 1;
			}
			else{
				for (int j=0; j<numAttrs; j++){
					newentries[i][j] = entries[i-inserted][j];
				}
			}
		}
		// deallocate old dynamic 2d array
		for (int i=0; i<numEntries; i++){
			delete [] entries[i];
		}
		delete [] entries;
		entries = newentries;
	}
	numEntries++; // update this data member
	return true;
};

bool Table::deleteAttribute(int index){
	// index out of range
	if (index > numAttrs-1 || attrs==nullptr || index<=-1){
		return false;
	}
	// update attributes
	string* newattrs = nullptr;
	newattrs = new string[numAttrs-1];
	int inserted = 0;
	for (int i=0; i<numAttrs; i++){
		if (i==index){
			inserted = 1;
		}
		else{
			newattrs[i-inserted]=attrs[i];
		}
	}
	delete [] attrs;
	attrs = newattrs;
	numAttrs--;

	// if no attributes left, delete all remaining entries
	if (numAttrs==0){
		for (int i=0; i<numEntries; i++){
			delete []entries[i];
		}
		delete []entries;
		entries = nullptr;
		numEntries = 0;
		return true;
	}

	// update existing entries, if they exist
	string**newentries = nullptr;
	if (numEntries>0){
		newentries = new string * [numEntries];
		for (int i=0; i<numEntries; i++){
			newentries[i]= new string [numAttrs];
			int entry_inserted=0;
			for (int j=0; j<numAttrs+1; j++){
				if (j==index){
					entry_inserted = 1;
				}
				else{
					newentries[i][j-entry_inserted]=entries[i][j];
				}
			}
			delete [] entries[i];
		}
		delete [] entries;
		entries = newentries;
	}
	return true;
};

bool Table::deleteEntry(int index){
	// index out of range
	if (index > numEntries-1 || entries == nullptr || index <= -1){
		return false;
	}
	// update existing entries, if they exist
	string**newentries = nullptr;
	if (numEntries>0){
		newentries = new string * [numEntries-1];
		int entry_inserted = 0;
		for (int i=0; i<numEntries-1; i++){
			newentries[i] = new string[numAttrs];
		}

		for (int i=0; i<numEntries; i++){// use the old entry amount
			if (i==index){
				entry_inserted = 1;
			}
			else{
				for (int j=0; j<numAttrs; j++){
					newentries[i-entry_inserted][j]=entries[i][j];
				}
			}
		}

		for (int i=0; i<numEntries; i++){
			delete [] entries[i];
		}
		delete []entries;
		entries = newentries;
		numEntries--;
	}
	return true;
};

bool Table::append(const Table &another){
	if (another.numAttrs != numAttrs){
		return false;
	}
	else{
		for (int i=0; i<numAttrs; i++){
			if (attrs[i]!=another.attrs[i]){
				return false;
			}
		}
	}
	for (int i=0; i<another.numEntries; i++){
		this->addEntry(another.entries[i]);
	}
	return true;
};

void Table::print() const{
	if(numAttrs>0){
		cout << "Attributes" << endl;
		for (int i=0; i<numAttrs; i++){
			cout << attrs[i] << " | ";
		}
		cout << endl;
	}
	if(numEntries>0){
		cout << "Entries" << endl;
		for (int i=0; i<numEntries; i++){
			for (int j=0; j<numAttrs; j++){
				cout << entries[i][j] << " | ";
			}
			cout << endl;
		}
		cout << endl;
	}
};


