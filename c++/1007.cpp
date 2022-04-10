#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;

pair<int, int>dots[21]; 
vector<vector<int>>minuses; // 20C10 ��� ����
double result; // ���� �� ũ�� �ִ� 20�� ��Ʈ2 * 10 < 400��

// ���͸� �� �� �� ���͸� ���� �� �ش� ���� ũ�� ���ϴ� ����
// ������ �������� ���� n�� �� �� n/2�� ���� ����, ������ n/2�� ���� ����
// 20C10 ���� ������ (���� to ��) ������ index ���� �� ���
// 20C10 = 184756

// 20C10 ���ϱ�
void combination(vector<int>& arr, vector<int>& comb, int r, int idx, int depth)
{
	if (r == 0) {
		minuses.push_back(comb);
	}

	else if (depth == arr.size())
		return;

	else {
		comb[idx] = arr[depth];
		combination(arr, comb, r - 1, idx + 1, depth + 1);
		combination(arr, comb, r, idx, depth + 1);
	}
}

void make_combination(int n)
{
	int r = n / 2;
	vector<int>arr(n);
	vector<int>comb(r);
	for (int i = 0; i < n; i++)
		arr[i] = i;

	int idx = 0;
	int depth = 0;

	combination(arr, comb, r, idx, depth);
	arr.clear();
	comb.clear();
}

// p1, p2 �Ÿ� ���ϱ�
// �ִ� 20�� * ��Ʈ2
double distance(pair<int, int>p)
{
	double y = (double)p.first;
	double x = (double)p.second;

	double d = sqrt(y * y + x * x);
	return d;
}

// n/2���� ����, �������� ����
double calculate(vector<int>& v, int n)
{
	bool check[21];
	memset(check, false, sizeof(check));

	int y = 0;
	int x = 0;

	for (int i = 0; i < v.size(); i++) {
		int idx = v[i];
		check[idx] = true;
		y -= dots[idx].first;
		x -= dots[idx].second;
	}

	for (int i = 0; i < n; i++) {
		if (check[i] == false) {
			y += dots[i].first;
			x += dots[i].second;
		}
	}

	pair<int, int>p = { y,x };

	return distance(p);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;

		for (int i = 0; i < N; i++) {
			int y, x;
			cin >> y >> x;
			dots[i] = { y,x };
		}

		result = numeric_limits<double>::max();

		minuses.clear();
		make_combination(N);

		for (int i = 0; i < minuses.size(); i++) {
			double tmp = calculate(minuses[i], N);
			result = min(result, tmp);
		}

		printf("%.6lf", result);
		printf("\n");
	}
}