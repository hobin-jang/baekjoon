#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

int T;
long long A, B;
bool is_prime[2000001];
int max_num = 2000001;
vector<long long>primes;

void init()
{
	cin >> A >> B;
}

void yes()
{
	cout << "YES";
}

void no()
{
	cout << "NO";
}

void Eratos()
{
	memset(is_prime, true, sizeof(is_prime));

	for (int i = 2; i * i < max_num; i++) {
		if (is_prime[i] == true) {
			for (int j = i * i; j < max_num; j += i)
				is_prime[j] = false;
		}
	}

	for (int i = 2; i < max_num; i++) {
		if (is_prime[i] == true)
			primes.push_back((long long)i);
	}
}

bool check_prime(long long num)
{
	bool check = true;
	for (int i = 0; i < primes.size(); i++) {
		if (num <= primes[i])
			break;

		if (num % primes[i] == 0) {
			check = false;
			break;
		}
	}
	return check;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// ������ ������ ���̶� �����ϰ�
	// ¦���� ���� �׻� �� (2 ����)
	// Ȧ�� = Ȧ�� + ¦��
	// �ᱹ A+B - 2�� �Ҽ��� true �ƴϸ� false
	
	// �з� ��� ���ϱ� Ʋ�ȴ� �׷� (���� ������������ �ռ����ΰ� �׽�Ʈ ���̽��� �ִ� ��)
	// �����佺�׳׽� ü�� ����
	// �ִ� 4���ϱ� 2�鸸������ �����佺�׳׽�ü�� ������

	Eratos();

	cin >> T;
	while (T--) {

		init();

		long long sum = A + B;

		if (sum <= 3) // ������ �� ��
			no();
		else if ((sum & 1) == 0) // 2���� ū ¦��
			yes();
		else {
			// 2���� ū Ȧ��
			// ������ 2 + �Ҽ� ��
			long long num = sum - 2;
			if (check_prime(num))
				yes();
			else
				no();
		}

		if (T != 0)
			cout << '\n';
	}
}