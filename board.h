#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "classic.h"
#include "doughnut.h"
#include "edge_type.h"
#include "mirror.h"
#include "randomizer.h"
#include "game_reader.h"
#include <iostream>

class Board{
    private: 
        Cell** generation_; 
        EdgeType *board_edge_type_; 
        Randomizer *board_randomizer_; 
        GameReader *file_reader_; 
        int hight_; 
        int width_;
        int generation_number_ = 0;
    
    public:
        //Default Constructor
        //10 by 10 grid, randomized (50% alive)
        //classic edge type
        Board();

        //Overloaded Constructor
        //Chosen edge type, chosen randomizer specifications
        Board(EdgeType *board_edge_type, Randomizer *board_randomizer);

        //Overloaded Constructor
        //Chosen edge type, chorsen file reader
        Board(EdgeType *board_edge_type, GameReader *file_reader);

        //Default Destructor
        ~Board();

        //calls EdgeType.Iterate(Cell[][] generation)
        //updates generation_ accodringly
        void Iterate();

        //gives a string representation of the board's generation_
        string ToString();


};

#endif //BOARD_H