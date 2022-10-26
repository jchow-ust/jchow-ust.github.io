#ifndef SET_H
#define SET_H

#include <iostream>
#include <sstream>

using namespace std;

template<typename T>
class set {
private:
	T* elements { nullptr };
	int size { 0 };
	string str() const {
		ostringstream os;
		os << "{";
		if (size != 0) {
			os << elements[0];
			for (int i = 1; i < size; i++) {
				os << "," << elements[i];
			}
		}
		os << "}";
		return os.str();
	}

public:
	set() = default;
	set(const T * arr, int size) :
			size(size) {
		elements = new T[size];
		for (int i = 0; i < size; i++)
			elements[i] = arr[i];
	}
	~set() {
		delete[] elements;
	}

	// Return the cardinality of the set, i.e., the size
	int cardinality() const {
		return size;
	}

	// Return the element's index if it exists. Otherwise return -1
	int findElement(const T& element) const {
		int pos = -1;
		for (int i = 0; i < size; i++) {
			if (elements[i] == element) {
				pos = i;
				break;
			}
		}
		return pos;
	}

	// Return true if the element exists, otherwise return false
	bool isExist(const T& element) const {
		int pos = findElement(element);
		bool existence = (pos == -1) ? false : true;
		return existence;
	}

	// Allocate a new array of size "size+1", copy all the existing elements over and
	// add the new element to the last position of the new array
	void addElement(const T& element) {

		if (!isExist(element)) {
			T* newElements = new T[size + 1];
			for (int i = 0; i < size; i++)
				newElements[i] = elements[i];
			newElements[size] = element;
			delete[] elements;
			elements = newElements;
			size++;
		}
	}

	// Check if the element is in the set.
	// If it is in the set, allocate a new array and copy all the existing elements over except
	// the element to be deleted.
	// Return true if the element is found and deleted. Otherwise return false
	bool removeElement(const T& element) {
		if (isExist(element)) {
			int pos = findElement(element);
			T* newElements = new T[size - 1];
			int count = 0;
			for (int i = 0; i < size; i++) {
				if (i != pos)
					newElements[count++] = elements[i];
			}
			delete[] elements;
			elements = newElements;
			size--;
			return true;
		} else
			return false;
	}

	/////////////////////////////////////////////////////////////////////////
	//                                                                     //
	//      	You should only modify the code after this line            //
	//                                                                     //
	/////////////////////////////////////////////////////////////////////////

	// TODO: Copy constructor: Perform deep copying
	set(const set&tocopy){
		*this=tocopy;
	}

	// Hint: Make use of assignment operator function `operator=`

	// TODO: Overload `operator+` to support union operation of two set objects
	set operator+(const set& t){
		set <T>s = set(*this);
		for (int i=0; i<t.cardinality(); i++){
			if (isExist(t.elements[i])==false){
				s.addElement(t.elements[i]);
			}
		}
		return s;
	}

	// TODO: Overload `operator*` to support intersect operation of two set objects
	// 1 2 4
	// 2 3
	set operator*(const set& t){
		set <T>s = set(*this); // call copy cons to make temp object

		bool lookup = true;
		while (lookup){
			lookup = false;
			for (int i=0; i<s.cardinality(); i++){
				if (t.isExist(s.elements[i])==false){
					s.removeElement(s.elements[i]);
					lookup = true; break;
				}
			}
		}

		return s;
	}

	// TODO: Overload assignment operator function `operator=`
	// Note: Deep copying is required
	set& operator=(const set& tocopy){
		size = tocopy.cardinality();
		if (size==0){
			elements = {nullptr};
			return *this;
		}
		T* newelements = new T[tocopy.cardinality()];
		for (int i=0; i<tocopy.cardinality(); i++){
			newelements[i]=tocopy.elements[i];
		}
		delete []elements;
		elements = newelements;
		return *this;
	}

	// TODO: Overload equality operator function `operator==`
	bool operator==(const set&b){
		if (cardinality()!=b.cardinality()){
			return false;
		}
		for (int i=0; i<cardinality(); i++){
			if (b.findElement(elements[i])==-1){
				return false;
			}
		}
		return true;
	}

	// TODO: Using the "friend" keyword, declare stream insertion operator function `operator<<`
	friend ostream& operator<<(ostream&os, const set& a){
		return os << a.str();
	}

};

#endif
