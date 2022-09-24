#include "dough.h"
#include "chicken.h"
#include "cheese.h"

#ifndef __PIZZA_H
#define __PIZZA_H
class Pizza {
public:
    Pizza();
    ~Pizza();
private:
    Dough* d;
    Chicken* c; 
    Cheese* cheese; 
};
#endif
