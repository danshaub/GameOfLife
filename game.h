// #ifndef GAME_H
// #define GAME_H

// #include "board.h"
// #include "cell.h"
// #include "classic.h"
// #include "doughnut.h"
// #include "edge_type.h"
// #include "mirror.h"
// #include "randomizer.h"
// #include "game_reader.h"
// #include <iostream>

// class Game{
//     private:
//         Board game_board_;
//         EdgeType game_edge_type_;
//         string input_file_name_;
//         Randomizer board_randomizer_;

//         //0-automatic with a pause
//         //1-manual
//         //2-output to file
//         int display_type_; 

//         void Display();
//     public:
//         Game();

//         Game(Board game_board; EdgeType game_edge_type, string input_file_name, int display_type);

//         Game(Board game_board; EdgeType game_edge_type, Randomizer board_randomizer, int display_type);

//         ~Game();

//         void Simulate();

// };

// #endif //GAME_H