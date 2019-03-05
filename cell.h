/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

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

        //Accepts a boolean and sets the state of the cell
        //to alive if true and dead if false
        void SetIsAlive(bool b);

        //Returns true if the cell is alive and false if dead
        bool GetIsAlive();
};

#endif //CELL_H