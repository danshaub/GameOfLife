/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#include "cell.h"
#include "game_reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex> 

using namespace std;

//Default Consturctor
GameReader::GameReader(){

}

// Takes a string as a parameter and initializes
// file_input_stream_ with the string as its file name
GameReader::GameReader(string f){
    if(InStreamIsOpen()){
        file_input_stream_.close();
    }
    input_file_name_ = f;
    file_input_stream_.open(input_file_name_);
}

//Destructs file_input_stream
GameReader::~GameReader(){
    file_input_stream_.close();
}

// returns true if file_input_stream is open
bool GameReader::InStreamIsOpen(){
    return file_input_stream_.is_open();
}

// Takes a string as a parameter and initializes
// file_input_stream_ with the string as its file name
// returns true if file_input_stream_ opens
bool GameReader::SetFileName(string f){
    input_file_name_ = f;
    file_input_stream_.open(input_file_name_);
    return file_input_stream_.is_open();
}

//Returns file_input_stream_ to the beginning
//of the input file.
void GameReader::ReturnToFileStart(){
    file_input_stream_.clear();
    file_input_stream_.seekg(0, file_input_stream_.beg);
}


//Returns true if input file is written in the 
//correct format with one number on the first two
//lines and a grid of 'X' and '-' with the specified
//dimentions below
//Note: a file whose actual grid is larger than the specified
//      dimensions is considered valid
bool GameReader::FileFormatIsValid(){
    ReturnToFileStart();

    int* dimensions = new int[2];
    string line = ""; //placeholder string for file reading
    char bad_char; //used in error messages

    //try-catch block will catch any formatting error
    try{
        //checks first two lines for valid dimensions
        for(int j = 0; j < 2; j++){
            getline(file_input_stream_, line);
            //makes sure each character of the line is a numeric digit
            //if one isn't, an exception is thrown
            for(int i = 0; i < line.length()-1; i++){
                if(!(line[i] == '0'||
                     line[i] == '1'||
                     line[i] == '2'||
                     line[i] == '3'||
                     line[i] == '4'||
                     line[i] == '5'||
                     line[i] == '6'||
                     line[i] == '7'||
                     line[i] == '8'||
                     line[i] == '9')){
                    bad_char = line[i];
                    throw 0; //invalid dimension character exception
                }
            }
            //parses that numeric value to test for 
            dimensions[j] = stoi(line);
        }

        //Boolean values to be used in verifying the dimensions
        //of the actual grid are valid taking into account
        //the specified dimensions on the first two lines of the file
        bool reached_end_lines;
        bool reached_end_chars;

        //get as many lines as there are specified for in the height dimension
        for(int i = 0; i < dimensions[0]; i++){
            //is true if the file reader ever tries to read a nonexistant line
            //meaning the actual board is smalled in height than the 
            //specified height dimension
            reached_end_lines = !getline(file_input_stream_, line);
            if(reached_end_lines){
                throw 1; //invalid height exception
            }

            //iterate through as many characters per line as
            //there were specified for in the width dimension
            for(int j = 0; j < dimensions[1]; j++){
                reached_end_chars = (j > line.length()-1);

                //is true if the current line element index is greater 
                //than the maximum line index, meaning the specified
                //width value is greater than the actual width of the 
                //board on this line
                if(reached_end_chars){
                    throw 2;//invalid width exception
                }
                //is true if the current character is ever not
                //a 'X' or a '-'
                if(line[j] != 'X' && line[j] != '-'){
                    bad_char = line[j];
                    throw 3; //invalid board character exception
                }
            }
        }
    }
    //catch exceptions thrown by integer
    catch(int e){
        //invalid dimension character exception
        if(e == 0){
            cerr << "Invalid argument in board dimensions:  \'" << bad_char << "\'" << endl;
            cerr << "Argument contained a non-numeric character" << endl;
        }
        //invalid height exception
        else if(e == 1){
            cerr << "Invalid dimensions provided" << endl;
            cerr << "Height dimension excedes provided board" << endl;
        }
        //invalid width exception
        else if(e == 2){
            cerr << "Invalid dimensions provided" << endl;
            cerr << "Width dimension excedes provided board" << endl;
        }
        //invalid board character exception
        else if(e == 3){
            cerr << "Invalid character in provided board:  \'" << bad_char << "\'" << endl;
            cerr << "Character was neither \'X\' nor \'-\'" << endl;
        }
        return false;
    }

    //catch specific error thrown if stoi finds an integer that is too large
    catch(const out_of_range& e){
        cerr << "Invalid argument in board dimensions:  " << line << endl;
        cerr << "Numeric argument too large to be contained in int" << endl;
        return false;
    }

    return true;
}

//Reads the two numbers at the top of the file
//and returns them in an int[2]
//height will be index 0 and width will be index 1s
int* GameReader::ReadDimensions(){
    ReturnToFileStart();

    int* dimensions = new int[2];

    string line = "";

    //takes input from the first line and
    //parses the int it contains
    getline(file_input_stream_, line);
    dimensions[0] = stoi(line);

    //takes input from the second line and
    //parses the int it contains
    getline(file_input_stream_, line);
    dimensions[1] = stoi(line);

    return dimensions;
}

//Reads 2D array of cells from input file
//and returns it
Cell** GameReader::ReadCells(){
    //gathers dimensions and puts the file reader
    //on the thrid line of the file where the board starts
    int height = ReadDimensions()[0];
    int width = ReadDimensions()[1];

    string line = "";

    //initializes Array of Cell Arrays that is "height" long
    Cell** cells = new Cell*[height];
    
    //for each element of the Array of Cell Arrays...
    for(int i = 0; i < height; i++){
        //...get the next line of the board from the input file,
        getline(file_input_stream_, line);

        //initialize the current element of the Array of Cell Arrays with
        //the exact size required for an Array of Cells of length "width".
        cells[i] = (Cell*)malloc(width * sizeof(Cell));
        
        //for each individual cell, set its state equal to
        //the corresponding cell in the input file's board
        for(int j = 0; j < width; j++){
            if(line[j] =='X')
                cells[i][j].SetIsAlive(true);
            else if(line[j] == '-')
                cells[i][j].SetIsAlive(false);
        }
    }

    return cells;
}