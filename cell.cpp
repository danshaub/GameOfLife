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
    if(neighbors < 2 || neighbors > 3){
        return false;
    }
    else if(neighbors == 2){
        return is_alive_;
    }
    else if(neighbors == 3){
        return true;
    }
}

void Cell::SetIsAlive(bool b){
    is_alive_ = b;
}

bool Cell::GetIsAlive(){
    return is_alive_;
}