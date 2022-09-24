#include "pizza.h"
#include <iostream>
using namespace std;
Pizza::Pizza() {
    c = new Chicken;
    d = new Dough;
    cheese=new Cheese;
    cout << "Make Pizza! " << endl << endl;
}

Pizza::~Pizza() {
    delete c;
    delete d;
    delete cheese;
}
