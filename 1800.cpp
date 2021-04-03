#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;

int N, P, K;
vector<pair<int, int>>v[1001]; // i�� ���� {node, w} �� �����
int dist[1001]; // i�� ������ ��� �� ����ġ�� x ������ ��� ��, k���Ͽ�����

void init()
{
	cin >> N >> P >> K;
	for (int i = 0; i < P; i++) {
		int node1, node2, cost;
		cin >> node1 >> node2 >> cost;
		v[node1].push_back({ node2,cost });
		v[node2].push_back({ node1,cost });
	}
}

// N�� ������ ������ ��
// ����ġ�� x ������ ��� ���� K���� �۾ƾ��Ѵ�.
// ���ͽ�Ʈ��� �̸� �Ǵ�
// x�� 1~1,000,000 ���� �����鼭 �̺� Ž������ x ���ϱ�

bool dijkstra(int x)
{
	for (int i = 0; i <= 1000; i++)
		dist[i] = 987654321;
	
	// �켱 ���� ť : ������������ (top : ���� ����)
	// pair<int,int> : ����ġ(x ���� ���� ����), �������
	// 1�� ��尡 ���ͳ� ���� => 1������ Ž��
	// x���� ū ����ġ ���� ��θ� +1 ���ش�
	// �������� K�� ���ؼ� K ������ ���� �̺�Ž�� ����
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >pq;
	pq.push({ 0,1 });
	dist[1] = 0;

	while (!pq.empty()) {
		int cost = pq.top().first; // node������ �� ���� �����ϴ� ����
		int node = pq.top().second;

		pq.pop();

		// ť�� ���� �� ���̴� +1 �Ǵ� ����. ���� ��尡 �� ���� ���̸�
		// �Ʒ� ���� ���� ���ص� ��.
		if (dist[node] < cost)
			continue;

		for (int i = 0; i < v[node].size(); i++) {
			int next_node = v[node][i].first;
			int next_weight = v[node][i].second; // ���� ����ġ
			int next_cost = cost;

			// x���� ū ���
			if (next_weight > x) {
				next_cost += 1;
			}
			
			// ��� �� �� ���� ������ ������Ʈ
			if (next_cost < dist[next_node]) {
				dist[next_node] = next_cost;
				pq.push({ next_cost,next_node });
			}
		}
	}

	if (dist[N] <= K) 
		return true;
	
	else
		return false;
}

// �̺� Ž��
// dijkstra�� true�� mid ������ ����� => right = mid-1
// false�� mid������ ��� �� �� => left = mid+1
int binary_search(int left, int right)
{
	int result = -1;
	int mid = (left + right) / 2;
	while (left <= right) {
		mid = (left + right) / 2;
		if (dijkstra(mid)) {
			result = mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	cout << binary_search(0, 1000001);
}