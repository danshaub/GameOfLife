#ifndef RANDOMIZER_H
#define RANDOMIZER_H

class Randomizer{
    private:
        int hight_;
        int width_;
        double percent_alive_;

    public:
        //Default Constructor (10-10 grid 50% alive)
        Randomizer();

        //Overloaded Constructor
        //Takes hight, width as a parameter
        Randomizer(int h, int w, double percent_alive);

        //Basic Destructor
        ~Randomizer();

        Cell** GenerateCellArray();

        int* getDimensions();
};

#endif //RANDOMIZER_H