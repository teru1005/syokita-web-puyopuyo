#include <iostream>
#include <vector>
#include <windows.h>
#include <utility>
#include <queue>
#include <time.h>

using namespace std;

enum color {
	none,
	red,
	green,
	yellow,
	blue
};


void show_puyo_w_era(vector<vector<int> > data, int score, vector<vector<vector<int> > > era, vector<vector<vector<int> > > next, long long time) {
	for (int i = 0; i < era.size(); i++) {
		for (int j = 0; j < era[i].size(); j++) {
			data[era[i][j][2]][era[i][j][1]] = era[i][j][0] + 5;
		}
	}

	system("cls");
	for (int y = 0; y < 12; y++) {
		cout << "□";
		for (int x = 0; x < 8; x++) {
			switch (data[y][x]) {
			case red:
				cout << "\033[31m■\033[m";
				break;
			case green:
				cout << "\033[32m■\033[m";
				break;
			case yellow:
				cout << "\033[33m■\033[m";
				break;
			case blue:
				cout << "\033[34m■\033[m";
				break;
			case red + 5:
				cout << "\033[31m□\033[m";
				break;
			case green + 5:
				cout << "\033[32m□\033[m";
				break;
			case yellow + 5:
				cout << "\033[33m□\033[m";
				break;
			case blue + 5:
				cout << "\033[34m□\033[m";
				break;
			default:
				cout << "  ";
			}
		}
		cout << "□";

		//NEXT部分の表示
		if (y == 0) cout << "NEXT";
		if (y == 1 || y == 5 || y == 9)
			for (int i = 0; i < 5; i++)
				cout << "□";
		if (y == 2 || y == 4 || y == 6 || y == 8) {
			for (int i = 0; i < 4; i++)
				cout << "  ";
			cout << "□";
		}
		//TODO:引数にnext_puyoを入れてそれぞれの色のぷよを表示するのをお願いします
		if (y == 3 || y == 7) {
			int num = (y == 3) ? 0 : 1;
			cout << "  ";

			for (int i = 0; i < 2; i++) {
				switch (next[num][i][0]) {
				case red:
					cout << "\033[31m■\033[m";
					break;
				case green:
					cout << "\033[32m■\033[m";
					break;
				case yellow:
					cout << "\033[33m■\033[m";
					break;
				case blue:
					cout << "\033[34m■\033[m";
					break;
				}
			}

			cout << "  □";
		}

		cout << endl;
	}
	for (int i = 0; i < 10; i++) cout << "□";
	cout << endl;

	//スコアと残り時間の表示
	printf("SCORE:%14d\n", score);
	printf("TIME :%14d\n", (180000 - (clock() - time)) / 1000);
}

vector<vector<int> > rota_puyo(vector<vector<int> > cp, vector<vector<int> > data) {
	int x_diff = cp[0][1] - cp[1][1];
	int y_diff = cp[0][2] - cp[1][2];

	if (x_diff == -1 && cp[0][2] < 11 && data[cp[0][2] + 1][cp[0][1]] == 0) {
		cp[1][1] = cp[0][1];
		cp[1][2] = cp[0][2] + 1;
	}
	else if (x_diff == 1 && cp[0][2] > 0 && data[cp[0][2] - 1][cp[0][1]] == 0) {
		cp[1][1] = cp[0][1];
		cp[1][2] = cp[0][2] - 1;
	}
	else if (y_diff == 1 && cp[0][1] < 7 && data[cp[0][2]][cp[0][1] + 1] == 0) {
		cp[1][1] = cp[0][1] + 1;
		cp[1][2] = cp[0][2];
	}
	else if (y_diff == -1 && cp[0][1] > 0 && data[cp[0][2]][cp[0][1] - 1] == 0) {
		cp[1][1] = cp[0][1] - 1;
		cp[1][2] = cp[0][2];
	}

	return cp;
}

void show_puyo_w(vector<vector<int> > data, int score, vector<vector<int> > cp, vector<vector<vector<int> > > next, long long time) {
	for (int i = 0; i < cp.size(); i++) {
		data[cp[i][2]][cp[i][1]] = cp[i][0];
	}

	system("cls");
	for (int y = 0; y < 12; y++) {
		cout << "□";
		for (int x = 0; x < 8; x++) {
			switch (data[y][x]) {
			case red:
				cout << "\033[31m■\033[m";
				break;
			case green:
				cout << "\033[32m■\033[m";
				break;
			case yellow:
				cout << "\033[33m■\033[m";
				break;
			case blue:
				cout << "\033[34m■\033[m";
				break;
			default:
				cout << "  ";
			}
		}
		//外の壁
		cout << "□";

		//NEXT部分の表示
		if (y == 0) cout << "NEXT";
		if (y == 1 || y == 5 || y == 9)
			for (int i = 0; i < 5; i++)
				cout << "□";
		if (y == 2 || y == 4 || y == 6 || y == 8) {
			for (int i = 0; i < 4; i++)
				cout << "  ";
			cout << "□";
		}
		//TODO:引数にnext_puyoを入れてそれぞれの色のぷよを表示するのをお願いします
		if (y == 3 || y == 7) {
			int num = (y == 3) ? 0 : 1;
			cout << "  ";

			for (int i = 0; i < 2; i++) {
				switch (next[num][i][0]) {
				case red:
					cout << "\033[31m■\033[m";
					break;
				case green:
					cout << "\033[32m■\033[m";
					break;
				case yellow:
					cout << "\033[33m■\033[m";
					break;
				case blue:
					cout << "\033[34m■\033[m";
					break;
				}
			}

			cout << "  □";
		}

		cout << endl;
	}

	//床
	for (int i = 0; i < 10; i++) cout << "□";
	cout << endl; 
	
	//スコアと残り時間の表示
	printf("SCORE:%14d\n", score);
	printf("TIME :%14d\n", (180000 - (clock() - time)) / 1000);
}

vector<vector<int> > puyo_gene() {
	vector<vector<int> > cp(2, vector<int> (3));
	cp[0][0] = rand() % blue + 1;
	cp[0][1] = 3;
	cp[0][2] = 0;
	cp[1][0] = rand() % blue + 1;
	cp[1][1] = 4;
	cp[1][2] = 0;

	return cp;
}

vector<vector<int> > move_x(vector<vector<int> > cp, int key, vector<vector<int> > data) {
	switch (key) {
	case 'a':
		if (cp[0][1] >= 1 && cp[1][1] >= 1 && data[cp[0][2]][cp[0][1] - 1] == 0 && data[cp[1][2]][cp[1][1] - 1] == 0) {
			cp[0][1]--; cp[1][1]--;
		}
		break;
	case 'd':
		if (cp[0][1] <= 6 && cp[1][1] <= 6 && data[cp[0][2]][cp[0][1] + 1] == 0 && data[cp[1][2]][cp[1][1] + 1] == 0) {
			cp[0][1]++; cp[1][1]++;
		}
		break;
	case 's':
		if (cp[0][2] < 11 && cp[1][2] < 11 && data[cp[0][2] + 1][cp[0][1]] == 0 && data[cp[1][2] + 1][cp[1][1]] == 0) {
			cp[0][2]++; cp[1][2]++;
		}
		break;
	case 'w':
		cp = rota_puyo(cp, data);
		break;
	}

	return cp;
}

vector<vector<int> > fall_puyo(vector<vector<int> > cp) {
	cp[0][2]++; cp[1][2]++;
	return cp;
}

vector<vector<int> > down_puyo(vector<vector<int> > cp, vector<vector<int> > data, int score, vector<vector<vector<int> > > next, long long time) {
	vector<int> down(0);
	for (int i = 0; i < cp.size(); i++) {
		if (data[cp[i][2] + 1][cp[i][1]] == 0) {
			down.emplace_back(i);
			data[cp[i][2]][cp[i][1]] = 0;
		}
		else
			data[cp[i][2]][cp[i][1]] = cp[i][0];
	}

	vector<int> che(down.size());
	int flag = 0;
	while (flag != down.size()) {
		vector<vector<int> > cp_data(12, vector<int> (8));
		for (int i = 0; i < down.size(); i++) {
			if (che[i] == 1) continue;
			if (cp[down[i]][2] < 11 && data[cp[down[i]][2] + 1][cp[down[i]][1]] == 0 && cp_data[cp[down[i]][2] + 1][cp[down[i]][1]] == 0) {
				cp[down[i]][2]++;
				cp_data[cp[down[i]][2]][cp[down[i]][1]] = 1;
				data[cp[down[i]][2] - 1][cp[down[i]][1]] = 0;
				if (cp[down[i]][2] == 11 || data[cp[down[i]][2] + 1][cp[down[i]][1]] != 0) {
					che[i] = 1;
					flag++;
					data[cp[down[i]][2]][cp[down[i]][1]] = cp[down[i]][0];
				}
			}
			else {
				che[i] = 1;
				flag++;
				data[cp[down[i]][2]][cp[down[i]][1]] = cp[down[i]][0];
			}
		}
		show_puyo_w(data, score, cp, next, time);

	}


	return data;
}

vector<vector<int> > down_puyo_cp(vector<vector<int> > cp, vector<vector<int> > data) {
	vector<int> down(0);
	for (int i = 0; i < cp.size(); i++) {
		if (data[cp[i][2] + 1][cp[i][1]] == 0) {
			down.emplace_back(i);
			data[cp[i][2]][cp[i][1]] = 0;
		}
		else
			data[cp[i][2]][cp[i][1]] = cp[i][0];
	}

	vector<int> che(down.size());
	int flag = 0;
	while (flag != down.size()) {
		vector<vector<int> > cp_data(12, vector<int>(8));
		for (int i = 0; i < down.size(); i++) {
			if (che[i] == 1) continue;
			if (cp[down[i]][2] < 11 && data[cp[down[i]][2] + 1][cp[down[i]][1]] == 0 && cp_data[cp[down[i]][2] + 1][cp[down[i]][1]] == 0) {
				cp[down[i]][2]++;
				cp_data[cp[down[i]][2]][cp[down[i]][1]] = 1;
				data[cp[down[i]][2] - 1][cp[down[i]][1]] = 0;
				if (cp[down[i]][2] == 11 || data[cp[down[i]][2] + 1][cp[down[i]][1]] != 0) {
					che[i] = 1;
					flag++;
					data[cp[down[i]][2]][cp[down[i]][1]] = cp[down[i]][0];
				}
			}
			else {
				che[i] = 1;
				flag++;
				data[cp[down[i]][2]][cp[down[i]][1]] = cp[down[i]][0];
			}
		}
	}


	return cp;
}

void game_end() {
	cout << "=====GAME OVER=====" << endl;
	Sleep(3000);
	return;
}

vector<vector<vector<int> > > puyo_era(vector<vector<int> > check_puyo, vector<vector<int> > data, long long time) {
	vector<vector<vector<int> > > era(0);
	vector<vector<int> > v = {
		{0, 1, 0, -1},
		{1, 0, -1, 0}
	};

	for (int i = 0; i < check_puyo.size(); i++) {
		vector<vector<int> > kari(0);
		queue<vector<int> > puyo;
		puyo.push(check_puyo[i]);
		kari.emplace_back(check_puyo[i]);

		while (!puyo.empty()) {
			vector<int> clo = puyo.front(); puyo.pop();
			for (int i = 0; i < 4; i++) {
				if (clo[2] + v[1][i] >= 0 && clo[2] + v[1][i] <= 11 && clo[1] + v[0][i] >= 0 && clo[1] + v[0][i] <= 7 && data[clo[2] + v[1][i]][clo[1] + v[0][i]] == clo[0]) {
					vector<int> pu = { clo[0], clo[1] + v[0][i], clo[2] + v[1][i] };
					puyo.push(pu);
					kari.emplace_back(pu);
					data[clo[2]][clo[1]] = -1;
				}
			}
		}
		if (kari.size() >= 4) {
			era.emplace_back(kari);
		}
	}

	return era;
}

vector<vector<int> > data_era(vector<vector<int> > data, vector<vector<vector<int> > > era, int score, vector<vector<vector<int> > > next, long long time) {
	vector<vector<int> > table(12, vector<int>(8, -1));
	for (int i = 0; i < era.size(); i++) {
		for (int j = 0; j < era[i].size(); j++) {
			table[era[i][j][2]][era[i][j][1]] = 0;
		}
	}

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 8; j++) {
			if (table[i][j] == 0) {
				data[i][j] = 0;
			}
		}
	}

	show_puyo_w_era(data, score, era, next, time);
	Sleep(100);
	return data;
}

vector<vector<int> > drop_puyo(vector<vector<int> > data, vector<vector<vector<int> > > era) {
	vector<vector<int> > down;

	for (int i = 0; i < era.size(); i++) {
		for (int j = 0; j < era[i].size(); j++) {
			data[era[i][j][2]][era[i][j][1]] = 0;
		}
	}

	for (int i = 0; i < 8; i++) {
		int flag = 0;
		for (int j = 11; j >= 0; j--) {
			if (flag == 0) {
				if (data[j][i] == 0)
					flag++;
			}
			else {
				if (data[j][i] != 0) {
					vector<int> puyo = { data[j][i], i, j};
					down.emplace_back(puyo);
				}
			}
		}
	}

	return down;
}
