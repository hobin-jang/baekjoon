#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, s, t;
vector<pair<int, int>>vec; // {���� �ð�, �� �ð�}
int res;

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s >> t;
		vec.push_back({ s, t });
	}
	res = 0;
}

void sorting()
{
	sort(vec.begin(), vec.end()); // ���� �ð� ���� ��, �� �ð� ���� ��
}

void result()
{
	priority_queue<int, vector<int>, greater<int>> pq;
	// �켱 ���� ť�� ������ �ð� ���� ������ ����
	// �׷� ���� �ð� ���� ������ �Է� �����鼭 
	// �켱���� ť�� top ������ ������ �ð����� ������
	// ���ο� ���ҷ�(������ �ð���), 
	// �����ų� ������ 
	// �� ���� ������ �̾ �� �� �ִ� �Ŵ� pop �ϰ� 
	// ���ο� ���ҷ�(������ �ð���)

	pq.push(vec[0].second);

	for (int i = 1; i < n; i++) {
		int end_time = pq.top();
		int new_start_time = vec[i].first;
		int new_end_time = vec[i].second;
		if (end_time > new_start_time) {
			// �� ���� ����
			pq.push(new_end_time);
		}
		else {
			// �� ���� ����
			pq.pop();
			pq.push(new_end_time);
		}
	}

	res = pq.size();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	sorting();
	result();
	cout << res;
}