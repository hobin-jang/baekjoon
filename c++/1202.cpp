#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n, k;
priority_queue<long long> pq;
vector<long long>weight;
vector<pair<long long, long long>>jewel;
int jewel_idx;

void init()
{
	cin >> n >> k;
	vector<pair<long long, long long>> vec;
	for (int i = 0; i < n; i++) {
		long long m, v;
		cin >> m >> v;
		pair<long long, long long> p = { m, v };
		vec.push_back(p);
	}

	for (int i = 0; i < k; i++) {
		long long c;
		cin >> c;
		weight.push_back(c);
	}

	sort(weight.begin(), weight.end()); // �������� ����

	// ���� ū ���溸�� ���ſ� �ֵ� ����
	long long max_w = weight[weight.size() - 1];

	for (int i = 0; i < vec.size(); i++) {
		if (vec[i].first <= max_w)
			jewel.push_back(vec[i]);
	}

	// ���� �������� ���� (����, ��ġ)
	sort(jewel.begin(), jewel.end());

	// �� ��° �������� Ȯ���ߴ��� üũ��
	jewel_idx = 0; 
}

// �켱���� ť�� ���� ��ġ ���������ǰ�
// ������ ��������
// ���� ���Ժ��� ������ ��� ���� pq�� �ֱ�
// �ܼ��� ��ġ �ո� ���ϴ� ���̹Ƿ�
// �켱���� ť�� top�� �ִ� ���� ���� ���� ���Կ� ���� �� �ִ� �ִ� ��ġ

long long find_value(int idx)
{
	long long w = weight[idx];
	long long result = 0;

	for (int i = jewel_idx; i < jewel.size(); i++) {
		long long mass = jewel[i].first;
		long long value = jewel[i].second;

		if (mass <= w) {
			pq.push(value);
			jewel_idx++;
		}

		else {
			jewel_idx = i;
			break;
		}
	}

	if (pq.empty())
		return result;
	else {
		result += pq.top();
		pq.pop();
		return result;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	long long result = 0;
	for (int i = 0; i < weight.size(); i++) {
		result += find_value(i);
	}

	cout << result;
}