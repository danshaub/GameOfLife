#ifndef EDGE_TYPE_H
#define EDGE_TYPE_H

#include "cell.h"
#include <iostream>
using namespace std;

class EdgeType{
    public:
        //Constructor (default only)
        EdgeType();

        //Destructor
        ~EdgeType();

        //Virtual Function that contains logic for generation calculations
        virtual Cell** Iterate(Cell** old_generation, Cell** new_generation, int width, int hight) = 0;
};

#endif // EDGE_TYPE_H