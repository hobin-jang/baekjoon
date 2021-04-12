#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

#define INF 987654321
int n, m, x;
int dist[1001]; // ��������� ���������� �ּ� �Ÿ�
vector<pair<int, int>>v[1001]; // {���� ����, �Ÿ�}
int go[1001]; // ��Ƽ ��ұ��� i������ ����ؼ� �� �� �ּڰ�
int back[1001]; // ��Ƽ��ҿ��� i������ �� �� �ּڰ�
int result;

// ���ͽ�Ʈ��� ��� -> ���� �ּ� �Ÿ� ���ϰ�
// �ٽ� ���ͽ�Ʈ��� ���� -> ��� �ּҰŸ� ���ؼ�
// ���� �ִ��� ���� ����

void dist_init()
{
	fill(dist, dist + 1001, INF);
}

void init()
{
	cin >> n >> m >> x;
	for (int i = 0; i < m; i++) {
		int Start, End, Cost;
		cin >> Start >> End >> Cost;
		v[Start].push_back({ End,Cost });
	}
	result = 0;
	dist_init();
}

void dijkstra(int start, int last)
{
	dist_init();

	// �켱���� ť : {�Ÿ�, ���� ����}, ť���� �Ÿ� ������������ (top�� �Ÿ� ���� ª��)
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
	pq.push({ 0,start });
	dist[start] = 0;

	while (!pq.empty())
	{
		int cost = pq.top().first; 
		int now = pq.top().second;
		pq.pop();

		for (int i = 0; i < v[now].size(); i++)
		{
			int ncost = v[now][i].second;
			int next = v[now][i].first;

			if (dist[next] > dist[now] + ncost) {
				dist[next] = dist[now] + ncost;
				pq.push({ ncost,next });
			}
		}
	}

	// ��Ƽ ��ҿ��� �� ������ ���� ���
	if (last == -1) {
		for (int i = 1; i <= n; i++) {
			back[i] = dist[i];
		}
	}

	// ��Ƽ ��ҷ� ���� ���
	else
		go[start] = dist[last];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	// start���� x���� �ּ� �Ÿ� ���ϱ�
	for (int start = 1; start <= n; start++) {
		dijkstra(start, x);
	}

	// ���ƿ� �� �ּ� �Ÿ� ���ϱ�
	dijkstra(x, -1);

	// ���� ���� �ɸ� ��� ���ϱ�
	for (int i = 1; i <= n; i++) {
		if (i == x)
			continue;
		result = max(result, go[i] + back[i]);
	}

	cout << result;
}
