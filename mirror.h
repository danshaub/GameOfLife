/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#ifndef MIRROR_H
#define MIRROR_H

#include "Cell.h"
#include "edge_type.h"
#include <iostream>
using namespace std;

class Mirror: public EdgeType{
    public:
        //default constructor
        Mirror();

        //default destructor
        ~Mirror();

        //Returns a reference to the next generation
        Cell** Iterate(Cell** old_generation, int width, int height);
};

#endif //MIRROR_H