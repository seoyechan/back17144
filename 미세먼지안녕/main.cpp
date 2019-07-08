#include <stdio.h>
#include <vector>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int nfiled[51][51];
int time;
int r, c;
int fresh_air_pos[4];

typedef struct pos{
	int x, y, value;
};
vector <pos> dust_v;

int dirx[4] = { 0, 0, 1, -1 };
int diry[4] = { 1, -1, 0, 0 };


int fnSol()
{
	for (int t = 0; t < time; t++)
	{
		////////
		int nextx = 0;
		int nexty = 0;
		for (int i = 0; i < dust_v.size(); i++)
		{
			int add_dust = 0;
			for (int j = 0; i < 4; j++)
			{
				nextx = dust_v[i].x + dirx[j];
				nexty = dust_v[i].y + diry[j];

				
				if (nextx >= 0 && nextx < r && nexty >= 0 && nexty < c && nfiled[nexty][nextx] != -1)
				{



					add_dust++;
				}
				nfiled[dust_v[i].y][dust_v[i].x] = (nfiled[dust_v[i].y][dust_v[i].x] / 5) * add_dust;


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
		for (int i = 0; i < c; i++){
			for (int j = 0; j < r; j++){
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


	}


	return 0;
}