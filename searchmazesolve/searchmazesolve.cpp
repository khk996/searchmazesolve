// searchmazesolve.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

int make_maze(int maze[15][15])
{
	
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			maze[i][j] = 3;
		}
	}

	maze[1][1] = maze[1][2] = maze[1][3] = maze[1][4] = maze[1][6] = maze[1][7] = maze[1][9] = 0;
	maze[2][2] = maze[2][6] = maze[2][9] = maze[2][10] = maze[2][11] = 0;
	maze[3][1] = maze[3][2] = maze[3][3] = maze[3][4] = maze[3][5] = maze[3][6] = maze[3][7] = maze[3][8] = maze[3][9] = maze[3][11] = 0;
	maze[4][2] = maze[4][4] = 0;
	maze[5][1] = maze[5][2] = maze[5][4] = maze[5][5] = maze[5][6] = maze[5][7] = maze[5][8] = maze[5][9] = maze[5][10] = maze[5][11] = 0;
	maze[6][5] = maze[6][11] = maze[6][12] = maze[6][13] = 0;
	maze[7][1] = maze[7][2] = maze[7][3] = maze[7][4] = maze[7][5] = maze[7][6] = maze[7][11] = maze[7][13] = 0;
	maze[8][2] = maze[8][5] = maze[8][9] = maze[8][10] = maze[8][11] = maze[8][13] = 0;
	maze[9][1] = maze[9][2] = maze[9][5] = maze[9][6] = maze[9][8] = maze[9][9] = maze[9][11] = maze[9][13] = 0;
	maze[10][1] = maze[10][9] = maze[10][13] = 0;
	maze[11][1] = maze[11][5] = maze[11][6] = maze[11][7] = maze[11][13] = 0;
	maze[12][1] = maze[12][3] = maze[12][4] = maze[12][5] = maze[12][8] = maze[12][9] = maze[12][10] = maze[12][11] = maze[12][12] = 0;
	maze[13][1] = maze[13][2] = maze[13][3] = maze[13][5] = maze[13][6] = maze[13][7] = maze[13][8] = maze[13][10] = maze[13][12] = maze[13][10] = maze[13][13] = 0;

	return 0;
}
int search_state
(int x, int y, int state[4], int maze[15][15])
{
	state[0] = maze[x][y - 1];
	state[1] = maze[x + 1][y];
	state[2] = maze[x][y + 1];
	state[3] = maze[x - 1][y];

	//cout << "上：" << state[0] << "　右：" << state[1] << "　下：" << state[2] << "　左：" << state[3] << endl;

	return 0;
}

int *move(int x, int y, int state, int maze[15][15], bool go)
{
	int a[2];

	/*if (go)
		maze[x][y] = 1;
	else
		maze[x][y] = 2;
	*/
	if (!go)
		maze[x][y] = 2;

	switch(state)
	{
	case 0:
		y--;
		//cout << "上へ" << endl;
		break;
	case 1:
		x++;
		//cout << "右へ" << endl;
		break;
	case 2:
		y++;
		//cout << "下へ" << endl;
		break;
	case 3:
		x--;
		//cout << "左へ" << endl;
		break;
	default:
		break;
	}
	//cout << "(" << x << ", " << y << ")" << endl;
	a[0] = x;
	a[1] = y;

	return a;
}

int print_map(int maze[15][15])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			cout << maze[j][i];
		}
		cout << endl;
	}

	return 0;
}

int search_maze_width(vector<vector<vector<int>>> reachable, int state[4], int maze[15][15], 
	vector<vector<vector<int>>> next_reachable)
{
	bool stateis0 = false;
	vector<vector<vector<int>>> reset;

	for (int i = 0; i < reachable.size(); i++)
	{
		if ((reachable[i][0][0] == 13) && (reachable[i][0][1] == 13))
		{

		}

		search_state(reachable[i][0][0],reachable[i][0][1],state, maze);
		for (int j = 0; j < 4; j++)
		{
			if (state[j] == 0)
			{
				stateis0 = true;
				reachable[i].insert(reachable[i].begin(), { move(reachable[i][0][0], reachable[i][0][1], j, maze, true)[0],
					move(reachable[i][0][0], reachable[i][0][1], j, maze, true)[1] });
				next_reachable.insert(next_reachable.begin(),reachable[i]);
			}
		}
	}

	search_maze_width(next_reachable, state,maze, reset);

	return 0;
}

int print_root(vector<vector<vector<int>>> answer)
{
	for (int i = 0; i < answer.size(); i++)
	{
		for (int j = 0; answer[i].size(); j++)
		{
			cout << "(" << answer[i][answer[i].size() - j][0] << ", " << answer[i][answer[i].size() - j][0] << ") ->";
		}
		cout << endl;
	}
}
int main()
{
	int maze[15][15];
	int select_type;
	int x, y, i, j;
	int state[4];	//{上、右、下、左}
	bool stateis0;
	bool stateis1;
	vector<vector<vector<int>>> reachable;
	vector<vector<vector<int>>> next_reachable;
	vector<vector<int>> answer_root;
	bool isgoal;

	//初期化
	make_maze(maze);
	x = y = 1;
	maze[1][1] = 1;
	stateis0 = false;
	stateis1 = false;
	isgoal = false;
	reachable = {{{1,1}}};

	//探索方法の選択
	cin >> select_type;

	//探索
		switch (select_type)
		{
		case 0:	//縦型
			while ((x < 13) || (y < 13))
			{
				//print_map(maze);
				//cout << endl;
				//cout << "今：(" << x << ", " << y << ")" << endl;


				search_state(x, y, state, maze);

				for (i = 0; i < 4; i++)
				{
					if (state[i] == 0)
					{
						stateis0 = true;
						break;
					}
				}

				if (stateis0)
				{
					x = move(x, y, i, maze, true)[0];
					y = move(x, y, i, maze, true)[1];
				}
				else
				{
					for (j = 0; j < 4; j++)
					{
						if (state[j] == 1)
						{
							stateis1 = true;
							break;
						}
					}
					if (stateis1)
					{
						x = move(x, y, j, maze, false)[0];
						y = move(x, y, j, maze, false)[1];
					}
				}
				//cout << "(" << x << ", " << y << ")" << endl;
				stateis0 = stateis1 = false;
				maze[x][y] = 1;
			}
			break;
		case 1:	//横型
			search_maze_width(reachable, state, maze, next_reachable);

			print_root(next_reachable);
			/*
			while (1)
			{
				for (int i = 0; i < reachable.size(); i++)
				{
					if ((reachable[i][0][0] == 13) && (reachable[i][0][1] == 13))
					{
						isgoal = true;
						cout << "reached" << endl;
						answer_root = reachable[i];
						break;
					}	

					search_state(reachable[i][0][0], reachable[i][0][1], state, maze);
					cout << "now:(" << reachable[i][0][0] << ", " << reachable[i][0][0] << ")" << endl;
					for (int j = 0; j < 4; j++)
					{
						if (state[j] == 0)
						{
							stateis0 = true;
							next_reachable.push_back({ { move(reachable[i][0][0], reachable[i][0][1], j, maze, true)[0],
														move(reachable[i][0][0], reachable[i][0][1], j, maze, true)[1] } });
							cout << "next_rootable:(" << next_reachable[i][0][0] << ", " << next_reachable[i][0][1] << ")" ;
						}
					}
					cout << endl;

					if (!stateis0)
					{
						next_reachable.push_back({ { move(reachable[i][0][0], reachable[i][0][1], 2, maze, false)[0],
														move(reachable[i][0][0], reachable[i][0][1], 2, maze, false)[1] } });
						cout << "nonstepable" << endl;
					}
					stateis0 = false;
				}

				if (isgoal)	//終了条件
					break;

				reachable = next_reachable;
				
				for (int i = 0; i < next_reachable.size(); i++)
				{
					next_reachable.erase(next_reachable.begin());
				}
			}
			
			for (int i = 0; i < answer_root.size(); i++)
			{
				cout << "(" << answer_root[i][0] << ", " << answer_root[i][1] << ") -> " ;
			}
			cout << endl;
			isgoal = false;
			*/

			break;
		default:
			break;
		}

	print_map(maze);
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
