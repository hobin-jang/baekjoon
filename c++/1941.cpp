#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

char map[5][5];

int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int result = 0;

void init()
{
	for (int i = 0; i < 5; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < 5; j++) {
			map[i][j] = s[j];
		}
	}
}

// 7�� �ڸ��� ����Ǿ����� Ȯ���ϰ� S�� 4 �̻����� Ȯ��
bool bfs(vector<int>&comb)
{
	bool visited[5][5]; // �ش� ��ġ �湮 ����
	bool check[5][5]; // ������ ��ġ ���� �ƴ��� üũ
	memset(visited, false, sizeof(visited));
	memset(check, false, sizeof(check));

	// S�� 4�� �̻����� Ȯ��
	int sum = 0;
	for (int i = 0; i < comb.size(); i++) {
		int num = comb[i];
		if (map[num / 5][num % 5] == 'S')
			sum++;
		check[num / 5][num % 5] = true;
	}

	if (sum < 4) {
		return false;
	}
	
	else {
		queue<pair<int, int>>q;
		int first = comb[0];

		q.push({ first / 5, first % 5 });
		visited[first / 5][first % 5] = true;

		int cnt = 1; // ���� ���� ī��Ʈ

		// 7�� �� �������� Ȯ��
		while (!q.empty())
		{
			int y = q.front().first;
			int x = q.front().second;

			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];

				if (ny < 0 || ny >= 5 || nx < 0 || nx >= 5)
					continue;

				if (visited[ny][nx] == false) {
					if (check[ny][nx] == true) {
						visited[ny][nx] = true;
						cnt++;
						q.push({ ny,nx });
					}
				}
			}
		}

		if (cnt == 7) {
			return true;
		}
		else {
			return false;
		}
	}
}

// ���� ���� �� [i][j] �� �ڸ��� 4*i+j �� ����
// 0 1 2 3
// 4 5 6 7
// ...

// ������ ���鼭 0~24 �� 7�� �� ���� ���
// S�� 4 �̻��� ��쿡 ����
// ��� �������� Ȯ��
// �� �����ϸ� result++
void combination(vector<int>&arr, vector<int>&comb, int r, int idx, int depth)
{
	// �� ���� ���
	// ��ȣ ������������ ��
	if (r == 0) {
		if (bfs(comb))
			result++;
	}

	// �� �̴ٰ� r�� �� ä�� ���
	else if (depth == arr.size())
		return;

	else {
		// arr[depth] ���� ���
		comb[idx] = arr[depth];
		combination(arr, comb, r - 1, idx + 1, depth + 1);

		// �� ���� ���
		combination(arr, comb, r, idx, depth + 1);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	vector<int>arr(25);
	for (int i = 0; i < 25; i++) {
		arr[i] = i;
	}

	int r = 7;
	vector<int>comb(r);

	combination(arr, comb, r, 0, 0);

	cout << result;
}