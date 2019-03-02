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
        Cell** Iterate(Cell** old_generation, Cell** new_generation, int width, int hight);
};

#endif //MIRROR_H