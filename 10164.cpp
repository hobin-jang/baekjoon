#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int N, M, K;
int r, c; // ���׶�� ��ġ, (1,1)���� ����
int result = 0;
int path[16][16];

void init()
{
	cin >> N >> M >> K;
	memset(path, 0, sizeof(path));

	if (K != 0) {
		r = K / M + 1;
		c = K % M;

		if (c == 0) {
			r -= 1;
			c = M;
		}
	}
	else {
		r = 0;
		c = 0;
	}

	// ���ۺκ� 1�� ä���
	for (int i = 1; i <= N; i++) {
		path[i][1] = 1;
	}
	for (int i = 1; i <= M; i++) {
		path[1][i] = 1;
	}
}

// ������ ��ã��� ������ ����
// ���׶�̴� �ݵ�� ���İ��� ��
// ���׶�� ������ 1,1���� ���׶�̱��� ��ã��
// ���׶�̺��� N,M ���� ��ã�� �ٽ� ����
// ���׶�� ������ 1,1���� N,M���� ��ã��

// ���׶�� ���� ���
int dp1(int n, int m)
{
	if (n == 1 || m == 1) {
		return 1;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 2; j <= m; j++) {
			path[i][j] = path[i - 1][j] + path[i][j - 1];
		}
	}

	return path[n][m];
}

// ���׶�� �ִ� ���
int dp2(int n, int m, int r, int c)
{
	if (n == 1 || m == 1)
		return 1;

	for (int i = 2; i <= r; i++) {
		for (int j = 2; j <= c; j++) {
			path[i][j] = path[i - 1][j] + path[i][j - 1];
		}
	}

	for (int i = r; i <= n; i++) {
		path[i][c] = path[r][c];
	}
	for (int i = c; i <= m; i++) {
		path[r][i] = path[r][c];
	}

	for (int i = r + 1; i <= n; i++) {
		for (int j = c + 1; j <= m; j++) {
			path[i][j] = path[i - 1][j] + path[i][j - 1];
		}
	}

	return path[n][m];
}

int main()
{
	init();
	if (r == 0 && c == 0) {
		cout << dp1(N, M);
	}
	else {
		cout << dp2(N, M, r, c);
	}
}