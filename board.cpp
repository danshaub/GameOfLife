/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#include "cell.h"
#include "classic.h"
#include "doughnut.h"
#include "edge_type.h"
#include "mirror.h"
#include "randomizer.h"
#include "game_reader.h"
#include "board.h"
#include <iostream>

//Default Constructor
//10 by 10 grid, randomized (50% alive)
//classic edge type
Board::Board(){
    height_ = 10;
    width_ = 10;

    board_randomizer_ = new Randomizer(height_, width_, 50);
    
    board_edge_type_ = new Classic();

    //Cell** initialization
    generation_ = new Cell*[height_];
    for (int i = 0; i < height_; i++){
        generation_[i] = new Cell[width_];
    }

    generation_ = board_randomizer_->GenerateCellArray();
}

//Overloaded Constructor
//Chosen edge type, chosen randomizer specifications
Board::Board(EdgeType *board_edge_type, Randomizer *board_randomizer){
    board_edge_type_ = board_edge_type;
    board_randomizer_ = board_randomizer;

    //sets height_ and width_ equal to the dimensions
    //contained in the randomizer object
    height_ = board_randomizer_->GetDimensions()[0];
    width_ = board_randomizer_->GetDimensions()[1];

    //Cell** initialization
    generation_ = new Cell*[height_];
    for(int i = 0; i < height_; i++){
        generation_[i] = new Cell[width_];
    }

    generation_ = board_randomizer_->GenerateCellArray();
}

//Overloaded Constructor
//Chosen edge type, chorsen file reader
Board::Board(EdgeType *board_edge_type, GameReader *file_reader){
    board_edge_type_ = board_edge_type;
    file_reader_ = file_reader;

    //Reads Dimensions from the GameReader object
    //and puts them in height_ and width_
    height_ = file_reader_->ReadDimensions()[0];
    width_ = file_reader_->ReadDimensions()[1];

    //Cell** initialization
    generation_ = new Cell*[height_];
    for (int i = 0; i < height_; i++){
        generation_[i] = new Cell[width_];
    }

    generation_ = file_reader_->ReadCells();
}

//Default Destructor
Board::~Board(){
    //Deletes all rows of the board array
    for(int i = 0; i < height_; i++){
        delete[] generation_[i];
    }

    //Deletes the rest of the objects contained within this board
    delete board_edge_type_;
    delete board_randomizer_;
    delete file_reader_;
}

//calls EdgeType.Iterate(Cell[][] generation)
//updates generation_ accodringly
void Board::Iterate(){
    generation_ = board_edge_type_->Iterate(generation_, height_, width_);
    generation_number_++;
}

//gives a string representation of the board's current generation
string Board::ToString(){
    string s = "";
    s += to_string(generation_number_); 
    s += "\n";
    for(int i = 0; i < height_; i++){
        for(int j = 0; j < width_; j++){
            if(generation_[i][j].GetIsAlive()){
                s += "X";
            }
            else{
                s += "-";
            }
        }
        s += "\n";   
    }
    return s;
}
