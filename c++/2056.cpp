#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n;
int times[10001]; // �ش� �۾� �ɸ��� �ð�
vector<int>PreWork[10001]; // [i]�� ���� �۾����� ������ ���
int degree[10001]; // �׷��� ����

void init()
{
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int weight, pre_cnt; 
		// weight: �ð�, pre_cnt : ���� �۾� ����
		
		cin >> weight;
		cin >> pre_cnt;

		times[i] = weight;

		degree[i] = pre_cnt;

		for (int j = 0; j < pre_cnt; j++) {
			int pre_work;
			cin >> pre_work;
			PreWork[pre_work].push_back(i);
		}
	}
}

int topology()
{
	int result = 987654321;

	// �켱���� ť : pair = {�ɸ� �ð�, ��� ��ȣ}
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> >pq;
	
	// ���� 0�� �͵� �ֱ�
	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0) {
			pq.push({ times[i], i });
		}
	}

	while (!pq.empty())
	{
		int w = pq.top().first;
		int node = pq.top().second;
		pq.pop();

		result = w;

		for (int i = 0; i < PreWork[node].size(); i++) {
			int nextnode = PreWork[node][i];
			degree[nextnode]--;

			if (degree[nextnode] == 0) {
				pq.push({ w + times[nextnode], nextnode });
			}
		}
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	cout << topology();
}