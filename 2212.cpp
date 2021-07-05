#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<long long>v; // ���� ����Ʈ
vector<long long>dist; // ���� �� �Ÿ� �� ����Ʈ
int n, k;

void init()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}
}

long long find_min()
{
	long long result = 0;

	// ���� �� �Ÿ� �� ���ϱ�
	// ���� �� �Ÿ� �� �� ���� �� �� n-k�� ���� ����

	// ���� �������� ����
	sort(v.begin(), v.end());
	
	// ���� �Ÿ� �� ���ϱ�
	for (int i = 0; i < (v.size() - 1); i++) {
		long long sensor1 = v[i];
		long long sensor2 = v[i + 1];

		long long d = sensor2 - sensor1;

		dist.push_back(d);
	}

	sort(dist.begin(), dist.end());

	for (int i = 0; i < (n - k); i++) {
		result += dist[i];
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cout.tie(NULL);
	init();

	// k >=n : ������ ���߱� �� �޸� ��
	if (k >= n)
		cout << 0;
	else
		cout << find_min();
}