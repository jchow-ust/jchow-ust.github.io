/*
 * regiony.cpp
 *
 *  Created on: 12 Apr 2020
 *      Author: jchow
 */

#include <iostream>
#include <cstring>
#include <iomanip>

#include "regiony.h"

using namespace std;

RegionY::RegionY(const char* name, int np, int nd) : Organization(name), num_patient(np), num_death(nd)
{}

RegionY::~RegionY()
{
	cout << "RegionY Dtor" << endl;
}

void RegionY::print_description() const
{
	Organization::print_description();
	cout << " Type: RegionY" << endl;
}

bool RegionY::report() const{
	double deathrate = static_cast<double>(num_death*100)/static_cast<double>(num_patient);
	if (deathrate <= 4){
		cout << "Death rate: " << setprecision(3) << deathrate << "% <= 4%, not severe!" << endl;
		return false;
	}
	cout << "Death rate: " << setprecision(3) << deathrate << "% > 4%, severe!" << endl;
	return true;
}





