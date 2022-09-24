#ifndef WHO_H
#define WHO_H

#include "organization.h"

const int MAX_NUM_WATCHLIST = 5;

class WHO: public Organization {
public:
	// Modify the function declarations below

	WHO(const char* name);

	virtual ~WHO();

	virtual void print_description() const override;

	virtual bool report() const override;

	void watch(Organization *);


private:
	Organization *watchlist[MAX_NUM_WATCHLIST];
	int num_watchlist = 0;

};

#endif
