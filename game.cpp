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

//Default Constructor: Auto displaying default board
Game::Game(){
    game_board_ = new Board();
    display_type_ = 0;
}

//Overloaded Constructor for use with reading from an imput file
//Accepts a string representing the input file name
Game::Game(EdgeType *game_edge_type, string input_file_name, int display_type){
    game_board_ = new Board(game_edge_type, new GameReader(input_file_name));
    display_type_ = display_type;
}

//Overloaded Constructor for use with randomizing the starting board
//Accepts a randomizer object pointer
Game::Game(EdgeType *game_edge_type, Randomizer *board_randomizer, int display_type){
    game_board_ = new Board(game_edge_type, board_randomizer);
    display_type_ = display_type;
}

//Default Destructor
Game::~Game(){
    delete game_board_;
}

//Calls the correct display function based
//on the int display_type_
void Game::Simulate(){
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

//Displays the simulation in the console with automatic timing
void Game::DisplayAuto(){
    //used to keep track of the stability of the simulation
    int stable_generations = 0;
    string old_generation = "";
    string new_generation = game_board_->ToString();

    //For as many generations as specified in MAX_GENERATIONS
    //or until the simulation becomes stable
    for(int i = 0; i < MAX_GENERATIONS__ && stable_generations < 5; i++){
        //sleep for .25 seconds
        this_thread::sleep_for(chrono::milliseconds(250));

        cout << game_board_->ToString() << endl; 

        game_board_->Iterate();

        //update old and new generation strings
        old_generation = new_generation;
        new_generation = game_board_->ToString();

        //check the stability using bool SimulationIsStable()
        if(SimulationIsStable(old_generation, new_generation)){
            stable_generations++;
        }
        else{
            stable_generations = 0;
        }
    }
}

//Displays the simulation in the console with manual timing
void Game::DisplayManual(){
    //cin used for manual generation timing and is required to be cleared
    cin.clear();

    //used to keep track of the stability of the simulation
    int stable_generations = 0;
    string old_generation = "";
    string new_generation = game_board_->ToString();

    //For as many generations as specified in MAX_GENERATIONS
    //or until the simulation becomes stable
    for(int i = 0; i < MAX_GENERATIONS__ && stable_generations < 5; i++){
        //wait until the user presses enter
        cin.get();

        cout << game_board_->ToString() << endl; 
        game_board_->Iterate();

        
        old_generation = new_generation;
        new_generation = game_board_->ToString();

        //check the stability using bool SimulationIsStable()
        if(SimulationIsStable(old_generation, new_generation)){
            stable_generations++;
        }
        else{
            stable_generations = 0;
        }
    }
}

//Displays the entire simulation to an output file
//that is asked for at this function call
void Game::DisplayToFile(){
    //declares output steam and file name string
    ofstream output;
    string out_file;

    //asks user for a file name for the output  
    //of the simulation until a valid one is given
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

    //used to keep track of the stability of the simulation
    int stable_generations = 0;
    string old_generation = "";
    string new_generation = game_board_->ToString();

    //For as many generations as specified in MAX_GENERATIONS
    //or until the simulation becomes stable
    for(int i = 0; i < MAX_GENERATIONS__ && stable_generations < 5; i++){
        output << game_board_->ToString() << endl; 
        game_board_->Iterate();

        //update old and new generation strings
        old_generation = new_generation;
        new_generation = game_board_->ToString();

        //check the stability using bool SimulationIsStable()
        if(SimulationIsStable(old_generation, new_generation)){
            stable_generations++;
        }
        else{
            stable_generations = 0;
        }
    }
}

//Returns true if current_gen and past_gen are equal
//after their first line (generation number)
bool Game::SimulationIsStable(string current_gen, string past_gen){
    //gets the starting index of the second line
    int index_new_line_current = current_gen.find('\n');
    int index_new_line_past = past_gen.find('\n');

    //trims the generation number off the front of the
    //string suing the index found above
    current_gen = current_gen.substr(index_new_line_current);
    past_gen = past_gen.substr(index_new_line_past);
    
    return current_gen == past_gen;
}