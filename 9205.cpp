#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//���� �� �ڽ� : max 20��
//50m�� �� �� ���ž���

int t, n;
vector<int>graph[102]; //���, ���� ����
bool check[102];
vector<pair<int, int>>location;

int dist(pair<int, int>p, pair<int, int>q)
{
	int dx = abs(p.second - q.second);
	int dy = abs(p.first - q.first);
	return dx + dy;
}

void dfs(int idx)
{
	check[idx] = true;

	for (int i = 0; i < graph[idx].size(); i++)
	{
		int next = graph[idx][i];
		if (!check[next])
			dfs(next);
	}
}

void init_and_start()
{
	for (int i = 0; i < 102; i++)
	{
		graph[i].clear();
		check[i] = false;
	}
	location.clear();

	cin >> n;
	int s1, s2; //������
	cin >> s1 >> s2;
	location.push_back({ s2,s1 });
	for (int i = 0; i < n; i++) {
		int y, x;
		cin >> x >> y;
		location.push_back({ y,x });
	}
	int e1, e2; //����
	cin >> e1 >> e2;
	location.push_back({ e2,e1 });
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;
	while (t--)
	{
		init_and_start();

		//������ ��� �ֱ�
		for (int i = 0; i < location.size(); i++)
		{
			for (int j = i + 1; j < location.size(); j++)
			{
				pair<int, int>p1 = location[i];
				pair<int, int>p2 = location[j];
				if (dist(p1, p2) <= 1000) 
				{
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
			}
		}

		//ó���� 0��° ���, �������� n+1���� ���
		dfs(0);

		if (check[n + 1])
			cout << "happy" << '\n';
		else
			cout << "sad" << '\n';
	}
}