#include <iostream>
#include "Patient_with_norovirus.h"
#include "Norovirus.h"
using namespace std;

//TODO: complete the constructor of Patient_with_norovirus
Patient_with_norovirus::Patient_with_norovirus(const string& pname, int page, const string& norovirus_name, const string& norovirus_genogroup) : norovirus(norovirus_name, norovirus_genogroup), Patient(pname, page) {}

//TODO: complete Patient_with_norovirus::print_virus_info
void Patient_with_norovirus::print_virus_info() const {
    //print "{name} is infected with {the name of the virus}, which belongs to G{the number of genogroup} genogroup."
	cout << this->get_name() << " is infected with " << this->norovirus.get_name() << ", which belongs to G" << this->norovirus.get_genogroup() << " genogroup." << endl;
}
