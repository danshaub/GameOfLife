#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "cell.h"
#include "classic.h"
#include "doughnut.h"
#include "edge_type.h"
#include "mirror.h"
#include "randomizer.h"
/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#include "game_reader.h"
#include <iostream>

class Game{
    private:
        Board *game_board_;

        //0-automatic with a pause
        //1-manual
        //2-output to file
        int display_type_; 
        const int MAX_GENERATIONS__ = 1000;

        //Displays the simulation in the console with automatic timing
        void DisplayAuto();

        //Displays the simulation in the console with manual timing
        void DisplayManual();

        //Displays the entire simulation to an output file
        //that is asked for at this function call
        void DisplayToFile();

        //Returns true if both passed string representations
        //of the current and past simulation are equivilant
        bool SimulationIsStable(string current_gen, string past_gen);

    public:
        //Default Constructor: Auto displaying default board
        Game();

        //Overloaded Constructor for use with reading from an imput file
        //Accepts a string representing the input file name
        Game(EdgeType *game_edge_type, string input_file_name, int display_type);

        //Overloaded Constructor for use with randomizing the starting board
        //Accepts a randomizer object pointer
        Game(EdgeType *game_edge_type, Randomizer *board_randomizer, int display_type);

        //Default Destructor
        ~Game();

        //Calls the correct display function based
        //on the int display_type_
        void Simulate();

};

#endif //GAME_H