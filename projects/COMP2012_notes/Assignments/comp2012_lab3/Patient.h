//TODO: Class declaration of Patient

#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include "Person.h"

class Patient : public Person {
private:
	int age;
public:
    Patient(const std::string &pname, int page);
    int get_age() const;
};

#endif
