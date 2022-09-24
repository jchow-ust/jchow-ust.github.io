#include <iostream>
#include "Patient.h"
using namespace std;


//TODO: complete the constructor of Patient
Patient::Patient(const string& pname, int page) : Person(pname), age(page){
}

//TODO: complete Patient::get_age
int Patient::get_age() const {
	return this->age;
}
