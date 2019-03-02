#ifndef CELL_H
#define CELL_H

#include <iostream>
using namespace std;

class Cell{
    private:
        //Keeps track of state of cell
        bool is_alive_;

    public:
        //Default Constructor
        Cell();

        //Constructs object with initial state
        Cell(bool a);

        //Destructs Cell object
        ~Cell();

        //Given rules of game of life, changes state of cell depending 
        //on its current state and the passed number of neighbors
        bool UpdateGeneration(int neighbors);

        void SetIsAlive(bool b);

        bool GetIsAlive();
};

#endif //CELL_H