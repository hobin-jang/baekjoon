#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int a, b, c;

typedef struct edge {
	int dist;
	int from;
	int to;
}edge; // �Ÿ�, ���, ����

vector<edge>vec; // ���� ���� ����, ���߿� �Ÿ� ������������ �����ؼ� ���
int parent[100001];
int result;

// vec sort �� �� ���� (����ġ ��������)
bool cmp(const edge& a, const edge& b)
{
	if (a.dist < b.dist)
		return true;
	else if (a.dist == b.dist) {
		if (a.from < b.from)
			return true;
		else if (a.from == b.from)
			if (a.to < b.to)
				return true;
	}
	return false;
}

// ũ�罺Į �˰��� �̿��� MST
// ��θ� ��� �������� ���� �� ����Ŭ �� ����� �̾��ش�.
// ����ġ ���� ū ������ ���� (�ش� �κ� �߶� ���� 2�� ����� ��)

void init()
{
	cin >> n >> m;
	while (m--) {
		cin >> a >> b >> c;
		edge e = { c, a, b };
		vec.push_back(e);
	}
	result = 0;
}

// �θ� ��� �ʱ�ȭ
void init_parent()
{
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}
}

// ��� x�� �ֻ��� �θ� ��� ã��
int find_parent(int x)
{
	if (x == parent[x])
		return x;
	else {
		parent[x] = find_parent(parent[x]);
		return parent[x];
	}
}

// ��� x�� ��� y�� �θ� ��� ��ġ��
void union_parent(int x, int y)
{
	int p_x = find_parent(x);
	int p_y = find_parent(y);

	parent[p_y] = p_x;
}

// ��� x, ��� y ������ ����Ŭ ������� �Ǵ�
bool is_cycle(int x, int y)
{
	int p_x = find_parent(x);
	int p_y = find_parent(y);
	if (p_x == p_y)
		return true; // ����Ŭ �߻�
	else
		return false; // ����Ŭ �߻� X
}

// vec ����ġ ���� �������� ����
void sorting_vec()
{
	sort(vec.begin(), vec.end(), cmp);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	sorting_vec();

	init_parent();

	int x, y, d;
	int max_possible_dist = 0; // ���� ������ ���� ����ġ �� �ִ�
	for (int i = 0; i < vec.size(); i++) {
		x = vec[i].from;
		y = vec[i].to;
		d = vec[i].dist;

		if (parent[x] != parent[y]) {
			if (is_cycle(x, y))
				continue;

			union_parent(x, y);
			result += d;
			max_possible_dist = d;
		}
	}

	result -= max_possible_dist;
	cout << result;
}