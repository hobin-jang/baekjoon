#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m, k;
char arr[101][101];
string s;
int slen;

int dp[101][101][81];
// dp[a][b][c] = d : (a,b)�� �����ϴ� ���ڰ� c��° ������ �� ������ ����� �� = d
// (a,b) ��ġ ��Ž�� �� c��° ������ �� ������ ��찡 d���̹Ƿ� �̸� ��Ž���ϰ��� �ϴ� ��ο� ���ϸ� ��
// ��δ� dfs�� Ž��

vector<pair<int, int>> start; // ������ ��ġ
int dy[4] = { 0,0,-1,1 };
int dx[4] = { 1,-1,0,0 };
vector<pair<int, int>> loc; // ������ �� �ִ� ��ġ

void init()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}
	cin >> s;
	slen = s.size();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == s[0])
				start.push_back({ i, j });
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= k; j++) {
			pair<int, int> p = { dy[i], dx[i] };
			p = { p.first * j, p.second * j };
			loc.push_back(p);
		}
	}

	memset(dp, -1, sizeof(dp));
}

int dfs(int r, int c, int idx)
{
	if (dp[r][c][idx] != -1)
		return dp[r][c][idx]; // ������ ã�� ��� ����

	if (idx + 1 == slen)
		return 1; // ��� �ϳ� ã��

	dp[r][c][idx] = 0;

	for (auto jump : loc) {
		int nr = r + jump.first;
		int nc = c + jump.second;

		if (nr < 0 || nr >= n || nc < 0 || nc >= m)
			continue;

		if (arr[nr][nc] == s[idx + 1]) {
			dp[r][c][idx] += dfs(nr, nc, idx + 1);
		}
	}

	return dp[r][c][idx];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	int res = 0;
	for (auto st : start) {
		res += dfs(st.first, st.second, 0);
	}

	cout << res;
}