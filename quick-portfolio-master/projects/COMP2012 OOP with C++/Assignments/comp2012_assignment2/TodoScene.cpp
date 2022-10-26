/*
 * File Created: Mon Mar 16 2020
 * Author: Chow Hau Cheung Jasper
 * SID: 20589533
*/

#include "Scene.h"
#include "Property.h"
#include "TodoFarmland.h"
#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoFarmer.h"
#include "TodoFeeder.h"
#include "TodoCow.h"

const int SCENE_W = 45;
const int SCENE_H = 10;
const int PROPERTY_X = 35;
const int SCENE_INIT_MONEY = 200;

Scene::Scene()
: m_objects(nullptr), m_num_objects(0), m_money(SCENE_INIT_MONEY) {
    nextRound();
}

Scene::~Scene() {
    //shallowremove employees
    for(int i = m_num_objects-1; i >= 0; i--) {
        if (m_objects[i]->getObjectType()==ObjectType::EMPLOYEE)
            shallowRemoveEmployee(dynamic_cast<Employee*>(m_objects[i]));
    }
    // remove properties
    for(int i = m_num_objects-1; i >= 0; i--) {
        if (m_objects[i]->getObjectType()==ObjectType::PROPERTY)
            delete m_objects[i];
    }
    delete[] m_objects;
}

void Scene::shallowRemoveEmployee(Employee* e) {
    if (m_num_objects <= 0) return;
    if (m_num_objects == 1 && e == m_objects[0]) {
        m_num_objects = 0;
        m_objects = nullptr;
        return;
    }
    int i;
	for (i = 0; i < m_num_objects; i++) {
		if (m_objects[i] == e)
			break;
	}
    Object ** newObjects = new Object*[m_num_objects--];
	for (int j = 0; j < m_num_objects; j++)
		newObjects[j] = m_objects[j];
	if (m_num_objects != i)
		newObjects[i] = m_objects[m_num_objects];
    delete [] m_objects;
    m_objects = newObjects;
}

bool Scene::checkOverlap(const Property* newproperty) {
    int x, y, sz_x, sz_y;
    newproperty->getXY(x, y);
    newproperty->getSize(sz_x, sz_y);
    for(int xx=x; xx<x+sz_x; xx++)
        for(int yy=y; yy<y+sz_y; yy++)
            if(getObjectAt(xx, yy) != nullptr) return true;
    return false;
}


void Scene::addProperty(int property, int x, int y) {
    Property* newProperty = nullptr;
    switch(property) {
    case FARMLAND:
        newProperty = new Farmland(x,y);
        break;
    case CATTLEFARM:
        newProperty = new Cattlefarm(x, y);
        break;
    }
    if (newProperty == nullptr) return;
    if (newProperty->getCost() > m_money || checkOverlap(newProperty)) {
        delete newProperty;
        return;
    }
    addObject(newProperty);
    m_money -= newProperty->getCost();
}


bool Scene::hire(Property* p, int employee) {
    Employee* newEmployee = nullptr;
    switch(employee){
    case EMPLOYEE:
        newEmployee = new Employee();
        break;
    case FARMER:
        newEmployee = new Farmer();
        break;
    case FEEDER:
        newEmployee = new Feeder();
        break;
    case COW:
        newEmployee = new Cow();
        break;
    }
    if (newEmployee == nullptr) return false;
    if (newEmployee->getCost() > m_money || ! p->assignEmployee(newEmployee)) {
        delete newEmployee;
        return false;
    }
    addObject(newEmployee);
    m_money -= newEmployee->getCost();
    return true;
}


Object* Scene::getObjectAt(int s_x, int s_y) const {
	int x, y, sz_x, sz_y;
    // If employee is at s_x, s_y, get employee
    // else, get property
    // otherwise return null
	for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::PROPERTY)
            continue;
		m_objects[i]->getXY(x,y);
        m_objects[i]->getSize(sz_x,sz_y);
        if ( s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
			return m_objects[i];
	}
	for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::EMPLOYEE)
            continue;
		m_objects[i]->getXY(x,y);
        m_objects[i]->getSize(sz_x,sz_y);
        if ( s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
			return m_objects[i];
	}
	return nullptr;
}

//perform shallow copying
void Scene::addObject(Object* newobj) {
	Object** newobjects = new Object*[m_num_objects + 1];
	for (int i = 0; i < m_num_objects; i++)
		newobjects[i] = m_objects[i];
	newobjects[m_num_objects++] = newobj;
	if (m_num_objects != 1)
		delete [] m_objects;
	m_objects = newobjects;
}

void Scene::getConstObjects(const Object**& obj, int& count) const {
	count = m_num_objects;
	if (m_num_objects == 0) {
		obj =nullptr;
		return;
	}
	obj = new const Object*[m_num_objects];
	for (int i = 0; i < m_num_objects; i++)
		obj[i] = m_objects[i];
}

// TODO: Start to implement your code.


// getMoney already implemented so OK
bool Scene::isGameOver() const{
	return (getMoney() < 0);
}

void Scene::removeProperty(Property * prop){

	if (prop==nullptr){return;}
	if (m_num_objects-1-prop->getNumEmployee()==0){// remove everything
		// deallocate memory
		delete []m_objects;
		delete prop; prop=nullptr; // delete property
		m_objects = nullptr; // reset dangling pointer
		m_num_objects = 0;
		return;
	}

	// total size decreases by 1 (the property to remove) and by number of employees assigned to that property
	Object ** newobjects = new Object * [m_num_objects-1-prop->getNumEmployee()];

	// remove all employees assigned to that property if employee list is not nullptr
	const Employee ** e;
	int skip = 0;
	bool removed = false;
	prop->getConstEmployeeList(e);

	if (e != nullptr){
		for (int i=0; i<m_num_objects; i++){
			removed = false;
			if (m_objects[i]==prop){// remove the property
				skip++; removed = true;
			}
			for (int j=0; j<prop->getNumEmployee(); j++){// remove employees assigned to that property
				if (m_objects[i]==e[j]){
					skip++; removed = true;
					break;
				}
			}
			if (!removed){newobjects[i-skip]=m_objects[i];}
		}
		delete []e; // since 'new' was called in getConstEmployeeList
	}


	// deallocate memory
	delete []m_objects;

	m_objects = newobjects;
	m_num_objects -= (1+prop->getNumEmployee());

	delete prop;
	prop = nullptr; // prevent dangling pointer
}

void Scene::nextRound(){
	// for every property we own, make $
	int profit = 0; int expenses = 0;
	for (int i=0; i<m_num_objects; i++){

		if (m_objects[i]->getObjectType()==ObjectType::PROPERTY){

			// dynamic cast Base -> Derived to call the appropriate makeMoney function

			if (dynamic_cast<Farmland *>(m_objects[i])!=nullptr){
				profit += dynamic_cast<Farmland *>(m_objects[i])->makeMoney();
			}
			else if (dynamic_cast<Cattlefarm *>(m_objects[i])!=nullptr){
				profit += dynamic_cast<Cattlefarm *>(m_objects[i])->makeMoney();
			}
		}

		// compute salary for each employee on each property
		// for each employee update work age and status
		// remove dead cows

		// only works for rest days = 1

		if (m_objects[i]->getObjectType()==ObjectType::EMPLOYEE){

			// employee gets salary
			if (dynamic_cast<Cow *>(m_objects[i])!=nullptr){
				if (dynamic_cast<Cow *>(m_objects[i])->getState()==ObjectState::WORK ||
						dynamic_cast<Cow *>(m_objects[i])->getState()==ObjectState::REST){
					expenses += dynamic_cast<Cow *>(m_objects[i])->getSalary();
				}
				dynamic_cast<Cow *>(m_objects[i])->updateWorkAge();
				if ((dynamic_cast<Cow *>(m_objects[i])->getWorkAge() % (dynamic_cast<Cow *>(m_objects[i])->getNumWorkDays())==0)){
					dynamic_cast<Cow *>(m_objects[i])->updateState();
				}
			}
			else if (dynamic_cast<Farmer *>(m_objects[i])!=nullptr){
				if (dynamic_cast<Farmer *>(m_objects[i])->getState()==ObjectState::WORK ||
						dynamic_cast<Farmer *>(m_objects[i])->getState()==ObjectState::REST){
					expenses += dynamic_cast<Farmer *>(m_objects[i])->getSalary();
				}
				dynamic_cast<Farmer *>(m_objects[i])->updateWorkAge();
				if ((dynamic_cast<Farmer *>(m_objects[i])->getWorkAge() % (dynamic_cast<Farmer *>(m_objects[i])->getNumWorkDays())==0)){
					dynamic_cast<Farmer *>(m_objects[i])->updateState();
				}
			}
			else if (dynamic_cast<Feeder *>(m_objects[i])!=nullptr){
				if (dynamic_cast<Feeder *>(m_objects[i])->getState()==ObjectState::WORK ||
						dynamic_cast<Feeder *>(m_objects[i])->getState()==ObjectState::REST){
					expenses += dynamic_cast<Feeder *>(m_objects[i])->getSalary();
				}
				dynamic_cast<Feeder *>(m_objects[i])->updateWorkAge();
				if ((dynamic_cast<Feeder *>(m_objects[i])->getWorkAge() % (dynamic_cast<Feeder *>(m_objects[i])->getNumWorkDays())==0)){
					dynamic_cast<Feeder *>(m_objects[i])->updateState();
				}
			}
			else if (dynamic_cast<Employee *>(m_objects[i])!=nullptr){
				if (dynamic_cast<Employee *>(m_objects[i])->getState()==ObjectState::WORK ||
						dynamic_cast<Employee *>(m_objects[i])->getState()==ObjectState::REST){
					expenses += dynamic_cast<Employee *>(m_objects[i])->getSalary();
				}
				dynamic_cast<Employee *>(m_objects[i])->updateWorkAge();
				if ((dynamic_cast<Employee *>(m_objects[i])->getWorkAge() % (dynamic_cast<Employee *>(m_objects[i])->getNumWorkDays()) == 0)){
					dynamic_cast<Employee *>(m_objects[i])->updateState();
				}

			}
		}
	}

	m_money -= expenses;
	m_money += profit;
	//cout << expenses << " " << profit << endl;

	// first do a shallow remove to remove pointers to all dead cows in the object list
	int s = m_num_objects;
	for (int j=0; j<s; j++){
		if (dynamic_cast<Cow *>(m_objects[j])!=nullptr){
			if (dynamic_cast<Cow *>(m_objects[j])->isAlive()==false){
				shallowRemoveEmployee(dynamic_cast<Employee *>(m_objects[j]));
				j -= 1;
				s = m_num_objects;
			}
		}
	}

	// then call fire employee to fully deallocate the memory associated with each of those dead cows
	for (int j=0; j<m_num_objects; j++){
		if (dynamic_cast<const Cattlefarm*>(m_objects[j])!=nullptr){
			// removes pointers to Cows from employee lists of each Cattlefarm property
			dynamic_cast<Cattlefarm*>(m_objects[j])->removeDiedCow();
		}
	}
}

bool Scene::upgrade(Property * prop){
	const int CATTLEFARM_UPGRADE_COST = 16; //https://piazza.com/class/k6q1alh7i103cj?cid=309 says they're not going to be changed
	const int FARMLAND_UPGRADE_COST = 10;
	if (prop==nullptr){return false;}
	if (dynamic_cast<Cattlefarm *>(prop)!=nullptr && getMoney()>=CATTLEFARM_UPGRADE_COST){
		dynamic_cast<Cattlefarm *>(prop)->upgrade();
		m_money -= CATTLEFARM_UPGRADE_COST;
		return true;
	}
	if (dynamic_cast<Farmland *>(prop)!=nullptr && getMoney()>=FARMLAND_UPGRADE_COST){
		dynamic_cast<Farmland *>(prop)->upgrade();
		m_money -= FARMLAND_UPGRADE_COST;
		return true;
	}
	return false; // not enough money
}

bool Scene::fire(Employee * emp){
	if (emp==nullptr){return false;}
	bool result = false;
	for(int i =0; i<m_num_objects; i++) {
		if (m_objects[i]->getObjectType()==ObjectType::PROPERTY){
			// since Property is ABC it must be either a Farmland or Cattlefarm from which we are to fire this employee
			Property * prop_pointer = dynamic_cast<Property *>(m_objects[i]);

			const Employee ** e;
			prop_pointer->getConstEmployeeList(e);
			if (e != nullptr){ // cant delete from nullptr list
				for (int i=0; i<prop_pointer->getNumEmployee(); i++){
					if (e[i]==emp){ // if found employee then must be assigned to this property, so fire employee from this property
						result = prop_pointer->fireEmployee(emp);
					}
				}
				shallowRemoveEmployee(emp);
				delete []e; // since 'new' was called in getConstEmployeeList
			}
		}
	}
	return result;
}

