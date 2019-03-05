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

Randomizer::Randomizer(){
    height_ = 10;
    width_ = 10;
    percent_alive_ = .5;
}

Randomizer::Randomizer(int height, int width, double percent_alive){
    height_ = height;
    width_ = width;
    percent_alive_ = percent_alive / 100; 
}

Randomizer::~Randomizer(){

}

Cell** Randomizer::GenerateCellArray(){
    srand(time(0));
    Cell **cells = new Cell *[height_];

    for(int i = 0; i < height_; i++){
        cells[i] = (Cell*)malloc(width_ * sizeof(Cell));
        for(int j = 0; j < width_; j++){
            double d = (double)rand()/RAND_MAX;
            bool e = (d <= percent_alive_);
            cells[i][j].SetIsAlive(e);
        }
    }

    return cells;
}

int* Randomizer::GetDimensions(){
    int* dim = new int[2];

    dim[0] = height_;
    dim[1] = width_;

    return dim;
}