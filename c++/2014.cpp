#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int k, n;
	map<long long, bool>check; // �ߺ� ���ſ�
	vector<long long>num; // �־��� ��
	priority_queue<long long, vector<long long>, greater<long long>>q; // �켱���� ť ��������

	cin >> k >> n;
	for (int i = 0; i < k; i++) {
		long long p;
		cin >> p;
		num.push_back(p);
	}

	// 1�� �켱���� ť�� ���� ����
	// �켱���� ť�� top���ҿ� num�� ���� ��� ���س���
	// �׷� num�� ������ �̷���� �켱���� ť ���� �� ����
	// ex. ť : 1 => ť : 2 3 5 7
	// => 2 * (2, 3, 5, 7), 3 * (2, 3, 5, 7), ... �� ť�� (���� ť�� ���Ҵ� pop) 
	// => ť :  4 6 9 10 14 ...
	// N�� ������ top�� ���ϰ��� �ϴ� �� (�ߺ� �����ؾ� �� n�� ���ư�)
	// ť�� N�� �̻� and max������ ũ�� �� �ʿ� ���� => ��¥�� N��° ���� ��

	q.push(1);
	check[1] = true;
	long long max_value = 0;

	while (n--) {
		long long now = q.top();
		q.pop();

		for (auto i : num) {
			long long next = now * i;

			// next�� �̹� ���� ��� : �ߺ��� ��� : �н�
			if (check.count(next)) {
				continue;
			}

			// ť�� n�� �Ѱ� �ְ� max ������ ū ���� �������� �ϸ�
			// �� �༮�� ��¥�� n��° ���� �� : �н�
			if (q.size() > n) {
				if (max_value <= next) {
					continue;
				}
			}

			// ������ : ť�� ���� �� �ִ� ���
			q.push(next);
			max_value = max(max_value, next);
			check[next] = true;
		}
	}

	cout << q.top();
}