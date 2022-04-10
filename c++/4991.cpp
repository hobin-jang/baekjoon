#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

int w, h;
char room[21][21];
bool visited[21][21];
vector<pair<int, int>>dots; // �κ�, ������ ��
int dist[11][11]; // 0���� �κ� ���� ��ġ
bool finish; // ���� �� ����
bool impossible; // �Ұ����� ��� (-1)
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 }; // �����¿�
int result; // ���
int bit_check; // �� ��� �� üũ�� (�ʱ�ȭ : 0b1111..1 : dots.size() ��ŭ), �ִ� 11�� (�κ� û�ұ� ����) �̹Ƿ� 11bit

void init()
{
	memset(room, 0, sizeof(room));
	memset(visited, false, sizeof(visited));
	memset(dist, 0, sizeof(dist));
	dots.clear();
	finish = false;
	impossible = false;
	result = 987654321;
	bit_check = 0;

	cin >> w >> h;

	if (w == 0 && h == 0) {
		finish = true;
		return;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> room[i][j];

			if (room[i][j] == 'o') {
				// �κ� ���� ��ġ : 0��
				vector<pair<int, int>>::iterator it = dots.begin();
				dots.insert(it, { i, j });
			}

			if (room[i][j] == '*') {
				dots.push_back({ i, j });
			}
		}
	}

	for (int i = 0; i < dots.size(); i++) {
		bit_check = bit_check | (1 << i);
	}
}

void getDist()
{
	queue<pair<pair<int, int>, int>>q;
	// {{���� ��ġ}, �Ÿ�}

	// bfs�� �� ������ �Ÿ� ���ϱ�

	for (int start_idx = 0; start_idx < dots.size(); start_idx++) {
		
		for (int end_idx = start_idx + 1; end_idx < dots.size(); end_idx++) {

			pair<int, int> start_dot = dots[start_idx];
			pair<int, int> end_dot = dots[end_idx];

			memset(visited, false, sizeof(visited));
			visited[start_dot.first][start_dot.second] = true;
			q = queue<pair<pair<int, int>, int>>(); // ť �ʱ�ȭ
			q.push({ start_dot, 0 });

			dist[start_idx][end_idx] = 987654321;

			while (!q.empty()) {

				pair<int, int>loc = q.front().first;
				int d = q.front().second;
				q.pop();

				if (loc == end_dot) {
					dist[start_idx][end_idx] = min(dist[start_idx][end_idx], d);
					continue;
				}

				for (int i = 0; i < 4; i++) {
					int ny = loc.first + dy[i];
					int nx = loc.second + dx[i];

					if (ny < 0 || ny >= h || nx < 0 || nx >= w)
						continue;

					if (room[ny][nx] == 'x')
						continue;

					if (visited[ny][nx] == true)
						continue;

					visited[ny][nx] = true;
					q.push({ {ny, nx}, d + 1 });
				}
			}

			// �� ���� ���
			if (dist[start_idx][end_idx] == 987654321) {
				impossible = true;
				result = -1;
				return;
			}
			else {
				dist[end_idx][start_idx] = dist[start_idx][end_idx];
				impossible = false;
			}
		}
	}
}

void dfs(int idx, int check, int sum)
{
	// dfs�� Ž���ϸ鼭 �Ÿ� �� �ּ� ���ϱ�
	// idx : Ž���ϴ� ��� ��ȣ (0 : �κ� ���� ��ġ)
	// check : bit ���� �� ��� Ž�� ���� Ȯ��

	if (bit_check == check) {
		result = min(result, sum);
		return;
	}

	bool chk = check & (1 << idx);

	if (chk == true) {
		return;
	}

	check = check | (1 << idx);

	for (int i = 0; i < dots.size(); i++) {
		dfs(i, check, sum + dist[idx][i]);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		init();

		if (finish)
			break;

		getDist();

		if (impossible) {
			cout << result << '\n';
			continue;
		}
		else {
			dfs(0, 0, 0);
			cout << result << '\n';
		}
	}
}