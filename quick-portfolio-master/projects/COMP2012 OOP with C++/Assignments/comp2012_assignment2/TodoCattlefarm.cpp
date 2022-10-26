/*
 * File Created: Sun Mar 15 2020
 * Author: Chow Hau Cheung Jasper
 * SID: 20589533
*/

#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoCow.h"
#include <cstdlib>

// Cattlefarm cost 80 upgrade cost 16
// Cattlefarm size 6, 6
// Cattlefarm init max num. of employee is CATTLEFARM_MAX_NUM_EMPLOYEE_MIN
// Cattlefarm Upgrade:
//      level increases by 1;
//      max num. of employees increases by 1 until CATTLEFARM_MAX_NUM_EMPLOYEE_MAX
// Cattlefarm Makemoney:
//      min(num. of cows, num. of feeders in work) x level x 10;

const int CATTLEFARM_COST = 80;
const int CATTLEFARM_UPGRADE_COST = 16;
const int CATTLEFARM_SIZE_X = 6; const int CATTLEFARM_SIZE_Y = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MIN = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MAX = (CATTLEFARM_SIZE_X-2) * (CATTLEFARM_SIZE_Y-2);

// TODO: Start to implement your code.

Cattlefarm::Cattlefarm(int x, int y) : Property(CATTLEFARM_COST, CATTLEFARM_UPGRADE_COST, CATTLEFARM_MAX_NUM_EMPLOYEE_MIN){
	setXY(x,y);
	setSize(CATTLEFARM_SIZE_X, CATTLEFARM_SIZE_Y);
}

bool Cattlefarm::checkEmployee(Employee* emp) const{
	if (emp==nullptr){return false;}
	if (emp->getName()=="Employee" || emp->getName()=="Farmer"){
		return false;
	}
	if (emp->getName()=="Feeder" || emp->getName()=="Cow"){
		return true;
	}
	return false;
}

void Cattlefarm::upgrade(){
	this->Property::upgrade();
	if (CATTLEFARM_MAX_NUM_EMPLOYEE_MAX > getMaxNumEmployee()){
		setMaxNumEmployee(getMaxNumEmployee()+1);
	}
}

int Cattlefarm::makeMoney() const{
	int profit = getLevel() * 10;
	int active_employees = 0;
	int moo = 0;

	// otherwise compiler throws a fit
	const Employee ** e;
	getConstEmployeeList(e);
	for (int i=0; i<getNumEmployee(); i++){
		if (e[i]->getState()==ObjectState::WORK && e[i]->getName()=="Feeder"){
			active_employees++;
		} // Object::getState()
		else if (e[i]->getName()=="Cow"){
			moo++;
		}
	}
	delete []e; // since 'new' was called in getConstEmployeeList

	return profit * (moo > active_employees ? active_employees: moo);
}

char Cattlefarm::getSymbol() const{
	return 'C';
}

string Cattlefarm::getName() const{
	string str1 = "Cattlefarm";
	return str1;
}

// deletes all cows that arent alive
void Cattlefarm::removeDiedCow(){
	bool nodeadcows = false;
	while (nodeadcows==false){
		const Employee ** e;
		nodeadcows = true;
		getConstEmployeeList(e);
		for (int i=0; i<getNumEmployee(); i++){
			if (dynamic_cast<const Cow *>(e[i]) != nullptr){
				if (dynamic_cast<const Cow *>(e[i])->isAlive()==false){
					fireEmployee(const_cast<Cow *>(dynamic_cast<const Cow *>(e[i])));
					nodeadcows = false;
					break;
				}
			}
		}
		delete []e;
	}
}
