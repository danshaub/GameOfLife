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
#include <math.h>
#include <string>
using namespace std;

void printCellArr(Cell** e, int width, int hight);

int main(){
    char answer = '\0'; // placeholder for all prompt answers
    bool success = false; //placeholder for all do-while loops

    bool randomized; // true if user wants a randomized board to start
    Randomizer * randomizer; // if randomized is true, this will be initialized and passed to the board's constructor
    int hight; // random board's hight
    int width; // random board's width
    double alive_percentage; // random board's alive percentage
    
    GameReader * game_reader; // if randomized is false, this will be initialized and passed to the board's constructor
    string input_file_name; // name of input file for initial board state

    int boundary_mode; // 0-classic, 1-doughnut, 2-mirror
    int display_mode; // 0-auto, 1-manual, 2-output file

    EdgeType * edge_mode;
    Game * the_game; // the allmighty game object! Behold its abstraction!

    cout << "~~~~WELCOME TO THE GAME OF LIFE!~~~~\n\n"
         << "*When I ask you things, the first option is the default*\n"
         << "*If what you put doesn't match any options, you get the default*\n\n"
         << "Would you like to see the rules? [y/n]\n";

    cin >> answer;
    if(answer == 'n'){
        cout << "\nOkay, moving on!\n\n";
    }
    else{
        cout << "\nthe rules\n\n";
    }

    cout << "Would you like the initial board to be randomized,\n"
         << "or do you have an input file in mind? [r,i]\n";
    
    cin >> answer;
    if(answer == 'i'){
        randomized = false;
        game_reader = new GameReader();
        cout << "\n"
             << "You have chosen to start with an input file!\n"
             << "Tell me, what is the name of this file?\n";
        
        cin >> input_file_name;

        game_reader->SetFileName(input_file_name);

        if(game_reader->InStreamIsOpen() && game_reader->FileFormatIsValid()){
            cout << "\nExcelent choice of file!\n";
            success = true;
        }

        //TODO Figure out how to test multiple files!!
        else{ 
            cout << "\nThat file was lame!\n"
                 << "I can't handle this!\n";
            return 1;
        }

    }
    else{
        randomized = true;
        cout << "\nYou have chosen to start with a random board!\n"
             << "Let me ask you some stuff about the board:\n";
        
        success = false;
        do{
            try{
                cout << "What is the hight of the board that you want?\n";
                string hight_string;
                cin >> hight_string;

                hight = stoi(hight_string);

                success = true;
            }
            catch (exception e){
                success = false;
                cout << "\nSorry, that was invalid. Let me ask again\n";
            }
        }while(!success);

        do{
            try{
                cout << "What is the width of the board that you want?\n";
                string width_string;
                cin >> width_string;

                width = stoi(width_string);

                success = true;
            }
            catch (exception e){
                success = false;
                cout << "\nSorry, that was invalid. Let me ask again\n";
            }
        }while(!success);

        do{
            try{
                cout << "What percent of cells alive that you want? (\"45.6\%\" would be simply \"45.6\"\n";
                string alive_percentage_string;
                cin >> alive_percentage_string;

                alive_percentage = stod(alive_percentage_string);

                success = true;
            }
            catch (exception e){
                success = false;
                cout << "\nSorry, that was invalid. Let me ask again\n";
            }
        }while(!success);
        randomizer = new Randomizer(hight, width, alive_percentage);
        cout << "Your game will be very random indeed!\n";
    }

    cout << "\nNow, how would you like your edges to be calculated?\n"
         << "-Classic mode (out of bounds doesn't exist)\n"
         << "-Doughnut mode (out of bounds wraps around to the other side)\n"
         << "-Mirror mode (out of bounds reflects back)\n"
         << "[c,d,m]\n";

    cin >> answer;

    if(answer == 'd'){
        cout << "\nYou chose Doughnut mode";
        edge_mode = new Doughnut();
        boundary_mode = 1;
    }
    else if(answer == 'm'){
        cout << "\nYou chose Mirror mode";
        edge_mode = new Mirror();
        boundary_mode = 2;
    }
    else{
        cout << "\nYou chose Classic mode";
        edge_mode = new Classic();
        boundary_mode = 0;
    }

    cout << "\nFinally, how would you like the results displayed?\n"
         << "-Auto (generations are displayed to the console automatically)\n"
         << "-Manual (generations are displayed when you press enter)\n"
         << "-File (generations are displayed to a file of your choosing)\n"
         << "[a,m,f]";

    cin >> answer;

    if(answer == 'm'){
        cout << "\nYou chose Manual mode";
        display_mode = 1;
                
    }
    else if(answer == 'f'){
        cout << "\nYou chose File Output mode";
        display_mode = 2;
    }
    else{
        cout << "\nYou chose Auto mode";
        display_mode = 0;
    }

    if(randomized){
        the_game = new Game(edge_mode, randomizer, display_mode);
    }
    else{
        the_game = new Game(edge_mode, input_file_name, display_mode);
    }

    the_game->Simulate();
    return 0;
}

void printCellArr(Cell** e, int hight, int width){
    cout << endl;
    cout << hight << endl << width << endl;
    for(int i = 0; i < hight; i++){
        for(int j = 0; j < width; j++){
            if(e[i][j].GetIsAlive()){
                cout << "X";
            }
            else{
                cout << "-";
            }
        }
        cout << endl;
    }
}

//Board Testing:
    //int main(){
        //     Board * b = new Board(new Classic(), new Randomizer(30, 50, 20));
        //     for(int i = 0; i < 5; i++){
        //         cout << b->ToString() << endl;
        //         b->Iterate();
        //     }

        //     Board * c = new Board(new Classic(), new GameReader("test.txt"));

        //     for(int i = 0; i < 100; i++){
        //         cout << c->ToString() << endl;
        //         c->Iterate();
        //     }

        //     return 0;
        // }

//Randomizer Testing:
        // int main()
        // {
        //     int hight = 10;
        //     int width = 20;

        //     Cell **t1 = new Cell *[hight];
        //     Cell **t2 = new Cell *[hight];

        //     for (int i = 0; i < hight; i++)
        //     {
        //         t1[i] = new Cell[width];
        //         t2[i] = new Cell[width];
        //     }

        //     Randomizer r(hight, width, 42893);

        //     t1 = r.GenerateCellArray();

        //     printCellArr(t1, hight, width);

        //     EdgeType *e = new Classic();

        //     e->Iterate(t1, t2, hight, width);

        //     printCellArr(t2, hight, width);

        //     return 0;
        // }

//GameReader Testing:
    // int main()
    // {
        // GameReader g("test.txt");

        // if (!g.FileFormatIsValid())
        //     return 1;

        // int *dim = new int[2];

        // dim = g.ReadDimensions();

        // int hight = dim[0];
        // int width = dim[1];

        // Cell **t1 = new Cell *[hight];
        // Cell **t2 = new Cell *[hight];

        // for (int i = 0; i < hight; i++)
        // {
        //     t1[i] = new Cell[width];
        //     t2[i] = new Cell[width];
        // }

        // t1 = g.ReadCells();

        // printCellArr(t1, hight, width);

        // EdgeType *e = new Classic();

        // t2 = e->Iterate(t1, t2, hight, width);

        // printCellArr(t2, hight, width);

        // return 0;
    // }

//EdgeType Testing:

    // int main(){
    //     int width = 15;
    //     int hight = 10;
    //     Cell** tester = new Cell*[hight];
        
    //     for(int i = 0; i < hight; i++){
    //         tester[i] = new Cell[width];
    //         for(int j = 0; j < width; j++){
    //             int d = rand()%2;
    //             bool e = (d == 0);
    //             tester[i][j].SetIsAlive(e);
    //         }
    //     }

    //     GameReader g("test.txt");

    //     int* dim = new int[2];
    //     dim = g.ReadDimensions();

    //     Cell** tester2 = new Cell*[dim[0]];
        
    //     for(int i = 0; i < dim[0]; i++){
    //         tester2[i] = new Cell[dim[1]];
    //     }

        

    //     tester2 = g.ReadCells();

    //     printCellArr(tester, hight, width);

    //     cout << endl;

    //     printCellArr(tester2, dim[0], dim[1]);

    //     EdgeType * e = new Classic(); //can be any of the three edge types

    //     tester2 = e->Iterate(tester, tester2, hight, width);

    //     printCellArr(tester2, hight, width);
    // }

    

//Cell Testing:
    // Cell* a = new Cell(false);
    // Cell* b = new Cell(false);
    // Cell* c = new Cell(false);
    // Cell* d = new Cell(false);
    // Cell* e = new Cell(true);
    // Cell* f = new Cell(true);
    // Cell* g = new Cell(true);
    // Cell* h = new Cell(true);

    // cout << a->GetIsAlive() << endl;
    // cout << b->GetIsAlive() << endl;
    // cout << c->GetIsAlive() << endl;
    // cout << d->GetIsAlive() << endl << endl;
    // cout << e->GetIsAlive() << endl;
    // cout << f->GetIsAlive() << endl;
    // cout << g->GetIsAlive() << endl;
    // cout << h->GetIsAlive() << endl << endl << endl;

    // a->UpdateGeneration(0);
    // b->UpdateGeneration(2);
    // c->UpdateGeneration(3);
    // d->UpdateGeneration(6);
    // e->UpdateGeneration(0);
    // f->UpdateGeneration(2);
    // g->UpdateGeneration(3);
    // h->UpdateGeneration(6);

    // cout << a->GetIsAlive() << endl;
    // cout << b->GetIsAlive() << endl;
    // cout << c->GetIsAlive() << endl;
    // cout << d->GetIsAlive() << endl << endl;
    // cout << e->GetIsAlive() << endl;
    // cout << f->GetIsAlive() << endl;
    // cout << g->GetIsAlive() << endl;
    // cout << h->GetIsAlive() << endl << endl << endl;

    // delete a;
    // delete b;
    // delete c;
    // delete d;
    // delete e;
    // delete f;
    // delete g;
    // delete h;

