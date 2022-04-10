#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

ll N, K, M;

ll dp[2000][2000];
// combination �� �����
// m �ִ밪 2000 �̹Ƿ� 2000 ������ �ص� ����� 0 ~ 1999
///////////////////////////////
// Lucas Theorem
// nCr % p = Pi(i = 0 to k) (n_i, k_i) (mod p)
// where n = n_k * p^k + n_(k-1) * p^(k-1) + ... + n_0 
// r = r_k * p^k + r_(k-1) * r^(k-1) + ... + r_0
// if n_i < k_i => combination (n_i, k_i) = 0

void init()
{
	// m�� �Ҽ�
	// Lucas theorem �̿�
	cin >> N >> K >> M;

	fill(&dp[0][0], &dp[1999][2000], -1);
}

// nCr % m ���ϱ�
ll combination(ll n, ll r, ll m)
{
	if (dp[n][r] != -1) {
		return dp[n][r];
	}

	if (n < r) {
		dp[n][r] = 0;
	}
	else if (n == r || r == 0) {
		dp[n][r] = 1;
	}
	else {
		dp[n][r] = combination(n - 1, r - 1, m) + combination(n - 1, r, m);
		dp[n][r] %= m;
	}

	return dp[n][r];
}

// m���� ���ϱ�
vector<ll> m_notation(ll num, ll m)
{
	vector<ll> vec;

	ll r; // ������
	while (num > 0) {
		r = num % m;
		num = num / m;
		vec.push_back(r);
	}

	return vec;
}

// nCk % m ���ϱ� (m�� �Ҽ�)
ll Lucas(ll n, ll k, ll m)
{
	vector<ll> vec_n = m_notation(n, m);
	vector<ll> vec_k = m_notation(k, m);

	int min_size = min(vec_n.size(), vec_k.size());
	// n�� m���� ��� ���� �� ���� ��� (n_i, k_i) = (n_i, 0) = 1 �̹Ƿ� ���ϸ� ��� ����

	ll result = 1;

	for (int i = 0; i < min_size; i++) {
		ll n_i = vec_n[i];
		ll k_i = vec_k[i];

		result *= (combination(n_i, k_i, m) % m);

		// �� �̻� �� ���ص� ��
		if (result == 0)
			break;
	}

	return result % m;
}


int main()
{
	init();

	cout << Lucas(N, K, M);
}