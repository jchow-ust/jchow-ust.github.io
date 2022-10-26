/*
 * File Created: Sun Mar 15 2020
 * Author: Chow Hau Cheung Jasper
 * SID: 20589533
*/

#ifndef FEEDER_H_
#define FEEDER_H_

#include "Employee.h"
// TODO: Start to implement your code.

class Feeder : public Employee{
public:
	Feeder();
	~Feeder();
	char getSymbol() const;
	string getName() const;
};

#endif /*FEEDER_H_*/
