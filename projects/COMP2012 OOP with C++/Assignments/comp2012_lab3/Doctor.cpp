#include <iostream>
#include "Doctor.h"
#include "Person.h"
//#include "Patient.h"
using namespace std;

//TODO: complete the constructor of Doctor
Doctor::Doctor(const string& pname) : Person(pname), num_of_patients(0) {
	for (int i=0; i<MAX_NUM_OF_PATIENTS; i++){
		patient_list[i]=nullptr;
	}
}

//TODO: complete Doctor::responsible_for
void Doctor::responsible_for(Patient const* patient) {
    if (num_of_patients >= MAX_NUM_OF_PATIENTS)
        {cout << "Reach the maximum number of patients." << endl;}
    else{
    	patient_list[num_of_patients] = patient;
    	num_of_patients++;
    	cout << "Doctor " << this->get_name() << " is responsible for patient " << patient->get_name() << "." << endl;
    }
    //add new patient to the end of the patient list
    //increment the number of patients
    //print "Doctor {doctor's name} is responsible for patient {patient's name}."
}

//TODO:complete Doctor::print_patient_name_list
void Doctor::print_patient_name_list() const {
	cout << "Doctor " << this->get_name() << "'s patients:" << endl;
	for (int i=0; i<num_of_patients; i++){
		cout << "Patient " << i << ": " << patient_list[i]->get_name() << ", age " << patient_list[i]->get_age() << endl;
	}
    //print "Doctor {doctor's name}'s patients:\n"
    //print information of each patient like: "Patient {number}: {patient's name}, age {patient's age}\n"
}
