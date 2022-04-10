#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int n, m;
vector<int>student[32001]; // vector : i�� �л����� ū �л���
int degree[32001]; // ���� ����

void make_student()
{
	cin >> n >> m;
	while (m--)
	{
		int a, b;
		cin >> a >> b;
		student[a].push_back(b);
		degree[b]++;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_student();

	// ���� ���� ����
	queue<int>q;
	for (int i = 1; i <= n; i++)
		if (degree[i] == 0)
			q.push(i);

	while (!q.empty())
	{
		int num = q.front();
		q.pop();
		cout << num << ' ';
		for (int i = 0; i < student[num].size(); i++) {
			degree[student[num][i]]--;
			if (degree[student[num][i]] == 0)
				q.push(student[num][i]);
		}
	}
}