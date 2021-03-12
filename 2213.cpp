#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<set>

using namespace std;

int n;
int weight[10001];
vector<int>tree[10001];
bool check[10001];
int dp[10001][2];
vector<int>result; // ���
bool check2[10001]; // ��ο��� ���� ��� ���� ���� Ȯ��

// ���� ��尡 �������� ���Ҹ� ���� ���� ������ �ȵ�
// ���� ��尡 �������� ���� �ƴϸ� ���� ���� ��� ����
// dp[i][0] : i�� �������� �ƴ� ��, i�� ��Ʈ�� �ϴ� ����Ʈ�������� �ִ�
// dp[i][1] : i�� �������� �� ��, "
// dp[i][0] += max(dp[next][0], dp[next][1])
// dp[i][1] += dp[next][0]

void make_tree()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> weight[i];

		check[i] = false;
		check2[i] = false;

		dp[i][0] = 0;
		dp[i][1] = 0;
	}
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
}

void search(int node)
{
	check[node] = true;
	dp[node][0] = 0;
	dp[node][1] = weight[node];

	for (int i = 0; i < tree[node].size(); i++) {
		int next = tree[node][i];
		if (check[next] == false) {
			search(next);
			dp[node][0] += max(dp[next][0], dp[next][1]);
			dp[node][1] += dp[next][0];
		}
	}
}

// dp[node][1] > dp[node][0] �̸鼭 ����� ��尡 ��ο� ���� �� �Ǿ�����
// �μ� : ���� ���, ���� ���
void path(int node, int prev)
{
	if (dp[node][1] > dp[node][0]) {
		if (check2[prev] == false) {
			result.push_back(node);
			check2[node] = true;
		}
	}

	for (int i = 0; i < tree[node].size(); i++) {
		int next = tree[node][i];
		if (next != prev)
			path(next, node);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_tree();
	search(1); // ��Ʈ 1�� ����
	path(1, 1); // ��Ʈ 1�� �θ� ���� �ڱ� �ڽ����� ó��
	sort(result.begin(), result.end());

	cout << max(dp[1][0], dp[1][1]) << '\n';
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << ' ';
}