#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n, m;
vector<int>v[32001]; // {A, B} : A�� B���� �ݵ�� ����
int degree[32001]; // ������ ����
vector<int>result; // ���� ���

void init()
{
	cin >> n >> m;
	memset(degree, 0, sizeof(degree));
	for (int i = 0; i < m; i++) {
		int A, B;
		cin >> A >> B;
		v[A].push_back(B);
		degree[B]++;
	}
}

// ���� ����
void topological_sort()
{
	priority_queue<int, vector<int>, greater<int>>q; // �켱���� ���� ������ ���� ���� �ź��� Ǯ����Ѵ�.
	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0)
			q.push(i);
	}

	while (!q.empty()) {
		int node = q.top();
		q.pop();
		result.push_back(node);

		for (int i = 0; i < v[node].size(); i++) {
			int nextnode = v[node][i];
			degree[nextnode]--;
			if (degree[nextnode] == 0)
				q.push(nextnode);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	topological_sort();

	for (int i = 0; i < result.size(); i++)
		cout << result[i] << ' ';
}