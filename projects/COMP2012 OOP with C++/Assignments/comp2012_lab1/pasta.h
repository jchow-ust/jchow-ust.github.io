/*
 * pasta.h
 *
 *  Created on: 6 Mar 2020
 *      Author: jchow
 */

#include "spaghetti.h"
#include "herb.h"
#include "chicken.h"
#include "cheese.h"
// if the pasta.h classes NOT already defined, define them
// otherwise we would be redefining classes and get a compile error
#ifndef __PASTA_H
#define __PASTA_H


class Pasta {
private:
	Spaghetti *s;
	Herb*h;
	Chicken*k;
	Cheese*c;
public:
    Pasta();
    ~Pasta();
};

#endif
