#include "cell.h"
#include "game_reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex> 

using namespace std;

// Takes a string as a parameter and initializes
// file_input_stream_ with the string as its file name
GameReader::GameReader(string f){
    input_file_name_ = f;
    file_input_stream_.open(input_file_name_);
}

//Destructs file_input_stream
GameReader::~GameReader(){
    file_input_stream_.close();
}

bool GameReader::InStreamIsOpen(){
    return file_input_stream_.is_open();
}

bool GameReader::SetFileName(string f){
    input_file_name_ = f;
    file_input_stream_.open(input_file_name_);
    return file_input_stream_.is_open();
}

void GameReader::ReturnToFileStart(){
    file_input_stream_.clear();
    file_input_stream_.seekg(0, file_input_stream_.beg);
}

bool GameReader::FileFormatIsValid(){
    ReturnToFileStart();

    int* dimensions = new int[2];
    string line = "";
    char bad_char;

    try{
        for(int j = 0; j < 2; j++){
            //takes first line of file and 
            //uses a regex test to make sure
            //it is purly numeric
            getline(file_input_stream_, line);
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
                    throw 0;
                }
            }
            //parses that numeric value to test for 
            dimensions[j] = stoi(line);
        }

        bool reached_end_lines;
        bool reached_end_chars;

        for(int i = 0; i < dimensions[0]; i++){
            reached_end_lines = !getline(file_input_stream_, line);
            if(reached_end_lines){
                throw 1;
            }
            for(int j = 0; j < dimensions[1]; j++){
                reached_end_chars = j >= line.length()-1;
                if(reached_end_chars){
                    throw 2;
                }
                if(line[j] != 'X' && line[j] != '-'){
                    bad_char = line[j];
                    throw 3;
                }
            }
        }
    }
    catch(int e){
        if(e == 0){
            cerr << "Invalid argument in board dimensions:  \'" << bad_char << "\'" << endl;
            cerr << "Argument contained a non-numeric character" << endl;
        }
        else if(e == 1){
            cerr << "Invalid dimensions provided" << endl;
            cerr << "Height dimension excedes provided board" << endl;
        }
        else if(e == 2){
            cerr << "Invalid dimensions provided" << endl;
            cerr << "Width dimension excedes provided board" << endl;
        }
        else if(e == 3){
            cerr << "Invalid character in provided board:  \'" << bad_char << "\'" << endl;
            cerr << "Character was neither \'X\' nor \'-\'" << endl;
        }
        return false;
    }
    catch(const out_of_range& e){
        cerr << "Invalid argument in board dimensions:  " << line << endl;
        cerr << "Numeric argument too large to be contained in int" << endl;
        return false;
    }

    return true;
}

int* GameReader::ReadDimensions(){
    //tests to see if file is in a valid form
    if(!FileFormatIsValid()){
        return nullptr;
    }
    
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

Cell** GameReader::ReadCells(){
    //tests to see if file is in a valid form
    if(!FileFormatIsValid())
        return nullptr;

    int hight = ReadDimensions()[0];
    int width = ReadDimensions()[1];

    string line = "";

    Cell** cells = new Cell*[hight];
    
    for(int i = 0; i < hight; i++){
        getline(file_input_stream_, line);
        cells[i] = (Cell*)malloc(width * sizeof(Cell));
        for(int j = 0; j < width; j++){
            if(line[j] =='X')
                cells[i][j].SetIsAlive(true);
            else if(line[j] == '-')
                cells[i][j].SetIsAlive(false);
        }
        cout << endl;
    }

    return cells;
}