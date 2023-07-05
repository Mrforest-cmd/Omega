#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool isdead;
int pos_x, pos_y, score, pos_fruit_x, pos_fruit_y;
const int map_width = 20;
const int map_height = 20;
int pos_hvost_x[50], pos_hvost_y[50], dlinna_hvostika;


enum direction { RIGHT, LEFT, UP, DOWN, STOP = 1 };
direction directi;

void start() {
	score = 0;
	isdead = false;
	directi = STOP;
	pos_x = map_width / 2;
	pos_y = map_height / 2;
	pos_fruit_x = rand() % map_width;
	pos_fruit_y = rand() % map_height;
}

void game() {
	int temp_save_x=pos_hvost_x[0], temp_save_y = pos_hvost_y[0], temp1,temp2;
	pos_hvost_x[0] = pos_x, pos_hvost_y[0] = pos_y;
	for (int i = 1; i < dlinna_hvostika; i++) {
		temp1 = pos_hvost_x[i];
		temp2 = pos_hvost_y[i];
		pos_hvost_x[i] = temp_save_x;
		pos_hvost_y[i] = temp_save_y;
		temp_save_x = temp1;
		temp_save_y = temp2;
	}
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
}

void controls() {
	if (_kbhit) {
		switch (_getch()) {
		case 'a':
			cout << 'a' << endl;
			directi = LEFT;
			break;
		case 'd':
			cout << 'd' << endl;
			directi = RIGHT;
			break;
		case 'w':
			cout << 'w' << endl;
			directi = UP;
			break;
		case 's':
			cout << 's' << endl;
			directi = DOWN;
			break;
		}
		if (pos_x > map_width -2 || pos_y > map_height-1 || pos_x < 0 || pos_y < 0) {
			isdead = true;
			for (int i = 0; i < dlinna_hvostika; i++) {
				if (pos_hvost_x[i] == pos_x && pos_hvost_y[i] == pos_y) {
					isdead = true;
				}
			}
		}
		if (pos_x == pos_fruit_x && pos_y == pos_fruit_y) {
			dlinna_hvostika++;
			score++;
			pos_fruit_x = rand() % map_width;
			pos_fruit_y = rand() % map_height;
		}
	}
}

void sketchup() {
	system("cls");
	for (int i = 0; i < map_width + 1; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < map_height; i++) {
		for (int w = 0; w < map_width; w++) {
			if (w == 0 || w == map_width - 1 ) {
				cout << "#";
			}
			if (i == pos_y && w == pos_x) {
				cout << "0";
			}
			else if (w == pos_fruit_x && i == pos_fruit_y) {
				cout << "F";
			}
			else {
				bool nospace = false;
				for (int b = 0; b < dlinna_hvostika; b++) {
					if (pos_hvost_y[b] == i && pos_hvost_x[b] == w) {
						cout << "0";
						nospace = true;
					}
					
				}
				if (!nospace) {
					cout << " ";
				}
				
			}
			
		}
		cout << endl;
	}

	for (int i = 0; i < map_width + 1; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score;
}


int main() {
	srand((unsigned)time(NULL));
	start();
	while (!isdead) {
		sketchup();
		controls();
		game();
	}
}
