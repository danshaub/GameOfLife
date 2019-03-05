/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#include "board.h"
#include "cell.h"
#include "classic.h"
#include "doughnut.h"
#include "edge_type.h"
#include "game.h"
#include "mirror.h"
#include "randomizer.h"
#include "game_reader.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

Game::Game(){
    game_board_ = new Board();
    display_type_ = 0;
}

Game::Game(EdgeType *game_edge_type, string input_file_name, int display_type){
    game_board_ = new Board(game_edge_type, new GameReader(input_file_name));
    display_type_ = display_type;
}

Game::Game(EdgeType *game_edge_type, Randomizer *board_randomizer, int display_type){
    game_board_ = new Board(game_edge_type, board_randomizer);
    display_type_ = display_type;
}

Game::~Game(){
    delete game_board_;
}

void Game::Simulate(){
    Display();
}

void Game::Display(){
    if(display_type_ == 0){
        DisplayAuto();
    }
    else if(display_type_ == 1){
        DisplayManual();
    }
    else if(display_type_ == 2){
        DisplayToFile();
    }
}

void Game::DisplayAuto(){
    int stable_generations = 0;
    string old_generation = "";
    string new_generation = game_board_->ToString();

    for(int i = 0; i < max_generations_ && stable_generations < 5; i++){
        this_thread::sleep_for(chrono::milliseconds(250));
        cout << game_board_->ToString() << endl; 
        game_board_->Iterate();

        old_generation = new_generation;
        new_generation = game_board_->ToString();

        if(SimulationIsStable(old_generation, new_generation)){
            stable_generations++;
        }
        else{
            stable_generations = 0;
        }
    }
}

void Game::DisplayManual(){
    cin.clear();

    int stable_generations = 0;
    string old_generation = "";
    string new_generation = game_board_->ToString();

    for(int i = 0; i < max_generations_ && stable_generations < 5; i++){
        cin.get();
        cout << game_board_->ToString() << endl; 
        game_board_->Iterate();

        old_generation = new_generation;
        new_generation = game_board_->ToString();

        if(SimulationIsStable(old_generation, new_generation)){
            stable_generations++;
        }
        else{
            stable_generations = 0;
        }
    }
}

void Game::DisplayToFile(){
    ofstream output;
    string out_file;
    bool success = false;
    do{
        cout << "Please enter an output file name:  ";
        cin >> out_file;

        output.open(out_file);

        if(output.is_open()){
            cout << "Output file opened successfully" << endl;
            success = true;
        }
        else{
            cout << "File name invalid >> ";
        }
    } while (!success);

    int stable_generations = 0;
    string old_generation = "";
    string new_generation = game_board_->ToString();

    for(int i = 0; i < max_generations_ && stable_generations < 5; i++){
        output << game_board_->ToString() << endl; 
        game_board_->Iterate();
        old_generation = new_generation;
        new_generation = game_board_->ToString();

        if(SimulationIsStable(old_generation, new_generation)){
            stable_generations++;
        }
        else{
            stable_generations = 0;
        }
    }


}

bool Game::SimulationIsStable(string current_gen, string past_gen){
    int index_new_line_current = current_gen.find('\n');
    int index_new_line_past = past_gen.find('\n');

    current_gen = current_gen.substr(index_new_line_current);
    past_gen = past_gen.substr(index_new_line_past);

    return current_gen == past_gen;
}