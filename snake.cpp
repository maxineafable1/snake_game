#include <stdlib.h>
#include <time.h>
#include "snake.h"

Coordinates::Coordinates(int x, int y): x(x), y(y) {}

Coordinates::Coordinates()
{
    x = 0;
    y = 0;
}

Snake::Snake()
{
    srand (time(NULL));
    height = 20;
    width = 40;
    game_over = false;
    wall = (char) 219;
    snake_part = 'O';
    food_part = '#';
    direction = STOP;
    snake = {width / 2, height / 2};
    n_tail = 0;
    score = 0;
}

void Snake::spawn_food()
{
    food.x = rand() % (width - 2) + 1;
    food.y = rand() % (height - 2) + 1;
}

void Snake::snake_collision()
{
    // when snake eat food, increase its tail
    if (snake.x == food.x && snake.y == food.y)
    {
        spawn_food();
        n_tail++;
        score++;
    }

    // check wall collision
    if (snake.x <= 0 || snake.x >= width - 1 || snake.y < 0 || snake.y >= height)
    {
        game_over = true;
    }

    // when snake touch its tail
    for (int i = 0; i < n_tail; i++)
    {
        if (snake.x == tail_x[i] && snake.y == tail_y[i])
            game_over = true;
    }
}

void Snake::move_snake()
{   
    // move each snake tail to their next tail's previous position
    // length = 3; example n[1] tail pos will now be the pos of n[2]
    for (int i = n_tail - 1; i > 0; i--)
    {
    	tail_x[i] = tail_x[i - 1];
    	tail_y[i] = tail_y[i - 1];
    }
    // and the first tail pos will be the prev pos of snake head
    tail_x[0] = snake.x;
    tail_y[0] = snake.y;

    switch (direction)
    {
        case UP:
            snake.y--;
            break;
        case DOWN:
            snake.y++;
            break;
        case LEFT:
            snake.x--;
            break;
        case RIGHT:
            snake.x++;
            break;
    }
}

void Snake::user_input()
{
    if (_kbhit())
    {
        int c = 0;
        switch (c = getch())
        {
            case KEY_UP:
                if (direction != DOWN)
                    direction = UP;
                break;
            case KEY_DOWN:
                if (direction != UP)
                    direction = DOWN;
                break;
            case KEY_LEFT:
                if (direction != RIGHT)
                    direction = LEFT;
                break;
            case KEY_RIGHT:
                if (direction != LEFT)
                    direction = RIGHT;
                break;
            case 'q':
                game_over = true;
                break;
            default:
                break;
        }
    }    
}

void Snake::draw_board()
{
    // clears the terminal; use this or the next code to refresh terminal
    // system("cls");
    
    // removes the cursor
    CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    // removes flickering of terminal
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

    // top wall
    for (int i = 0; i < width; i++)
    {
        std::cout << wall;
    }
    std::cout << '\n';

    // inside box
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // side walls
            if (j == 0 || j == width - 1)
                std::cout << wall;
            // snake head
            else if (i == snake.y && j == snake.x)
                std::cout << snake_part;
            // food position
            else if (i == food.y && j == food.x)
                std::cout << food_part;
            else
            {
                // this print empty space if not the snake's tail
                bool print = false;
                for (int k = 0; k < n_tail; k++)
                {
                    if (tail_x[k] == j && tail_y[k] == i)
                    {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    std::cout << ' ';
            }   
        }
        std::cout << '\n';
    }
    
    // bottom wall
    for (int i = 0; i < width; i++)
    {
        std::cout << wall;
    }
    std::cout << '\n';

    // game instructions and score display
    for (int i = 0; i < width; i++)
    {
        std::cout << '*';
    }
    std::cout << '\n';
    
    std::string space_below = "                              *";
    std::string space_above = "                             *";
    
    std::cout << '*' << "Use arrow keys to move the snake" << "      *" << '\n';
    std::cout << '*' << "Press (q) to quit" << "                     *" << '\n';
    std::cout << '*' << "Score: " << score << (score >= 10 ? space_above : space_below) << '\n';

    for (int i = 0; i < width; i++)
    {
        std::cout << '*';
    }
    std::cout << '\n';
}

void Snake::start()
{
    spawn_food();
    while (!game_over)
    {
        draw_board();
        user_input();
        move_snake();
        snake_collision();
        // controls speed of game
        Sleep(100);
    }
}