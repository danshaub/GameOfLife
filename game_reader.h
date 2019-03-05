/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#ifndef GAME_READER_H
#define GAME_READER_H

#include "cell.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class GameReader{
    private:
        //holds string associated with file name
        string input_file_name_;

        //file reader object
        ifstream file_input_stream_;
    
    public:
        //Default constructor, doesn't initialize anything.
        GameReader();
        // Takes a string as a parameter and initializes
        // file_input_stream_ with the string as its file name
        GameReader(string f);

        // default destructor
        ~GameReader();

        // returns true if file_input_stream is open
        bool InStreamIsOpen();

        // Takes a string as a parameter and initializes
        // file_input_stream_ with the string as its file name
        // returns true if file_input_stream_ opens
        bool SetFileName(string f);

        //Returns file_input_stream_ to the beginning
        //of the input file.
        void ReturnToFileStart();

        //Returns true if input file is written in the 
        //correct format with one number on the first two
        //lines and a grid of 'X' and '-' with the specified
        //dimentions (or larger) below
        bool FileFormatIsValid();

        //Reads the two numbers at the top of the file
        //and returns them in an int[2]
        //height will be index 0 and width will be index 1s
        int* ReadDimensions();

        //Reads 2D array of cells from input file
        //and returns it 
        Cell** ReadCells();

};

#endif //GAME_READER_H