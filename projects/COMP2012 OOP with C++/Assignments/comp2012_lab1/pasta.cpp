/*
 * pasta.cpp
 *
 *  Created on: 6 Mar 2020
 *      Author: jchow
 */


#include "pasta.h"
#include <iostream>
using namespace std;

Pasta::Pasta() {
	s = new Spaghetti;
	h = new Herb;
	k = new Chicken;
	c = new Cheese;
    cout << "Make Pasta!" << endl;
}
Pasta::~Pasta() {
    delete s;
    delete h;
    delete k;
    delete c;
}
