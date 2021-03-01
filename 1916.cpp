#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int n, m;
vector<pair<int, int>>v[1001]; // [i] : ���, {����, ����ġ}
int dist[1001];
int From, To;

void make_map()
{
	cin >> n;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		v[from].push_back({ to,weight });
	}
	cin >> From >> To;

	// ���ͽ�Ʈ�� : ó�� ��� inf�� �ʱ�ȭ
	for (int i = 1; i <= n; i++)
		dist[i] = 987654321;
}

// �켱���� ť �̿��� ���ͽ�Ʈ��
void dijkstra(int start)
{
	dist[start] = 0; // �������� 0���� �ʱ�ȭ
	// �⺻ ��������, ����ġ ���� ������ ����ϹǷ�
	// ���� ����ġ �־�� ��
	priority_queue<pair<int, int>>pq; // {����ġ, ���}
	pq.push({ 0,start });

	while (!pq.empty())
	{
		int d = (-1) * pq.top().first; // ����ġ ����� ��ȯ
		int current = pq.top().second;
		pq.pop();

		// ���� ��ΰ� ���� ���� ��κ��� ������ ����� �ʿ� ����
		if (dist[current] < d)
			continue;

		// ������ ��� �˻�
		for (int i = 0; i < v[current].size(); i++) {
			int next = v[current][i].first;
			int next_d = d + v[current][i].second;

			// ��� ����
			if (dist[next] > next_d) {
				dist[next] = next_d;
				pq.push({ (-1) * next_d, next });
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_map();
	dijkstra(From);
	cout << dist[To];
}