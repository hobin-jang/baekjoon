#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int m;
int Q;
int n, x;
int f[200001];
// 2^18 < 500,000 < 2^19
#define max_log 20
int table[21][200001]; // table[y][x] : x���� ������ 2^y �̵��� ��ġ


// Q<=200,000, n<=500,000 �̹Ƿ�
// log n �� �Ϸ��ؾ���
// �־��� n�� �ִ� 500,000�� log���� k�� �ϸ�
// n & 1<<k, k-- �� �ݺ��ϸ鼭 �ش� ��Ʈ ������ 
// �ش� ��Ʈ�� f������ ������Ʈ
// ex) f_15(x) = f_8( f_4 ( f_2 ( f_1(x) ) ) ) )
// �ռ��Լ� 1���� �̵� 1���̶� ����.

// �⺻ �׷��� + ��ó��
void init()
{
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int num;
		cin >> num;
		f[i] = num;
	}

	// table[0][x] = f(x)
	for (int i = 1; i <= m; i++)
		table[0][i] = f[i];

	// table[y][x] : x���� ������ 2^y �̵��� ��ġ
	// �̴� x���� ������ 2^(y-1) �̵��� ��ġ���� 2^(y-1) �̵��� �Ͱ� ����
	for (int i = 1; i < max_log; i++) {
		for (int j = 1; j <= m; j++) {
			int tmp = table[i - 1][j];
			table[i][j] = table[i - 1][tmp];
		}
	}
}

// 15 = 8+4+2+1 �� �����ϸ�
// 15�� �̵� = 1�� �̵� �� 2�� �̵� �� 4�� �̵� �� 8�� �̵� �� �Ͱ� ����
// �̸� �̿��� ��
int solve(int n, int x)
{
	int cur = x; // ������
	for (int k = 0; k < max_log; k++) {
		if (n & (1 << k)) {
			cur = table[k][cur];
		}
	}
	return cur;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	cin >> Q;
	while (Q--) {
		cin >> n >> x;
		
		int res = solve(n, x);
		cout << res << '\n';
	}
}