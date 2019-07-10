#include <stdio.h>
#include <vector>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int nfiled[51][51];
int time;
int r, c;
int nRet;
int fresh_air_pos[4];

typedef struct pos{
	int x, y, value;
};
vector <pos> dust_v;
vector <pos> dust_add_v;

int dirx[4] = { 0, 0, 1, -1 };
int diry[4] = { 1, -1, 0, 0 };

int fnSol()
{
	for (int t = 0; t < time; t++)
	{
		////////
		int nextx = 0;
		int nexty = 0;
		int dust_size = dust_v.size();

		dust_add_v.clear();
		for (int i = 0; i < dust_size; i++)
		{
			int add_dust = 0;
			for (int j = 0; j < 4; j++)
			{
				nextx = dust_v[i].x + dirx[j];
				nexty = dust_v[i].y + diry[j];

				if (nextx >= 0 && nextx < c && nexty >= 0 && nexty < r && nfiled[nexty][nextx] != -1)
				{
					dust_add_v.push_back({ nextx, nexty, dust_v[i].value / 5 });
					add_dust++;
				}
			}
			nfiled[dust_v[i].y][dust_v[i].x] = (dust_v[i].value - ((dust_v[i].value / 5) * add_dust));
		}

		for (int i = 0; i < dust_add_v.size(); i++){
			nfiled[dust_add_v[i].y][dust_add_v[i].x] += dust_add_v[i].value;
		}

		for (int i = fresh_air_pos[1] - 2; i >= 0; i--){
			nfiled[i + 1][0] = nfiled[i][0];
		}
		for (int i = 1; i < c; i++){
			nfiled[0][i - 1] = nfiled[0][i];
		}
		for (int i = 1; i <= fresh_air_pos[1]; i++){
			nfiled[i - 1][c - 1] = nfiled[i][c - 1];
		}
		for (int i = c - 2; i >= 1; i--){
			nfiled[fresh_air_pos[1]][i + 1] = nfiled[fresh_air_pos[1]][i];
		}
		nfiled[fresh_air_pos[1]][1] = 0;

		for (int i = fresh_air_pos[3] + 2; i < r; i++){
			nfiled[i - 1][0] = nfiled[i][0];
		}
		for (int i = 1; i < c; i++){
			nfiled[r - 1][i - 1] = nfiled[r - 1][i];
		}
		for (int i = r - 2; i >= fresh_air_pos[3]; i--){
			nfiled[i + 1][c - 1] = nfiled[i][c - 1];
		}
		for (int i = c - 2; i >= 1; i--){
			nfiled[fresh_air_pos[3]][i + 1] = nfiled[fresh_air_pos[3]][i];
		}
		nfiled[fresh_air_pos[3]][1] = 0;

		dust_v.clear();
		for (int i = 0; i < r; i++){
			for (int j = 0; j < c; j++){
				if (nfiled[i][j] != 0 && nfiled[i][j] != -1){
					dust_v.push_back({ j, i, nfiled[i][j] });
				}
			}
		}

	}
	return 0;
}




int main()
{
	int t;
	int test_case;

	freopen("input.txt", "r", stdin);

	scanf("%d",&t);
	for (test_case = 1; test_case <= t; ++test_case)
	{
		scanf("%d %d %d", &r, &c, &time);

		int index = 0;
		dust_v.clear();

		for (int i = 0; i < r; i++){
			for (int j = 0; j < c; j++){
				scanf("%d", &nfiled[i][j]);
				if (nfiled[i][j] == -1){
					fresh_air_pos[index] = j;
					index++;
					fresh_air_pos[index] = i;
					index++;
				}
				else if (nfiled[i][j] != 0){
					dust_v.push_back({ j, i, nfiled[i][j] });
				}
			}
		}

		fnSol();

		nRet = 2;
		for (int i = 0; i < r; i++){
			for (int j = 0; j < c; j++){
				nRet += nfiled[i][j];
			}
		}
		printf("#%d %d\n", test_case, nRet);
	}


	return 0;
}