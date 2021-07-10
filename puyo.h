#pragma once
#include <vector>
using namespace std;

void show_puyo_w(vector<vector<int> > data, int score, vector<vector<int> > cp, vector<vector<vector<int> > > next, long long time);
vector<vector<int> > puyo_gene();
vector<vector<int> > move_x(vector<vector<int> > cp, int key, vector<vector<int> > data);
vector<vector<int> > fall_puyo(vector<vector<int> > cp);
vector<vector<int> > down_puyo(vector<vector<int> > cp, vector<vector<int> > data, int score, vector<vector<vector<int> > > next, long long time);
void game_end();
vector<vector<vector<int> > > puyo_era(vector<vector<int> > check_puyo, vector<vector<int> > data, long long time);
vector<vector<int> > data_era(vector<vector<int> > data, vector<vector<vector<int> > > era, int score, vector<vector<vector<int> > > next, long long time);
vector<vector<int> > drop_puyo(vector<vector<int> > data, vector<vector<vector<int> > > era);
vector<vector<int> > down_puyo_cp(vector<vector<int> > cp, vector<vector<int> > data);