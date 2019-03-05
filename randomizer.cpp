/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#include "cell.h"
#include "randomizer.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

//Default Constructor (10-10 grid 50% alive)
Randomizer::Randomizer(){
    height_ = 10;
    width_ = 10;
    percent_alive_ = .5;
}

//Overloaded Constructor
//Takes height, width as a parameter
Randomizer::Randomizer(int height, int width, double percent_alive){
    height_ = height;
    width_ = width;
    percent_alive_ = percent_alive / 100; 
}

//Default Destructor
Randomizer::~Randomizer(){

}

//Returns a reference to a random 2D array of Cells
//with the specified dimensions
Cell** Randomizer::GenerateCellArray(){
    //Sets random seed based on the current time
    srand(time(0));

    //initializes Array of Cell Arrays that is "height" long
    Cell **cells = new Cell *[height_];

    //for each element of the Array of Cell Arrays...
    for(int i = 0; i < height_; i++){
        //initialize the current element of the Array of Cell Arrays with
        //the exact size required for an Array of Cells of length "width".
        cells[i] = (Cell*)malloc(width_ * sizeof(Cell));

        //for each individual cell, set its state equal to
        //a random state with the desired probability
        for(int j = 0; j < width_; j++){
            double d = (double)rand()/RAND_MAX;
            bool e = (d <= percent_alive_);
            cells[i][j].SetIsAlive(e);
        }
    }

    return cells;
}

//Returns an int array of length 2 that
//stores the dimensions of the 2D array
int* Randomizer::GetDimensions(){
    int* dim = new int[2];

    dim[0] = height_;
    dim[1] = width_;

    return dim;
}