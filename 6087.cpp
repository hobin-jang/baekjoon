#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
#include<string>
#include<cstdio>

using namespace std;

int w, h;
char map[101][101];
pair<int, int>p1 = { -1,-1 }; // c�� �� ��
pair<int, int>p2 = { -1,-1 }; // c�� �ٸ� ��
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 }; // �����¿� index = 0,1,2,3
int check[101][101]; 
// check : �ſ� ��ġ ����
// �ش� ���� check������ ���� ���� ������ 
// �ش� ������ �� ���� �ſ� ��ġ�ϴ� ��� ����

void make_map()
{
	cin >> w >> h;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'C') {
				if (p1.first == -1) {
					p1 = { i,j };
				}
				else {
					p2 = { i,j };
				}
			}
			check[i][j] = 987654321;
		}
	}
}

// ������ ���� ������� �ľ�
// -1�̸� �� �Ǵ� ���
// 0�̸� �����ϴ� ���
// 1�̸� 90���� ���̴� ���
int possible(int dir, int ndir)
{
	if (dir == 0 && ndir == 1)
		return -1;
	else if (dir == 1 && ndir == 0)
		return -1;
	else if (dir == 2 && ndir == 3)
		return -1;
	else if (dir == 3 && ndir == 2)
		return -1;
	else if (dir == ndir)
		return 0;
	else
		return 1;
}

// ���� ��ġ���� ���� ���ϱ�
int cal_dir(int y, int x, int ny, int nx)
{
	// �����¿� 0123
	if (y > ny && x == nx)
		return 0;
	else if (y < ny && x == nx)
		return 1;
	else if (y == ny && x > nx)
		return 2;
	else if (y == ny && x < nx)
		return 3;
	else
		return -1;
}

int bfs()
{
	// �켱���� ť �������� ����
	// üũ �� -1�̸� �����ϰ� ť ����
	// �ƴϸ� üũ ���� �۾����� ��츸 ť ����
	// ť : { {�ſ� ��ġ Ƚ��, �� ����}, { ��ġ y, x} }
	// �� ���� : 0123 �� �����¿�
	priority_queue<pair<pair<int,int>, pair<int, int>>, vector<pair<pair<int,int>,pair<int,int>>>, greater<pair<pair<int,int>, pair<int,int>>> >q;
	//queue < pair<pair<int, int>, pair<int, int>>>q;
	q.push({ {0,0},{p1.first, p1.second} });
	q.push({ {0,1},{p1.first, p1.second} });
	q.push({ {0,2},{p1.first, p1.second} });
	q.push({ {0,3},{p1.first, p1.second} });
	check[p1.first][p1.second] = 0;

	int result = 0;

	while (!q.empty())
	{
		int y = q.top().second.first;
		int x = q.top().second.second;
		int cnt = q.top().first.first;
		int dir = q.top().first.second;
		//int y = q.front().second.first;
		//int x = q.front().second.second;
		//int cnt = q.front().first.first;
		//int dir = q.front().first.second;

		if (y == p2.first && x == p2.second) {
			q.pop();
			continue;
		}

		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			int ndir = cal_dir(y, x, ny, nx);
			int ncnt = cnt;

			if (ny >= 0 && ny < h && nx >= 0 && nx < w) {
				// ���̸� ���� �Ұ�
				if (map[ny][nx] == '*')
					continue;
				// �����¿� �ƴ� ���
				if (ndir == -1)
					continue;
				
				int pos = possible(dir, ndir);
				// �ݴ�������� �� ��������
				if (pos == -1)
					continue;
				else {
					// ���̴� ���
					if (pos == 1)
						ncnt++;
					if (check[ny][nx] >= ncnt) {
						check[ny][nx] = ncnt;
						q.push({ {ncnt, ndir},{ny,nx} });
					}
				}
			}
		}
	}

	result = check[p2.first][p2.second];
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("input.txt", "r", stdin);

	make_map();
	int result = bfs();

	cout << result;
}