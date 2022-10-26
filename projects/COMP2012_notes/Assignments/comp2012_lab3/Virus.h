//TODO: Class declaration of Virus


#ifndef VIRUS_H
#define VIRUS_H

#include <string>

class Virus {
private:
	std::string name;
public:
	Virus(const std::string& vname);
	std::string get_name() const;
};

#endif
