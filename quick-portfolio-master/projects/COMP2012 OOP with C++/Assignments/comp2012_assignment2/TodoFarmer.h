/*
 * File Created: Sun Mar 15 2020
 * Author: Chow Hau Cheung Jasper
 * SID: 20589533
*/

#ifndef FARMER_H_
#define FARMER_H_

#include "Employee.h"
// TODO: Start to implement your code.

class Farmer : public Employee{
public:
	Farmer();
	~Farmer();
	char getSymbol() const;
	string getName() const;
};

#endif /*FARMER_H_*/
