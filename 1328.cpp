#include <iostream>

using namespace std;

int n, l, r;
long long dp[101][101][101] = { 0 };

#define mod 1000000007

void init()
{
	cin >> n >> l >> r;

	// base
	// 0�� �� l, r�� ���� ���� ����
	// dp[n][l][r] = 0 , where, n = 0 or l = 0 or r = 0
	// dp[1][1][1] = 1, dp[2][1][2] = 1, dp[2][2][1] = 1
	// �������� ���
	// dp[n+1][l][r] = 
	// dp[n][l-1][r] (���� ���� �� �� ���ʿ� ����� ���) + 
	// dp[n][l][r-1] (���� ���� �� �� �����ʿ� ����� ���) + 
	// dp[n][l][r] * (n-1) (���� ���� �� n�� ����� ���̿� ���� �ִ� ���)

	dp[1][1][1] = 1;
	dp[2][2][1] = 1;
	dp[2][1][2] = 1;
}

int main()
{
	init();

	for (int i = 2; i < n; i++) { // n+1 �� ������� ����ؼ� �길 i < n ����
		for (int j = 1; j <= l; j++) {
			for (int k = 1; k <= r; k++) {
				dp[i + 1][j][k] = dp[i][j - 1][k] + dp[i][j][k - 1] + dp[i][j][k] * (i - 1);
				dp[i + 1][j][k] %= mod;
			}
		}
	}

	cout << dp[n][l][r];
}