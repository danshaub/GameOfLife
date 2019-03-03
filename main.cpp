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
using namespace std;

void printCellArr(Cell** e, int width, int hight);

int main(){
    Board * b = new Board(new Classic(), new Randomizer(10, 13, 20));
    for(int i = 0; i < 5; i++){
        cout << b->ToString() << endl;
        b->Iterate();
    }

    //cout << "1HERE\n";

    Board * c = new Board(new Classic(), new GameReader("test.txt"));
    
    //cout << "2HERE\n";

    for(int i = 0; i < 100; i++){
        cout << c->ToString() << endl;
        c->Iterate();
    }

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

