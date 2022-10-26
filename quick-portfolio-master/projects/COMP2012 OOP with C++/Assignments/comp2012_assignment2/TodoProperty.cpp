/*
 * File Created: Sun Mar 15 2020
 * Author: Chow Hau Cheung Jasper
 * SID: 20589533
*/

#include "Property.h"
#include "Employee.h"

void Property::writeToStream(ostream& os) const {
	Object::writeToStream(os);
	os << "Cost:" << getCost() << endl;
    os << "Upgrade Cost:" << getUpgradeCost() << endl;
    os << "Level:" << getLevel() << endl;
    os << "# of Employee:" << getNumEmployee() << " / " << getMaxNumEmployee() << endl;
}

void Property::upgrade() {
    m_level++;
}

void Property::getConstEmployeeList(const Employee**& employee) const {
	if (m_num_employee == 0) {
		employee =nullptr;
		return;
	}
	employee = new const Employee*[m_num_employee];
	for (int i = 0; i < m_num_employee; i++)
		employee[i] = m_employee_list[i];
}

// TODO: Start to implement your code.

Property::Property(int x, int y, int z) : m_cost(x), m_upgrade_cost(y), m_max_num_employee(z) {

}

Property::~Property(){
	if (m_employee_list!=nullptr){
		for (int i=0; i<m_num_employee; i++){
			delete m_employee_list[i];
		}
		delete []m_employee_list;
	}
}

int Property::getCost() const{
	return m_cost;
}

int Property::getUpgradeCost() const{
	return m_upgrade_cost;
}

int Property::getLevel() const{
	return m_level;
}

int Property::getNumEmployee() const{
	return m_num_employee;
}

int Property::getMaxNumEmployee() const{
	return m_max_num_employee;
}

void Property::setMaxNumEmployee(int z) {
	m_max_num_employee = z;
}

bool Property::assignEmployee(Employee * emp){
	if (getMaxNumEmployee() == getNumEmployee()){
		return false; // over the max number of employees
	}
	if (!checkEmployee(emp)){ // employee not ok for this property type
		return false;
	}
	for (int i=0; i<m_num_employee; i++){
		if (m_employee_list[i]==emp){ // already in this employee list
			return false;
		}
	}

	int x,y;
	getXY(x, y); // return by reference x,y of this property
	int sizex, sizey;
	getSize(sizex, sizey); // return by reference size of property
	if (m_employee_list==nullptr){
		m_employee_list = new Employee * [1];
		m_employee_list[0]=emp;
		emp->setXY(x+1, y+1); // first available cell
		m_num_employee++;
		emp->updateState(); // make them work
	}
	else{
		Employee ** newemployeelist = new Employee * [m_num_employee+1];
		for (int i=0; i<m_num_employee; i++){
			newemployeelist[i]=m_employee_list[i];
		}
		newemployeelist[m_num_employee]=emp;

		emp->updateState(); // make them work

		// fill out column by column
		int a, b;

		// x-coordinate for every (sizey-2) employees the same
		// y-coordinate for employees 1,3,5 the same, depends on {number of employees mod (sizey-2)}
		// XXXXX
		// X147X
		// X258X
		// X369X
		// XXXXX

		a = (m_num_employee+1) / (sizey-2); // if this is equal to 0 this is the last employee to fit in the column
		if (((m_num_employee+1) % (sizey-2))!=0){a++;}

		b = (m_num_employee+1) % (sizey-2);
		if (b==0){b = b+(sizey-2);} // then this is the last employee that can fit in this column

		//cout <<"Branch 2b: " << a << " " << x << " " << b << " " << y << endl;
		emp->setXY(x+a, y+b);

		// deallocate old memory
		delete [] m_employee_list;

		m_num_employee++;  // update number of employees
		m_employee_list = newemployeelist;
	}
	return true;
}

bool Property::fireEmployee(Employee* emp){
	if (m_employee_list==nullptr){
		return false;
	}

	if (m_num_employee==1){
		// must reset to nullptr
		delete []m_employee_list;
		m_employee_list = nullptr;
		m_num_employee--;
	}
	else{
		int del_index = -1;
		int skip =0;
		Employee ** newemployeelist = new Employee * [m_num_employee-1];

		// make the new employee list dynamic array
		for (int i=0; i<m_num_employee; i++){
			if (emp==m_employee_list[i]){
				del_index = i;
				skip=1;
			}
			else{
				newemployeelist[i-skip]=m_employee_list[i];
			}
		}

		int x,y;
		getXY(x, y); // return by reference x,y of this property
		int sizex, sizey;
		getSize(sizex, sizey); // return by reference size of property

		// fix x, y coordinates of all employees AFTER the fired employee
		for (int i=del_index; i<m_num_employee-1; i++){
			int my_x, my_y;
			newemployeelist[i]->getXY(my_x, my_y);
			if (my_y-1==sizey+y){ // if this would make the employee sit on the border, reduce x, and make y the maximum value such that it still is not touching border
				newemployeelist[i]->setXY(my_x - 1, my_y + sizey - 1);
			}
			else{
				newemployeelist[i]->setXY(my_x, my_y - 1);
			}
		}

		// deallocate old memory
		delete [] m_employee_list;

		m_num_employee--;  // update number of employees
		m_employee_list = newemployeelist;
		delete emp; // if i dont call this i get 3 memory leak. if i do program crashes on some output
		emp = nullptr;

	}

	return true;
}
