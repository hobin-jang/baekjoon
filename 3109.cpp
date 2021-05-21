#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int r, c;
char map[10001][501];
bool visited[10001][501]; // �湮 ����, ������ �׻� �湮���� ó��
int dy[3] = { -1,0,1 };
int dx[3] = { 1,1,1 };
int result = 0;

void make_map()
{
	cin >> r >> c;
	for (int i = 1; i <= r; i++) {
		string s;
		cin >> s;
		for (int j = 1; j <= s.size(); j++) {
			map[i][j] = s[j - 1];
			visited[i][j] = false;
			if (s[j - 1] == 'x') {
				visited[i][j] = true;
			}
		}
	}
}

// 1,1 ���� �ִ��� �밢�� ���� �� ������ ��� �� ������ �밢�� �Ʒ��� ����
// ���� ���� false�� �� �̻� �� �� ����
// x ��ġ c�϶��� ��ΰ� �� ��
bool dfs(int y, int x)
{
	visited[y][x] = true;

	if (x == c) {
		result++;
		return true;
	}

	for (int i = 0; i < 3; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 1 || ny > r || nx < 1 || nx > c)
			continue;

		if (map[ny][nx] == 'x')
			continue;

		if (visited[ny][nx] == false && map[ny][nx] == '.') {
			if(dfs(ny, nx))
				return true;
		}
	}

	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_map();

	for (int i = 1; i <= r; i++) {
		visited[i][1] = true;
		dfs(i, 1);
	}

	cout << result;
}