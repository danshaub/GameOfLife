/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#include "cell.h"
#include <iostream>
using namespace std;


//Default constructor
Cell::Cell(){
    is_alive_ = false;
}
//Constructs object with initial state
Cell::Cell(bool is_alive){
    is_alive_ = is_alive;
}

//Destructs Cell object
Cell::~Cell(){

}

//Given rules of game of life, changes state of cell depending 
//on its current state and the passed number of neighbors
//returns true if cell will be alive
bool Cell::UpdateGeneration(int neighbors){
    //isolation or overpopulation
    if(neighbors < 2 || neighbors > 3){
        return false;
    }

    //stable amount of neighbors
    else if(neighbors == 2){
        return is_alive_;
    }

    //generative abount of neighbors
    else if(neighbors == 3){
        return true;
    }
}

//Accepts a boolean and sets the state of the cell
//to alive if true and dead if false
void Cell::SetIsAlive(bool b){
    is_alive_ = b;
}

//Returns true if the cell is alive and false if dead
bool Cell::GetIsAlive(){
    return is_alive_;
}