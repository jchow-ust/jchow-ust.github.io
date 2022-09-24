/*
 * File Created: Sun Mar 15 2020
 * Author: Chow Hau Cheung Jasper
 * SID: 20589533
*/

#ifndef COW_H_
#define COW_H_

#include "Employee.h"
// TODO: Start to implement your code.
class Cow : public Employee{
private:
	const int m_lifespan;
public:
	Cow();
	~Cow();
	char getSymbol() const;
	string getName() const;
	bool isAlive() const;
	int getLifespan() const;
	void writeToStream(ostream& os) const;
};
#endif /*COW_H_*/
