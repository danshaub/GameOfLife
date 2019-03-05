/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#ifndef EDGE_TYPE_H
#define EDGE_TYPE_H

#include "cell.h"
#include <iostream>
using namespace std;

class EdgeType{
    public:
        //Default Constructor (unused)
        EdgeType();

        //Default Destructor (unused)
        ~EdgeType();

        //Virtual Function that contains logic for generation calculations
        virtual Cell** Iterate(Cell** old_generation, int width, int height) = 0;
};

#endif // EDGE_TYPE_H