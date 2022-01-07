#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long n;
int k, q;
long long x, y;

void init()
{
	cin >> n >> k >> q;
}

void get_num()
{
	cin >> x >> y;
}

// num�� �θ�� (num - 2) / k + 1
long long get_parent(long long num)
{
	return (num - 2) / k + 1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	if (k == 1) {
		while (q--) {
			get_num();
			cout << ((x > y) ? (x - y) : (y - x)) << '\n';
		}
	}

	else {
		while (q--) {
			get_num();

			int cnt = 0;

			while (true) {
				// ���� �� ������ ���� (LCA)
				if (x == y)
					break;

				// �� ���� �ִ� �� �������� �θ� ã�� �ö󰡱�
				if (x > y) {
					x = get_parent(x);
				}
				else {
					y = get_parent(y);
				}

				cnt++;
			}

			cout << cnt << '\n';
		}
	}
}