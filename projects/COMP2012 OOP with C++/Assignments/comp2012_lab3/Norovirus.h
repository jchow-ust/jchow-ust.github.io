//TODO: Class declaration of Norovirus


#ifndef NOROVIRUS_H
#define NOROVIRUS_H

#include <string>
#include "Virus.h"

class Norovirus : public Virus {
private:
	std::string genogroup;
public:
	Norovirus(const std::string& vname, const std::string& vgenogroup);
	std::string get_genogroup() const;
};

#endif
