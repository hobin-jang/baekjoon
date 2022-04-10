#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int n, m;
long long inf = 9223372036854775807; // ���Ѵ� (long long max)
vector<long long>v; // �� ��� �ִ� �ð� (v[1] : ���) 
vector<pair<pair<int, int>, int>>edge; // {{���, ����}, ����ġ}
int check = 0;

void make_bus()
{
	cin >> n >> m;
	v.resize(n + 1, inf);
	while (m--) {
		int a, b, c;
		cin >> a >> b >> c;
		edge.push_back({ {a,b},c });
	}
}

void Bellman_Ford()
{
	// 1�� ��� 0���� 
	// n-1 �� ���鼭 ��� �� �� ��� ��� (inf) �Ѿ��
	// �� ���̶� ���� ��� ���� ������Ʈ

	v[1] = 0;
	for (int i = 1; i <= (n - 1); i++) {
		for (int j = 0; j < edge.size(); j++) {
			int from = edge[j].first.first;
			int to = edge[j].first.second;
			int cost = edge[j].second;

			if (v[from] == inf)
				continue;
			if (v[to] > (v[from] + cost))
				v[to] = (v[from] + cost);
		}
	}

	// ��� edge�� ���� �� �� �� Ž���ϸ鼭 ���� �׷������� �Ǵ�
	// �ش� ��� ���� inf�� 1������ ����Ͽ� ���� ��� ����
	// ������Ʈ�� �ٽ� �Ͼ�� ���� ����Ŭ ���� : ������ �۾����Ƿ� ������ �׷���

	for (int i = 0; i < edge.size(); i++) {
		int from = edge[i].first.first;
		int to = edge[i].first.second;
		int cost = edge[i].second;

		// from ��� ���� ��� X
		if (v[from] == inf) 
			continue;

		// ������ �׷��� : check = -1�� ����
		if (v[to] > (v[from] + cost)) {
			check = -1;
			return;
		}
	}
}

int main()
{
	make_bus();
	if (n == 1)
	{
		cout << 0;
		return 0;
	}

	Bellman_Ford();

	if (check == -1)
	{
		cout << -1;
		return 0;
	}

	else {
		for (int i = 2; i <= n; i++) {
			if (v[i] == inf)
				cout << -1 << '\n';
			else
				cout << v[i] << '\n';
		}
	}
}