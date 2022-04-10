#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

int n, m;
int* parent;
int result;

// ���Ͽ� ���ε�. ó���� �� ����� �θ� �ڱ� �ڽ�����
void init()
{
	cin >> n >> m;
	parent = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		parent[i] = i;
}

void end()
{
	cout << result;
	free(parent);
}

// ��� x�� �θ� ��带 ã�´�.
int find_parent(int x)
{
	if (x == parent[x])
		return x;	
	else
		return find_parent(parent[x]);
}

// ��� x, y�� ����ȴ� ����. ����Ŭ ����� break
// ���� �׷������� ����Ŭ�� x, y�� �θ� ��尡 ���� ��� �߻�
// ����Ŭ �� ����� ����Ǹ� y�� �θ� x�� �ȴ�.
void union_and_result()
{
	int x, y;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		x = find_parent(x);
		y = find_parent(y);

		if (x == y) {
			result = i;
			break;
		}
		parent[y] = x;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	union_and_result();
	end();
}