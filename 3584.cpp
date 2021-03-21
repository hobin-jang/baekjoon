#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int t, n;
vector<int>tree[10001];
bool check[10001];

int Log = 14;
int parent[10001][14]; 
// parent[i][j] : i�� ����� 2^j��° �θ�, 2^13<10000<2^14
// parent[i][j] = parent[parent[i][j-1]][j-1] ����

int depth[10001]; // ����� depth ���ϱ�
int node1, node2;

int find_root[10001]; // ��Ʈ ��� ã��� 

void make_tree()
{
	// Ʈ�� �ʱ�ȭ
	for (int i = 0; i < 10001; i++) {
		tree[i].clear();
		check[i] = false;
		memset(parent[i], sizeof(parent[i]), 0);
		depth[i] = -1;
		find_root[i] = 0;
	}

	// Ʈ�� �Է�
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);

		find_root[b] = a;
	}

	// ���� ��� �Է�
	cin >> node1 >> node2;
}

// node�� �ٷ� ���κа� ���� �� depth���ϱ�
void dfs(int node, int Depth)
{
	check[node] = true;
	depth[node] = Depth;
	for (int i = 0; i < tree[node].size(); i++) {
		int next_node = tree[node][i];
		if (check[next_node] == false) {
			parent[next_node][0] = node;
			dfs(next_node, Depth + 1);
		}
	}
}

// ��Ʈ ��� ���ϱ�
// ���� Ʈ���� ��Ʈ �ƹ��ų� �ص� ��������� �������� �θ� �־������Ƿ�
// ��Ʈ�� ���ؼ� set_parent ������
int Find_root()
{
	for (int node = 1; node <= n; node++)
		if (find_root[node] == 0)
			return node;
}

// ��ü �θ� ���� ����
void set_parent(int root)
{
	dfs(root, 0); // ��Ʈ ��� root, ��Ʈ ����� depth=0
	for (int jump = 1; jump < Log; jump++) {
		for (int node = 1; node <= n; node++) {
			parent[node][jump] = parent[parent[node][jump - 1]][jump - 1];
		}
	}
}

int LCA(int node1, int node2)
{
	// node2�� �� ��� �ִ� ������ ����
	if (depth[node1] > depth[node2])
		swap(node1, node2);

	// �� ����� ���� �����ϵ��� ����
	for (int i = Log - 1; i >= 0; i--) {
		if (depth[node2] - depth[node1] >= (1 << i)) {
			node2 = parent[node2][i];
		}
	}

	// �θ� ���� ��� ã��
	if (node1 == node2)
		return node1;

	for (int i = Log - 1; i >= 0; i--) {
		if (parent[node1][i] != parent[node2][i]) {
			node1 = parent[node1][i];
			node2 = parent[node2][i];
		}
	}

	return parent[node1][0];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;
	while (t--) {
		make_tree();
		int root = Find_root();
		set_parent(root);
		cout << LCA(node1, node2) << '\n';
	}
}