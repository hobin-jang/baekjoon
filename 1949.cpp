#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;

int n;
int people[10001];
vector<int>town[10001];
int dp[10001][2];
bool check[10001];

void make_town()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> people[i];
		check[i] = false;
		dp[i][1] = 0;
		dp[i][0] = 0;
	}
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		town[a].push_back(b);
		town[b].push_back(a);
	}
}

// ���� ��尡 ��������̸� ���� ������ ������ �� ��
// ���� ��尡 ������� �ƴϸ� ���� ������ ��� ����
// dp[i][0] : i�� ������ ������� �ƴҶ� �ִ밪
// dp[i][1] : i�� ������ ������� �϶� �ִ�
// dp[i][0] = dp[i][0] + max(dp[next][0], dp[next][1])
// dp[i][1] = dp[i][1] + dp[next][0]
// �ִ��� ���ϴ� ���̹Ƿ� �� ���� ���� ���� �ȵǴ� ��� ����
void dfs(int node)
{
	// �����Ǿ��� �� �� �Ǿ��� �� �⺻��
	dp[node][0] = 0;
	dp[node][1] = people[node];
	check[node] = true;

	for (int i = 0; i < town[node].size(); i++) {
		int next = town[node][i];
		if (check[next] == false) {
			dfs(next);
			dp[node][0] += max(dp[next][0], dp[next][1]);
			dp[node][1] += dp[next][0];
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_town();
	int root = 1; // Ʈ���̹Ƿ� ���ǻ� 1�� ��Ʈ�� ����
	dfs(root);

	cout << max(dp[root][0], dp[root][1]);
}


