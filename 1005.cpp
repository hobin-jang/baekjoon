#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int T, n, k, w;
int weight[1001]; // �� ��� ����ġ ����, 0���� �ʱ�ȭ
vector<int>v[1001]; // i�� ���� ������ ��� ����
int result[1001]; // �� ����� ������ �ּڰ�, ��Ʈ�� �ڱ� �ڽ�����
int degree[1001]; // �� ����� ���� (fan-in)

// ���� ���� �̿�
// ���� ��� �� �Ϸ�� �� + �ڽ��� ����ġ�� �ִ��� ���ϸ� ��
// result[next] = max(result[next], result[node]+weight[next])
// node�� ���� 0�� ���, next�� node�� �ڽ� ���
void init()
{
	cin >> n >> k;
	for (int i = 0; i <= 1000; i++) {
		weight[i] = 0;
		v[i].clear();
		result[i] = 0;
		degree[i] = 0;
	}
	for (int i = 1; i <= n; i++)
		cin >> weight[i];
	for (int i = 0; i < k; i++) {
		int prev, next;
		cin >> prev >> next;
		v[prev].push_back(next);
		degree[next]++;
	}
	cin >> w;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	while (T--) {
		// �ʱ�ȭ
		init();

		// ���� ������ ���� ���� q�� ����
		queue<int>q;
		for (int i = 1; i <= n; i++) {
			if (degree[i] == 0) {
				q.push(i);
				result[i] = weight[i];
			}
		}

		// �������� ����
		while (!q.empty()) {
			int node = q.front();
			q.pop();

			if (node == w)
				break;

			for (int i = 0; i < v[node].size(); i++) {
				int next = v[node][i];
				result[next] = max(result[next], result[node] + weight[next]);

				degree[next]--;
				if (degree[next] == 0)
					q.push(next);
			}
		}

		cout << result[w] << '\n';
	}
}