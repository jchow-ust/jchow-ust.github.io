/*
 * File Created: Sun Mar 15 2020
 * Author: Chow Hau Cheung Jasper
 * SID: 20589533
*/

#ifndef FARMLAND_H_
#define FARMLAND_H_

#include "Property.h"
extern const int FARMLAND_SIZE_X;
extern const int FARMLAND_SIZE_Y;
// TODO: Start to implement your code.

class Farmland : public Property{
public:
	Farmland(int, int);
	virtual bool checkEmployee(Employee*) const override;
	virtual void upgrade() override;
	virtual int makeMoney() const override;
	virtual char getSymbol() const override;
	virtual string getName() const override;
};

#endif /*FARMLAND_H_*/
