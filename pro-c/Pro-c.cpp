#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool isdead;
int pos_x, pos_y, score, pos_fruit_x, pos_fruit_y;
const int map_width = 20;
const int map_height = 20;
int pos_hvost_x[50], pos_hvost_y[50], dlinna_hvostika;


enum direction { RIGHT, LEFT, UP, DOWN };
direction directi;
// Сетап 
void start() {
    score = 0;
    isdead = false;
    directi = UP;
    pos_x = map_width / 2;
    pos_y = map_height / 2;
    pos_fruit_x = rand() % (map_width - 2) + 1;
    pos_fruit_y = rand() % (map_height - 2) + 1;
}

void game() {
    // Тут делаеться хвост.
    int temp_save_x = pos_hvost_x[0], temp_save_y = pos_hvost_y[0], temp1, temp2;
    pos_hvost_x[0] = pos_x, pos_hvost_y[0] = pos_y;
    for (int i = 1; i < dlinna_hvostika; i++) {
        temp1 = pos_hvost_x[i];
        temp2 = pos_hvost_y[i];
        pos_hvost_x[i] = temp_save_x;
        pos_hvost_y[i] = temp_save_y;
        temp_save_x = temp1;
        temp_save_y = temp2;
    }
    // Тут проверка на значение directi (управление)
    switch (directi) {
    case RIGHT:
        pos_x++;
        break;
    case LEFT:
        pos_x--;
        break;

    case UP:
        pos_y--;
        break;

    case DOWN:
        pos_y++;
        break;
    }
    // Тут проверка на удар об стену
    if (pos_x > map_width - 2 || pos_y > map_height - 1 || pos_x < 0 || pos_y < 0) {
        isdead = true;
        for (int i = 0; i < dlinna_hvostika; i++) {
            if (pos_hvost_x[i] == pos_x && pos_hvost_y[i] == pos_y) {
                isdead = true;
            }
        }
    }
    // Тут проверка на удар об звост
    for (int i = 1; i < dlinna_hvostika; i++) {
        if (pos_x == pos_hvost_x[i] && pos_y == pos_hvost_y[i]) {
            isdead = true;
            return;
        }
    }
    // Тут зачисление очков + удлиннение хвоста
    if (pos_x == pos_fruit_x && pos_y == pos_fruit_y) {
        dlinna_hvostika++;
        score++;
        // И ещё регенерация фруктов) (- 2 - чтобы не выйти за границы карты и -1 для того,чтобы они появлялись на последнем столбике перед правой стеной)
        pos_fruit_x = (rand() % (map_width - 2)) + 1;
        pos_fruit_y = (rand() % (map_height - 2)) + 1;
    }
}
// Нажатия клавишь (игра работает только с английской раскладкой)
void controls() {
    // Реализовано оно так, чтобы мы не могли пойти сразу в противоположную сторону, что-бы не врезаться в самого себя
    if (_kbhit()) {
        switch (_getch()) {
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
        case '\b':
            system("pause");
        }
    }
}
// Отрисовка карты
void sketchup() {
    system("cls");
    // потолок
    for (int i = 0; i < map_width + 1; i++) {
        cout << "_";
    }
    cout << endl;

    for (int i = 0; i < map_height; i++) {
        for (int w = 0; w < map_width; w++) {
            // стены
            if (w == 0 || w == map_width - 1) {
                cout << "|";
            }
            // голова змеи
            if (i == pos_y && w == pos_x) {
                cout << "*";
            }
            // фрукт
            else if (w == pos_fruit_x && i == pos_fruit_y) {
                cout << "#";
            }
            else {
                bool nospace = false;
                // хвост
                for (int b = 0; b < dlinna_hvostika; b++) {
                    if (pos_hvost_y[b] == i && pos_hvost_x[b] == w) {
                        cout << "*";
                        nospace = true;
                    }
                }
                // пустое место на карте
                if (!nospace) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    // пол
    for (int i = 0; i < map_width + 1; i++) {
        cout << "_";
    }
    cout << endl << endl;
    cout << "Score: " << score;
}

int main() 
{
    srand((unsigned)time(NULL));
    start();
    while (!isdead) {
        sketchup();
        controls();
        game();
        Sleep(100);
    }
}
