#ifndef REGIONY_H
#define REGIONY_H

#include "organization.h"

class RegionY : public Organization {
public:
	// Modify the function declarations below

	RegionY(const char* name, int, int);

	virtual ~RegionY();

	virtual void print_description() const override;

	bool report() const override;

private:
	int num_patient;
	int num_death;

};

#endif
