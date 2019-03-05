/*
Name:  Dan Haub
Student ID#:  2315346
Chapman Email:  haub@chapman.edu
Course Number and Section:  CPSC 350-01
Assignment:  2- Game of Life
*/

#ifndef RANDOMIZER_H
#define RANDOMIZER_H

class Randomizer{
    private:
        int height_;
        int width_;
        double percent_alive_;

    public:
        //Default Constructor (10-10 grid 50% alive)
        Randomizer();

        //Overloaded Constructor
        //Takes height, width as a parameter
        Randomizer(int h, int w, double percent_alive);

        //Basic Destructor
        ~Randomizer();

        Cell** GenerateCellArray();

        int* GetDimensions();
};

#endif //RANDOMIZER_H