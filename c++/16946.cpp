#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>

using namespace std;

int n, m;
int map[1001][1001]; // ���� ��
pair<int,int> zero_map[1001][1001]; // 0�� ���� ī��Ʈ �� �� {���� ��ȣ, ī��Ʈ}
vector<pair<int, int>>zero_vec; // 0���� ����� ��ġ ���� Ž����
bool visited[1001][1001]; // 0 Ž�� ���� Ȯ�ο�

int result[1001][1001]; // ���� ���

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 }; // �����¿�

// 0���� ����� ��ġ���� ���� ���� ī��Ʈ (�Ź� Ž���� �ƴ� �� �� Ž������ �� ����)
// 1 ��ġ���� �����¿� Ž���ϸ鼭 0 ������ �� ���� + 1 (�ڱ� �ڽ�) % 10

void init()
{
	cin >> n >> m;
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		for (int j = 0; j < m; j++) {
			if (s[j] == '0')
				map[i][j] = 0;
			else
				map[i][j] = 1;
		}
		s.clear();
	}
	memset(visited, false, sizeof(visited));
}

void countZeros()
{
	// bfs�� 0 ����� ��ġ�� �� ������ ī��Ʈ
	queue<pair<int, int>> q;

	int section = 0; 
	// ���߿� 1 ��ġ���� �����¿� Ž���� �� ���� �����̸� ���ϸ� �� �Ǵ� �� üũ��

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			q = queue<pair<int, int>>{};
			zero_vec.clear();
			section++;

			if (map[i][j] == 1)
				continue;
			if (visited[i][j] == true)
				continue;

			q.push({ i,j });
			visited[i][j] = true;

			while (!q.empty()) {
				pair<int, int>zero = q.front();
				q.pop();
				zero_vec.push_back(zero);

				for (int k = 0; k < 4; k++) {
					int ny = zero.first + dy[k];
					int nx = zero.second + dx[k];

					if (ny < 0 || ny >= n || nx < 0 || nx >= m)
						continue;
					if (visited[ny][nx] == true)
						continue;
					if (map[ny][nx] == 1)
						continue;

					q.push({ ny, nx });
					visited[ny][nx] = true;
				}
			}

			int zero_size = zero_vec.size();
			for (auto zero : zero_vec) {
				zero_map[zero.first][zero.second] = { section,zero_size };
			}
		}
	}
}

void getResult()
{
	// 1 ��ġ���� �����¿� ���鼭 0 �̸� �� ��ġ ���� �� + 1
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				result[i][j] = 0;
				continue;
			}

			if (map[i][j] == 1) {
				int sum = 1;
				vector<int>section_check; // �����¿� ���� üũ��

				for (int k = 0; k < 4; k++) {
					int ni = i + dy[k];
					int nj = j + dx[k];

					bool check = false;

					if (ni < 0 || ni >= n || nj < 0 || nj >= m)
						continue;

					if (map[ni][nj] == 0) {
						for (auto section : section_check) {
							if (section == zero_map[ni][nj].first){
								check = true;
								break; // �̹� üũ �� ����
							}
						}

						if (check == false) {
							section_check.push_back(zero_map[ni][nj].first);
							sum += zero_map[ni][nj].second;
						}
					}
				}
				section_check.clear();

				sum %= 10;
				result[i][j] = sum;
			}
		}
	}
}

void printResult()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << result[i][j];
		}
		cout << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	countZeros();
	getResult();
	printResult();
}