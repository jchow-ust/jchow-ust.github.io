//TODO: Class declaration of Patient_with_norovirus


#ifndef PATIENT_WITH_NOROVIRUS_H
#define PATIENT_WITH_NOROVIRUS_H

#include <string>
#include "Patient.h"
#include "Norovirus.h"

class Patient_with_norovirus : public Patient {
private:
	Norovirus norovirus;
public:
	Patient_with_norovirus(const std::string& pname, int page, const std::string& norovirus_name, const std::string& norovirus_genogroup);
	void print_virus_info() const;
};

#endif
