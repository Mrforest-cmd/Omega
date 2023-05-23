#include<Windows.h>
#include<iostream>
#include <stdlib.h>
#include <string>
using namespace std;

bool KEY[256];
void GetKEY()
{
	int i = 0;
	while (i < 256)
	{	
		if (GetAsyncKeyState(i)) {
			KEY[i] = 1;
		}
		else {
			KEY[i] = 0;
		}
		i++;
	}
}

void main() {
	char b = 219;
	char b = 8;
	const int x = 10;
	const int y = 10;
	string map[x + 1][y + 1];
	for (int i = 0; i < y + 1; i++) {
		cout << "-";
	}
}