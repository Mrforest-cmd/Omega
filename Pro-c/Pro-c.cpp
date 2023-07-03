#include <iostream>
#include <conio.h>

using namespace std;

bool isdead;
int pos_x, pos_y, score, pos_fruit_x, pos_fruit_y;
const int map_width = 20;
const int map_height = 20;

enum direction {RIGHT,LEFT,UP,DOWN,STOP=1};
direction directi;

void start() {
	isdead = false;
	directi = STOP;
	pos_x = map_width / 2 - 1;
	pos_y = map_height / 2 - 1;
	pos_fruit_x = rand() % map_width;
}

void game() {
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
	
void control() {
	if (_kbhit) {
		switch (_getch()) {
		case 'a':
			directi = LEFT;
			break;
		case 'd':
			directi = RIGHT;
			break;
		case 'w':
			directi = UP;
			break;
		case 's':
			directi = DOWN;
			break;
		}
		if (pos_x > map_width || pos_y > map_height || pos_x < 0 || pos_y < 0) {
			isdead = true;
		}
	}
}

void sketch() {
	system("cls");
	for (int i = 0; i < map_width + 1; i++) {
		cout << "#";	}
	cout << endl;

	for (int i = 0; i < map_height; i++) {
		for (int w = 0; w < map_width; w++) {
			if (w == map_width - 1 || w == 0) {
				cout << "#";
			}
			if (i == pos_y && w == pos_y) {
				cout << "s";
			}
			else if (w == pos_fruit_x && i == pos_fruit_y) {
				cout << "*";
			}
			else cout << " ";
		}
	}

	for (int i = 0; i < map_width + 1; i++) {
		cout << "#";
	}
	cout << endl;
}



void main() {
	srand((unsigned)time(NULL));
	start();
	while (!isdead) {
		sketch();
		control();
		game();
	}
}
