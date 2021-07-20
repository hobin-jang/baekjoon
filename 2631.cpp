#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;

int n;
int* arr;
int* dp;

void init()
{
	cin >> n;
	arr = (int*)malloc(sizeof(int) * (n + 1));
	dp = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 1;i <= n;i++) {
		int num;
		cin >> num;
		arr[i] = num;
	}
}

void init_dp() {
	for (int i = 1;i <= n;i++) {
		dp[i] = 0;
	}
}

// �������� ����
int calc1() {

	init_dp();
	// ù ��° �� ������ ũ�� 1 (ù ��° �ε��� = 1)
	dp[arr[1]] = 1;

	for (int i = 2;i <= n;i++) {
		int num = arr[i];

		int before_max = 0;
		for (int j = num - 1;j > 0;j--) {
			if (dp[j] != 0) {
				before_max = max(before_max, dp[j]);
			}
		}

		dp[num] = max(dp[num], before_max + 1);
	}

	// ���� ū ��������
	int result = 0;
	for (int i = 1;i <= n;i++) {
		result = max(result, dp[i]);
	}

	return n - result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	cout << calc1();

}