#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

int n;
vector<int>graph[101]; // �־��� �׷���
vector<int>inv_graph[101]; // ������ �׷���
bool visited[101]; // SCC ���鼭 ��� üũ��
stack<int>stk; // SCC�� �ʿ��� ����
vector<int>result; 

// �־��� �Է��� 1->a, 2->b, ... ���� �׷����� ����
// SCC �̿��ؼ� ������ ����� �͵� ���� ��󳻸� �ִ�� ���� ��

void init()
{
	cin >> n;
	int node;
	for (int i = 1; i <= n; i++) {
		cin >> node;
		graph[i].push_back(node);
		inv_graph[node].push_back(i);
	}

	memset(visited, false, sizeof(visited));

	// ���� ��� ��������
	for (int i = 1; i <= n; i++) {
		sort(graph[i].begin(), graph[i].end());
		sort(inv_graph[i].begin(), inv_graph[i].end());
	}
}

void dfs(int node)
{
	// dfs�� ����� �ֵ� Ž��
	// ������ ������ ���ÿ� �ֱ�
	// node : ���� ����

	visited[node] = true;

	for (auto next_node : graph[node]) {
		if (visited[next_node])
			continue;
		dfs(next_node);
	}
	stk.push(node);
}

void dfs_inv(int node, vector<int>& vec)
{
	// ���� top���� ������ �׷������� dfs 

	visited[node] = true;
	vec.push_back(node);

	for (auto next_node : inv_graph[node]) {
		if (visited[next_node])
			continue;
		dfs_inv(next_node, vec);
	}
}

void SCC()
{
	// �ڻ���� �˰������� SCC ���ϱ�

	for (int node = 1; node <= n; node++) {
		if (visited[node])
			continue;
		dfs(node);
	}

	memset(visited, false, sizeof(visited));
	vector<int>vec; // �������� �����

	while (!stk.empty()) {
		int start = stk.top();
		stk.pop();

		if (visited[start])
			continue;

		dfs_inv(start, vec);

		// vec Ȯ��
		// ���� 2�� �̻��̸� scc
		// 1���ε� �ڱ� �ڽ� �����ѵ� scc

		if (vec.size() >= 2) {
			for (auto num : vec) {
				result.push_back(num);
			}
		}
		if (vec.size() == 1) {
			int num = vec[0];
			if (graph[num][0] == num)
				result.push_back(num); // graph�� �� 1���� ����
		}

		vec.clear();
	}

	// ����� ��������
	sort(result.begin(), result.end());
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	SCC();

	cout << result.size() << '\n';

	for (auto num : result) {
		cout << num << '\n';
	}
}