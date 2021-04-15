#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n, m;
int map[101][101]; //  ġ�� ��
bool air[101][101]; // �ٱ� ����, true�� �ٱ� ����
bool check[101][101]; // Ž���Ұ�, �̹� Ž�� : false, Ž�� ���� : true
vector<pair<int, int>>v; // ������ ġ�� ��ġ {y,x}
int time;
int cheese; // ��ü ġ�� ����, 0�Ǹ� time �׸� ���

int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

void make_map()
{
	cin >> n >> m;

	time = 0;
	cheese = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0)
				check[i][j] = false;
			else {
				check[i][j] = true;
				cheese++;
			}
			air[i][j] = false;
		}
	}
}

// ó�� �ٱ� ���� ���ϱ�
void first_Air()
{
	queue<pair<int, int>>q;
	q.push({ 0,0 }); // �� �����ڸ��� ����
	air[0][0] = true;

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
				if (air[ny][nx])
					continue;

				if (map[ny][nx] == 0) {
					q.push({ ny,nx });
					air[ny][nx] = true;
				}
			}
		}
	}
}

// �������� ġ������ üũ ���� true�� ������ ġ��
bool bye(int y, int x)
{
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
			if (air[ny][nx])
				cnt++;
		}
	}

	if (cnt >= 2)
		return true;
	else
		return false;
}

// {Y,X}���� ������ ġ�� ã��
void bfs(int Y, int X)
{
	// {Y,X} : Ž�� ���� ġ�� ��ġ (������ ġ��)
	queue<pair<int, int>>q;
	q.push({ Y,X });
	check[Y][X] = false;
	
	if (bye(Y, X))
		v.push_back({ Y,X });

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			// �� �ȿ� ����
			if (ny >= 0 && ny < n && nx >= 0 && nx < m)
			{
				// Ž�� ������ ���
				if (check[ny][nx] == true) {
					// ������ ġ���� ���
					if (bye(ny, nx)) {
						v.push_back({ ny,nx });
					}
					q.push({ ny,nx });
					check[ny][nx] = false;
				}
			}
		}
	}
}

// ġ�� ����
void delete_cheese()
{
	for (int i = 0; i < v.size(); i++) {
		map[v[i].first][v[i].second] = 0;
	}
	cheese -= (int)(v.size());
}

// ���ο� �ٱ� ����, ���ŵ� ġ��� �ٱ� �����̹Ƿ� 
// ��׵�� bfs ������ ���ο� �ٱ� ���� ���� �� �ִ�.
void new_Air()
{
	queue<pair<int, int>>q;
	for (int i = 0; i < v.size(); i++) {
		q.push({ v[i].first, v[i].second });
		air[v[i].first][v[i].second] = true;
	}

	v.clear();

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			
			if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
				if (map[ny][nx] == 0) {
					if (air[ny][nx] == false) {
						q.push({ ny,nx });
						air[ny][nx] = true;
					}
				}
			}
		}
	}
}

void init_check()
{
	memset(check, false, sizeof(check));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 1)
				check[i][j] = true;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_map();

	first_Air();

	while (cheese != 0)
	{
		init_check();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 1) {
					if (check[i][j]) {
						bfs(i, j);
					}
				}
			}
		}

		delete_cheese();
		new_Air();
		time++;
	}

	cout << time;
}