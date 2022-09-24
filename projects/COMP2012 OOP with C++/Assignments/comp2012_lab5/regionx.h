#ifndef REGIONX_H
#define REGIONX_H

#include "organization.h"

class RegionX : public Organization {
public:
	// Modify the function declarations below

	RegionX(const char* name, int, int);

	virtual ~RegionX();

	virtual void print_description() const override;

	bool report() const override;

private:
	int num_patient;
	int num_death;


};

#endif
