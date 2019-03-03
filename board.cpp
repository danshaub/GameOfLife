#include "cell.h"
#include "classic.h"
#include "doughnut.h"
#include "edge_type.h"
#include "mirror.h"
#include "randomizer.h"
#include "game_reader.h"
#include "board.h"
#include <iostream>



Board::Board(){
    hight_ = 10;
    width_ = 10;

    board_randomizer_ = new Randomizer(hight_, width_, 50);
    
    board_edge_type_ = new Classic();

    generation_ = new Cell*[hight_];

    for (int i = 0; i < hight_; i++){
        generation_[i] = new Cell[width_];
    }

    generation_ = board_randomizer_->GenerateCellArray();
}

Board::Board(EdgeType *board_edge_type, Randomizer *board_randomizer){
    board_edge_type_ = board_edge_type;
    board_randomizer_ = board_randomizer;

    hight_ = board_randomizer_->getDimensions()[0];
    width_ = board_randomizer_->getDimensions()[1];

    generation_ = new Cell*[hight_];

    for(int i = 0; i < hight_; i++){
        generation_[i] = new Cell[width_];
    }

    generation_ = board_randomizer_->GenerateCellArray();
}

Board::Board(EdgeType *board_edge_type, GameReader *file_reader){
    board_edge_type_ = board_edge_type;
    file_reader_ = file_reader;

    hight_ = file_reader_->ReadDimensions()[0];
    width_ = file_reader_->ReadDimensions()[1];

    generation_ = new Cell*[hight_];

    for (int i = 0; i < hight_; i++){
        generation_[i] = new Cell[width_];
    }

    generation_ = file_reader_->ReadCells();
}

Board::~Board(){
    for(int i = 0; i < hight_; i++){
        delete[] generation_[i];
    }
    delete board_edge_type_;
    delete board_randomizer_;
    delete file_reader_;
}


void Board::Iterate(){
    generation_ = board_edge_type_->Iterate(generation_, hight_, width_);
    generation_number_++;
}

string Board::ToString(){
    string s = "";
    s += to_string(generation_number_); 
    s += "\n";
    for(int i = 0; i < hight_; i++){
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
