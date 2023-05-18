#include<Windows.h>
#include<iostream>
#include <stdlib.h>



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
	char p = 219;
	char b = 8;
	int d = 0;
	string outPut = "";
	while (true) {
		GetKEY();
		if (KEY[39])
		{
			outPut += " ";
			d++;
		}
		else if (KEY[37])
		{
			if (size(outPut) > 0) {
				outPut += b;
				d--;
			}
		}
		else if (KEY[40])
		{
			outPut += "\n";
			for (int i = 0; i < d; i++) {
				outPut += " ";
			}

		}
		else if (KEY[38])
		{
			outPut += "";
			outPut += "\033[A";
		}
		cout << "\033[2J\033[1;1H";
		cout << outPut << p << endl;
		Sleep(200);
	}
}