#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

typedef long long ll;

int n;
// n�� �Է¿� ���� a,c,b �� ����
ll a[20001];
ll b[20001];
ll c[20001];

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> c[i] >> b[i];
	}
}

// f(x) : n�� �Է¿� ���� x ������ ���� ����
// n�� �Է¿� ���� ���鼭
// a[i]�� ������, c[i]�� �ִ�, b[i]�� �����̹Ƿ�
// i��° �Է¿����� x ������ ���� ���� = max(0, (min(x,c[i])-a[i])/b[i] + 1)
// ex) i��° �Է� a=2 c=300 b=3, x=120
// 2, 5, 8, ....., 299
// �� �������� 120 ������ ���� ���� : 40�� (2, 5, ..., 119)
// min(120,300) = 120, 120-2=118, 118/3=39, 39+1=40
// �̷��� n�� �Է¿� ���� �� ���� �� f(x)�� Ȧ���� x���Ͽ� �� ����
// ¦���� ���� �� ���� => x ���Ŀ� �� ���� 
// �̺� Ž������ ������ x ���� ����������
// f(x)-f(x-1) �� Ȧ���� x�� ����, ������ f(x)-f(x-1)
// f(x)-f(x-1) �� ¦���� Ȧ������ ���� ����
ll func(ll x)
{
	ll sum = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] > x)
			continue;
		sum += ((min(x, c[i]) - a[i]) / b[i] + 1ll);
	}
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	ll inf = 1ll << 32;
	ll left, right, mid;
	left = 0;
	right = inf;
	mid = (left + right) >> 1;

	// �̺� Ž��
	while (1)
	{
		if (left >= right)
			break;

		ll sum = func(mid);
		if (sum & 1) {
			right = mid;
			mid = (left + right) >> 1;
		}
		else {
			left = mid + 1;
			mid = (left + right) >> 1;
		}
	}

	// x ��ġ ������
	ll answer = func(left) - func(left - 1);

	// left�� �ش� ���� ���̸� ���� ����
	if (left==inf) {
		cout << "NOTHING";
	}
	else {
		cout << left << ' ' << answer;
	}
}