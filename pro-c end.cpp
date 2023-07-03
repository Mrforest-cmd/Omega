﻿#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <vector>

using namespace std;

bool isdead;
int pos_x, pos_y, score, pos_fruit_x, pos_fruit_y;
const int map_width = 20;
const int map_height = 20;

enum direction { RIGHT, LEFT, UP, DOWN, STOP };
direction directi;

struct Segment {
    int x;
    int y;
};

vector<Segment> snake;

void start() {
    isdead = false;
    directi = STOP;
    pos_x = map_width / 2 - 1;
    pos_y = map_height / 2 - 1;
    pos_fruit_x = rand() % map_width;
    pos_fruit_y = rand() % map_height;
    score = 0;
    snake.clear();
    snake.push_back({ pos_x, pos_y });
}

void game() {
    int prev_x = snake[0].x;
    int prev_y = snake[0].y;

    switch (directi) {
    case RIGHT:
        prev_x++;
        break;
    case LEFT:
        prev_x--;
        break;
    case UP:
        prev_y--;
        break;
    case DOWN:
        prev_y++;
        break;
    }

    snake[0].x = prev_x;
    snake[0].y = prev_y;

    if (prev_x >= map_width || prev_y >= map_height || prev_x < 0 || prev_y < 0) {
        isdead = true;
    }

    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[i].x == prev_x && snake[i].y == prev_y) {
            isdead = true;
            break;
        }
    }

    for (size_t i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    if (prev_x == pos_fruit_x && prev_y == pos_fruit_y) {
        score++;
        pos_fruit_x = rand() % map_width;
        pos_fruit_y = rand() % map_height;

        snake.push_back({ prev_x, prev_y });

        if (score == 1) {
            snake.push_back({ prev_x, prev_y });
        }
    }
}


void control() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'a':
            if (directi != RIGHT)
                directi = LEFT;
            break;
        case 'd':
            if (directi != LEFT)
                directi = RIGHT;
            break;
        case 'w':
            if (directi != DOWN)
                directi = UP;
            break;
        case 's':
            if (directi != UP) 
                directi = DOWN;
            break;
        }
    }
}


void sketch() {
    system("cls");
    for (int i = 0; i < map_width + 1; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < map_height; i++) {
        for (int w = 0; w < map_width + 1; w++) {
            if (w == 0 || w == map_width) {
                cout << "#";
            }
            else {
                bool is_snake_segment = false;
                for (const auto& segment : snake) {
                    if (segment.x == w && segment.y == i) {
                        cout << "s";
                        is_snake_segment = true;
                        break;
                    }
                }
                if (!is_snake_segment) {
                    if (w == pos_fruit_x && i == pos_fruit_y) {
                        cout << "*";
                    }
                    else {
                        cout << " ";
                    }
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i < map_width + 2; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

int main() {
    srand((unsigned)time(NULL));
    start();
    while (!isdead) {
        sketch();
        control();
        game();
        Sleep(70);
    }
    cout << "Game over!" << endl;
}