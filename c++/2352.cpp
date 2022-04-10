#include<iostream>
#include<algorithm>

using namespace std;

int n;
int ans;
int port[40001];
int dp[40001]; 
// �κ� ������ ���̰� i�� �� �� ���� ���� ������ ��
// ex . 5 2 6 1 8 3 4 7
// �� ��ġ�� �������� ������� �� ���� �� �κм��� ����
//      1 1 2 1 3 2 3 4
// dp={ 1,3,4,7 } (1���� index ����) => ������������ ���ĵ�

void init()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;
		port[i] = num;
		dp[i] = 0;
	}
	ans = 0;
}

int Binary(int start, int last, int num)
{
	// dp �߿��� num���� ���� ���� ū ���� �ε��� ���ϱ�
	// dp�� ��������
	int mid = (start + last) / 2;
	while (start <= last) {
		mid = (start + last) / 2;
		if (num > dp[mid]) {
			start = mid + 1;
		}
		else
			last = mid - 1;
	}
	return last;
}

void calculate()
{
	dp[1] = port[1];
	ans = 1;
	int start = 1;
	int last = 1;
	for (int i = 2; i <= n; i++) {
		// �κ� ���� ���� 1�� ���
		// �̺� Ž������ ã�� �� ���� ���
		if (port[i] < dp[1]) {
			dp[1] = port[i];
		}
		else {
			last = ans;
			int idx = Binary(start, last, port[i]);

			// ���ο� ���� �κ� ����
			if (dp[idx + 1] == 0) {
				dp[idx + 1] = port[i];
				ans++;
			}
			// ���� ���� �ִ� ���
			else {
				dp[idx + 1] = min(dp[idx + 1], port[i]);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	calculate();
	cout << ans;
}