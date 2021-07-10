#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define ENTER 13

using namespace std;

void ru_re();

int opening() {
	int op = 0;
	int flag = 0;
	do {
		while (1) {
			system("cls");
			cout << "=====ぷよぷよ@パクリ=====\n" << endl;
			printf("     %sSTART\n", (op == 0) ? "◎" : "  ");
			printf("     %sRURE\n", (op == 1) ? "◎" : "  ");
			printf("     %sEND\n", (op == 2) ? "◎" : "  ");
			if (_kbhit()) {
				int key = _getch();
				switch (key) {
				case 'w':
					op--;
					break;
				case 's':
					op++;
					break;
				case ENTER:
					flag = 1;
					break;
				}
				op = (op + 3) % 3;
				if (flag == 1)
					break;
			}
		}
		if (op == 1) {
			ru_re();
			flag = 0;
			op = 0;
		}
	} while (!flag);

	return op;
}

void ru_re() {
	while (1) {
		system("cls");
		cout << "=====RURE=====\n" << endl;
		cout << "1,ぷよぷよを丸パクリしたよ" << endl;
		cout << "2.同じ色のぷよを4つ以上繋げたら消せるよ" << endl;
		cout << "ハイスコアを目指して頑張ってね!" << endl;
		cout << "Any key plese..." << endl;
		if (_kbhit()) {
			int gomi = _getch();
			system("cls");
			return;
		}
	}
}

int game_select() {
	int op = 0;
	int flag = 1;

	while (flag) {
		system("cls");
		printf("%sNEW GAME\n", (op == 0) ? "◎" : "  ");
		printf("%sEND\n", (op == 1) ? "◎" : "  ");
		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			case 'w':
				op--;
				break;
			case 's':
				op++;
				break;
			case ENTER:
				flag = 0;
				break;;
			}
		}
	}

	return op;
}

void time_up() {
	cout << "======================" << endl;
	cout << "          終了" << endl;
	cout << "======================" << endl;
	Sleep(3000);
	return;
}