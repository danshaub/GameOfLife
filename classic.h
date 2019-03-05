/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#ifndef CLASSIC_H
#define CLASSIC_H

#include "Cell.h"
#include "edge_type.h"
#include <iostream>
using namespace std;

class Classic: public EdgeType{
    public:
        //default constructor
        Classic();

        //default destructor
        ~Classic();

        //Returns a reference to the next generation
        Cell** Iterate(Cell** old_generation, int width, int height);
};

#endif //CLASSIC_H