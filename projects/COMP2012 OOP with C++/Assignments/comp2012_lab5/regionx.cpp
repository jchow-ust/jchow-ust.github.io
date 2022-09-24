/*
 * regionx.cpp
 *
 *  Created on: 12 Apr 2020
 *      Author: jchow
 */

#include <iostream>
#include <cstring>
#include <iomanip>

#include "regionx.h"

using namespace std;

RegionX::RegionX(const char* name, int np, int nd) : Organization(name), num_patient(np), num_death(nd)
{}

RegionX::~RegionX()
{
	cout << "RegionX Dtor" <<endl;
}

void RegionX::print_description() const
{
	Organization::print_description();
	cout << " Type: RegionX" << endl;
}

bool RegionX::report() const{
	double deathrate = static_cast<double>(num_death*100)/static_cast<double>(num_patient);
	if (deathrate <= 3){
		cout << "Death rate: " << setprecision(3) << deathrate << "% <= 3%, not severe!" << endl;
		return false;
	}
	cout << "Death rate: " << setprecision(3) << deathrate << "% > 3%, severe!" << endl;
	return true;
}


