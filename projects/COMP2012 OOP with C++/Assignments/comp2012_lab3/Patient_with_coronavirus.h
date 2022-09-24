//TODO: Class declaration of Patient_with_coronavirus



#ifndef PATIENT_WITH_CORONAVIRUS_H
#define PATIENT_WITH_CORONAVIRUS_H

#include <string>
#include "Patient.h"
#include "Coronavirus.h"

class Patient_with_coronavirus : public Patient {
private:
	std::string travel_history;
	Coronavirus coronavirus;
public:
	Patient_with_coronavirus(const std::string& pname, int page, const std::string& ptravel_history, const std::string& coronavirus_name, const std::string& coronavirus_genus);
	void print_travel_history() const;
	void print_virus_info() const;
};

#endif
