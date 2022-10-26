//TODO: Class declaration of Doctor

//define the const int MAX_NUM_OF_PATIENTS to be 15 here

#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
const int MAX_NUM_OF_PATIENTS = 15;
#include "Person.h"
#include "Patient.h"

class Doctor : public Person {
private:
    Patient const * patient_list [MAX_NUM_OF_PATIENTS];
    int num_of_patients;
public:
    Doctor(const std::string& pname);
    void responsible_for(Patient const * patient);
    void print_patient_name_list() const;
};

#endif
