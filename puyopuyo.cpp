#include <iostream>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "menu.h"
#include "puyo.h"

using namespace std;

int main() {
	/*ぷよぷよ@パクリ始まるよ*/
	do {
		/*オープニング*/
		int op = opening();
		if (op == 2) {
			break;
		}

		/*メインループ*/
		int game_flag = 0;
		do {
			int flag = 1;
			int score = 0;
			vector<vector<int> > data(12, vector<int>(8));
			vector<vector<int> > cp(2, vector<int>(3));
			vector<vector <vector<int> > > next(2);
			cp = puyo_gene();
			next[0] = puyo_gene();
			next[1] = puyo_gene();

			long long time_start;
			long long game_start;
			time_start = clock();
			game_start = clock();
			while (1) {
				if (data[0][3] != 0 || data[0][4] != 0) {
					game_end();
					break;
				}

				if (clock() - game_start >= 180000) {
					time_up();
					break;
				}

				if (flag == 0) {
					cp = next[0];
					next[0] = next[1];
					next[1] = puyo_gene();
					flag = 1;
					time_start = clock();
				}
				srand(time(NULL));

				if (flag == 1 && clock() - time_start >= 1000) {
					vector<vector<vector<int> > > era;
					if (cp[0][2] < 11 && cp[1][2] < 11) {
						if (data[cp[0][2] + 1][cp[0][1]] == 0 && data[cp[1][2] + 1][cp[1][1]] == 0) {
							cp = fall_puyo(cp);
							time_start = clock();
						}
						else {
							/*ぷよの処理*/
							//下に下げる
							vector<vector<int> > cp_pre = cp;
							cp = down_puyo_cp(cp, data);
							data = down_puyo(cp_pre, data, score, next, game_start);
							flag = 0;
							
							//連鎖処理
							int i = 0; //連鎖回数を保持して点数計算に利用
							while (1) {
								era = puyo_era(cp, data, game_start);
								score += (long long)era.size() * 100 * pow(2, i);

								vector<vector<int> > down_pu = drop_puyo(data, era);

								data = data_era(data, era, score, next, game_start);
								vector<vector<int> > data_pr = data;

								data = down_puyo(down_pu, data, score, next, game_start);
								cp = down_puyo_cp(down_pu, data_pr);

								if (cp.size() == 0) break;

								i++;
							}
						}
					}
					else {
						/*ぷよの処理*/
						flag = 0;
						data[cp[0][2]][cp[0][1]] = cp[0][0];
						data[cp[1][2]][cp[1][1]] = cp[1][0];
						era = puyo_era(cp, data, game_start);

						//消えたやつの間を埋める
						int i = 0;
						while (1) {
							era = puyo_era(cp, data, game_start);
							score += (long long)era.size() * 100 * pow(2, i);

							vector<vector<int> > down_pu = drop_puyo(data, era);

							data = data_era(data, era, score, next, game_start);
							vector<vector<int> > data_pr = data;

							data = down_puyo(down_pu, data, score, next, game_start);
							cp = down_puyo_cp(down_pu, data_pr);

							if (cp.size() == 0) break;
							i++;
						}
					}
				}
				if (_kbhit()) {
					int key = _getch();
					if (flag == 1)
					    cp = move_x(cp, key, data);
				}
				show_puyo_w(data, score, cp, next, game_start);
			}
			game_flag = game_select();
		} while (game_flag == 0);
	} while (1);

	system("cls");
	cout << "See you next time!!!!!" << endl;
	Sleep(3000);

	return 0;
}