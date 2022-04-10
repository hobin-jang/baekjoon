#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

vector<int>tree[1000001]; // ���� Ʈ��
vector<int>top_down[1000001]; // �θ�->�ڽĸ� ������ Ʈ��
int dp[1000001][2];
int n;

// ��Ʈ�� 1������
void make_tree()
{
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);

		dp[i][0] = -1;
		dp[i][1] = -1;
	}

	dp[n][0] = -1;
	dp[n][1] = -1;
}

// root�� 1�� ��, parent ����� �ڽ� ��� ���ϱ�
// �������� free ��Ű��

// �θ� ��尡 �󸮾���͸� �ڽ��� ��� ����
// �θ� �󸮾���� �ƴϸ� �ڽ��� ������ �󸮾����
// �̸� �̿��ϱ� ���� top_down ����
void make_top_down(int parent, int node)
{
	// parent : node�� �θ���
	for (int i = 0; i < tree[node].size(); i++) {
		int child = tree[node][i];
		if (child == parent)
			continue;
		top_down[node].push_back(child);
		make_top_down(node, child);
	}
}

// dp[i][0] : i�� ��尡 �󸮾���� �ƴϰ�
// i�� ��尡 root�� ����Ʈ���� �󸮾���� �ּڰ�
// dp[i][1] : i�� ��尡 �󸮾�����̰� ����Ʈ���� �󸮾���� �ּڰ�
// dfs �̿��� 
// dfs(parent, state) : state�� 0�̸� �ڽ��� ������ �󸮾�����̹Ƿ�
// dp[parent][0] += dfs(childe,1) �� child ��ŭ dfs�� �ݺ�
// state�� 1�̸� �ڽ��� �������
// dp[parent][1] += min(dfs(child,0), dfs(child,1)) �� child ��ŭ dfs �ݺ�

int dfs(int parent, int state)
{
	// ���� ����� ���
	if (top_down[parent].empty()) {
		if (state == 0)
			return 0;
		else
			return 1;
	}

	// ����Ʈ������ ��� �Ϸ�� ���
	if (dp[parent][state] != -1) {
		return dp[parent][state];
	}

	// �θ� �󸮾���� �ƴ� ���, �ڽ��� ������ �󸮾����
	if (state == 0) {
		dp[parent][state] = 0;
		for (int i = 0; i < top_down[parent].size(); i++) {
			dp[parent][state] += dfs(top_down[parent][i], 1);
		}
	}

	// �θ� �󸮾������ ���, �ڽ��� ������� (min��)
	else {
		dp[parent][state] = 1;
		for (int i = 0; i < top_down[parent].size(); i++) {
			dp[parent][state] += min(dfs(top_down[parent][i], 0), dfs(top_down[parent][i], 1));
		}
	}

	return dp[parent][state];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_tree();
	make_top_down(1, 1);

	// ��Ʈ(1)�� �󸮾������ ���, �ƴ� ��� �� �ּڰ��� ����
	int answer = min(dfs(1, 0), dfs(1, 1));
	cout << answer;
}


