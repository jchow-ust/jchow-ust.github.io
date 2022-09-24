/*
 * who.cpp
 *
 *  Created on: 12 Apr 2020
 *      Author: jchow
 */

#include <iostream>
#include <cstring>

#include "who.h"

using namespace std;

WHO::WHO(const char* name) : Organization(name){}

WHO::~WHO()
{
	for (int i=0; i<num_watchlist; i++){
		delete watchlist[i];
	}
	cout << "WHO Dtor" << endl;
}

void WHO::print_description() const
{
	Organization::print_description();
	cout << " Type: WHO" << endl;
}

bool WHO::report() const{
	int severe_regions = 0;
	bool severe = false;
	for (int i=0; i<num_watchlist; i++){
		watchlist[i]->print_description();
		severe = watchlist[i]->report();
		if (severe){
			severe_regions++;
		}
	}

	print_description();

	if (num_watchlist != 0){
		if ((severe_regions / num_watchlist) > 0.5){
			cout << "Severe regions: " << severe_regions << "/" << num_watchlist << ", severe!" << endl;
			return true;
		}
	}
	cout << "Severe regions: " << severe_regions << "/" << num_watchlist << ", not severe!" << endl;
	return false;
}

void WHO::watch(Organization*org){
	if (num_watchlist == MAX_NUM_WATCHLIST){
		return;
	}
	watchlist[num_watchlist] = org;
	num_watchlist++;
}



