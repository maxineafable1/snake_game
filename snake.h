#include <iostream>
#include <conio.h>
#include <windows.h>

#ifndef SNAKE_H
#define SNAKE_H

struct Coordinates
{
    int x, y;
    Coordinates(int x, int y);
    Coordinates();
};

enum Keys { 
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77
};

enum Directions { UP, DOWN, LEFT, RIGHT, STOP };

class Snake
{
    private:
        int height, width;
        bool game_over;
        unsigned char wall;
        unsigned char snake_part;
        unsigned char food_part;
        unsigned int tail_x[100], tail_y[100];
        unsigned int n_tail;
        unsigned int score;
        Coordinates snake;
        Coordinates food;
        Directions direction;
        Keys key;

        void move_snake();
        void snake_collision();
        void spawn_food();
        void user_input();
        void draw_board();
    
    public:
        Snake();
        void start();
};

#endif