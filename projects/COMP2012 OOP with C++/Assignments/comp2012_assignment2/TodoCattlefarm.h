/*
 * File Created: Sun Mar 15 2020
 * Author: Chow Hau Cheung Jasper
 * SID: 20589533
*/

#ifndef CATTLEFARM_H_
#define CATTLEFARM_H_

#include "Property.h"
extern const int CATTLEFARM_SIZE_X;
extern const int CATTLEFARM_SIZE_Y;

// HINT: You may seek help from Property::fireEmployee()
//       when you implement your Cattlefarm::removeDiedCow().
// TODO: Start to implement your code.

class Cattlefarm : public Property{
public:
	Cattlefarm(int, int);
	virtual bool checkEmployee(Employee*) const override;
	virtual void upgrade() override;
	virtual int makeMoney() const override;
	void removeDiedCow();
	virtual char getSymbol() const override;
	virtual string getName() const override;
};

#endif /*CATTLEFARM_H_*/
