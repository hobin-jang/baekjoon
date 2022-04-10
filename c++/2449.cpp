#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, k;
vector<int>vec;
int dp[201][201]; // dp[n][k] : n ~ k ��° �������� �ּ� ��ȯ Ƚ��
int inf = 987654321;

void init()
{
	cin >> n >> k;
	vec.resize(n, 0);
	for (int i = 0; i < n; i++) {
		cin >> vec[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = -1;
		}
	}
}

int calculate(int start, int last)
{
	// ���� ����
	if (start == last)
		return 0;

	// �̹� ���� ����
	if (dp[start][last] != -1)
		return dp[start][last];

	// start to last �ּ� ���� ��� ����
	dp[start][last] = inf;

	for (int i = start; i < last; i++) {

		// �ٸ� �� ���������� ���
		int tmp = 0;
		if (vec[start] != vec[i + 1])
			tmp = 1;

		// start to i �ּڰ�
		int start_to_i = calculate(start, i);
		// i+1 to last �ּڰ�
		int i_plus_one_to_last = calculate(i + 1, last);

		// start to last�� �ּڰ��� min(������, start to i �ּڰ� + i+1 to last �ּڰ� + start �� i+1 ���̿� ���� �� �ٲ�� �� ���� (0,1)
		dp[start][last] = min(dp[start][last], start_to_i + i_plus_one_to_last + tmp);
	}

	return dp[start][last];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	cout << calculate(0, n - 1);
}