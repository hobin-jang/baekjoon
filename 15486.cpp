#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, t, p;
int arr[1500002][2];
int dp[1500002];

void init()
{
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> t >> p;
		arr[i][0] = t;
		arr[i][1] = p;
	}
	memset(dp, 0, sizeof(dp));
}

// i �� ° �� t �� �� �� �� : i+t �Ͽ� �� ���´ٰ� ����
// dp[x] = max(dp[x], P_i + dp[i]) (i+t=x)
// n+1���� ū ���� ��� X

int getResult() {
	int result = 0;
	int current = 0; // ���� �� ���� �ִ밪

	for (int i = 1; i <= (n + 1); i++) {
		int T = arr[i][0];
		int P = arr[i][1];

		int x = i + T;
		current = max(current, dp[i]);
		if (x > (n + 1)) {
			result = max(result, current);
		}
		else {
			dp[x] = max(dp[x], P + current);
			result = max(result, current);
		}
	}

	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	init();
	cout << getResult();
}