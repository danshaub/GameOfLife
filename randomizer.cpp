#include "cell.h"
#include "randomizer.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

Randomizer::Randomizer(){
    hight_ = 10;
    width_ = 10;
    percent_alive_ = .5;
}

Randomizer::Randomizer(int hight, int width, double percent_alive){
    hight_ = hight;
    width_ = width;
    percent_alive_ = percent_alive / 100; 
}

Randomizer::~Randomizer(){

}

Cell** Randomizer::GenerateCellArray(){
    srand(time(0));
    Cell **cells = new Cell *[hight_];

    for(int i = 0; i < hight_; i++){
        cells[i] = new Cell[width_];
        for(int j = 0; j < width_; j++){
            double d = (double)rand()/RAND_MAX;
            bool e = (d <= percent_alive_);
            cells[i][j].SetIsAlive(e);
        }
    }

    return cells;
}

int* Randomizer::getDimensions(){
    int* dim = new int[2];

    dim[0] = hight_;
    dim[1] = width_;

    return dim;
}