//TODO: Class declaration of Coronavirus


#ifndef CORONAVIRUS_H
#define CORONAVIRUS_H

#include <string>
#include "Virus.h"

class Coronavirus : public Virus {
private:
	std::string genus;
public:
	Coronavirus(const std::string& vname, const std::string& vgenus);
	std::string get_genus() const;
};

#endif
