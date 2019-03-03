#include "cell.h"
#include "classic.h"
#include "edge_type.h"
#include <iostream>

Classic::Classic(){

}

Classic::~Classic(){

}

Cell** Classic::Iterate(Cell** old_generation, int hight, int width){
    Cell** new_generation = new Cell *[hight];

    for (int i = 0; i < hight; i++){
        new_generation[i] = new Cell[width];
    }
    //iterates through each row of the array
    for(int row = 0; row < hight; row++){
        //iterates through each column of the array
        for(int col = 0; col < width; col++){
            //keeps track of number of alive neighbors for current element
            int neighbors = 0;
            //iterates through surrounding elements
            for(int i = row - 1; i <= row + 1; i++){
                for(int j = col - 1; j <= col + 1; j++){
                    //if current [i][j] element is the same
                    //as the current [row][col] element, continue
                    if(row == i && col == j){
                        continue;
                    }

                    if((0 <= i && i < hight) && (0 <= j && j < width)) {
                        neighbors+=old_generation[i][j].GetIsAlive();
                    }
                }
            }
            //sets the new generation current element to be the
            //old generation's updated form given the number of neighbors
            new_generation[row][col].SetIsAlive(old_generation[row][col].UpdateGeneration(neighbors));
        }
    }
    return new_generation;
}