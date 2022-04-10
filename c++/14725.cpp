#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

int n, k;
vector<string>foods[1001];

// �ڽ� ��� ���� ����ü
// map �����̳��� count : key�� �����ϸ� 1, ������ 0
// �Է��� ������� count==1 �̸� �ű⿡ �ڽ� ��� ����
// ������ �� ��� ����
struct Node {
	map<string, Node>child;
};

// ������ ���� �Է�
void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> k;
		for (int j = 0; j < k; j++) {
			string s;
			cin >> s;
			foods[i].push_back(s);
		}
	}
}

// vector v�� idx��° �Է��� node�� ����
// �ش� string�� ������ ���� node�� ����
// ������ �� ���� string�� ���� ����
void insert(Node &node, vector<string>&v, int idx)
{
	// ���� ����� ��� (�� �̻� ���� �ڽ��� ����)
	if (idx == v.size())
		return;

	map<string, Node>::iterator iter;
	bool exit = false;

	// �ش� string ����
	for (iter = node.child.begin(); iter != node.child.end(); iter++) {
		if (iter->first == v[idx]) {
			exit = true;
			break;
		}
	}
	// �ش� string ���� => �� ��� ������
	if (!exit) {
		node.child[v[idx]] = Node();
	}
	// ���� string�� ���� ����
	insert(node.child[v[idx]], v, idx + 1);
}

// Ʈ���̿� ����� �� ���
// map�� �⺻������ ������������ ����
// �������� ���������� ����϶������Ƿ� �⺻�� �״�� ���θ� ��
void dfs(Node &node, int depth)
{
	// iterator �� ���� auto i : node.child �̷� ������ �ص� ��
	map<string, Node>::iterator iter;
	for (iter = node.child.begin(); iter != node.child.end(); iter++) {
		for (int idx = 0; idx < depth; idx++) {
			cout << "--";
		}
		cout << iter->first << '\n';
		dfs(iter->second, depth + 1);
	}
}

int main()
{
	init();
	Node root;

	// �Է¿� ���� Ʈ��(Ʈ����) �����
	for (int i = 0; i < n; i++) {
		insert(root, foods[i], 0);
	}

	// ���
	dfs(root, 0);
}

