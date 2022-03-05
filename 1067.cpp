#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <string>

using namespace std;

typedef complex<double> cpx;

const double PI = acos(-1);

void FFT(vector<cpx>& f, cpx w)
{
	// f(x) = a_(n-1) x^(n-1) + ... + a_0 = f_even(x^2) + x*f_odd(x^2)
	// f_even = a_(n-2) x^(n/2-1) + ... + a_2 x + a_0
	// f_odd = a_(n-1) x^(n/2-1) + ... + a_3 x + a_1
	// f(w) = f_even(w^2) + w f_odd(w^2)
	// f(-w) = f_even(w^2) - w f_odd(w^2)

	int n = f.size();

	// base case (�����)
	if (n == 1)
		return;

	// ���׽� even, odd �и�
	vector<cpx> even(n / 2);
	vector<cpx> odd(n / 2);

	for (int i = 0; i < n; i++) {
		if (i % 2 == 0)
			even[i / 2] = f[i];
		else
			odd[i / 2] = f[i];
	}

	// ���� DFT ���� (divide)
	FFT(even, w * w);
	FFT(odd, w * w);

	// conquer
	cpx wp(1, 0); // wp = 1 + 0*i

	for (int i = 0; i < n / 2; i++) {
		// f(w) = f_even(w^2) + w f_odd(w^2)
		f[i] = even[i] + wp * odd[i];

		// f(-w) = f_even(w^2) - w f_odd(w^2)
		f[i + n / 2] = even[i] - wp * odd[i];

		wp *= w;
	}
}

// �� ���׽� �� ����
// i ��° ���Ҵ� x^i ���
vector<cpx> multiply(vector<cpx> a, vector<cpx> b)
{
	int n = 1;
	// ���׽� ���̺��� ū �ּ� 2�� �ŵ������� n����
	while ((n < a.size() + 1) || (n < b.size() + 1))
		n *= 2;
	n *= 2;

	a.resize(n);
	b.resize(n);

	vector<cpx> c(n); // c = a * b

	cpx w(cos((2 * PI) / n), sin((2 * PI) / n)); // base (root of unity)

	// FFT�� ���׽� DFT ����
	FFT(a, w);
	FFT(b, w);

	// DFT ��� ���ϸ� c�� DFT ��
	for (int i = 0; i < n; i++) {
		c[i] = a[i] * b[i];
	}

	// IDFT�� (����ȯ) c�� ���׽� ���� ����
	FFT(c, cpx(1, 0) / w);

	for (int i = 0; i < n; i++) {
		c[i] /= cpx(n, 0);

		// ���׽� ����� ������ �� ����, �Ǽ��� ���Ҽ��� �״�� �θ� ��
		c[i] = cpx(round(c[i].real()), round(c[i].imag()));
	}

	return c;
}

vector<cpx> getCpxVector(vector<int>& v)
{
	vector<cpx> f(v.size());
	for (int i = 0; i < v.size(); i++) {
		f[i] = cpx(v[i], 0);
	}
	return f;
}

int getSum(vector<cpx>& f)
{
	int ret = 0;
	for (const auto c : f) {
		ret += (int)c.real();
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int n;
	cin >> n;
	vector<int>vec1(2 * n);
	vector<int>vec2(n);
	
	for (int i = 0; i < n; i++) {
		cin >> vec1[i];
		vec1[i + n] = vec1[i];
	}
	for (int i = n - 1; i >= 0; i--) {
		cin >> vec2[i];
	}

	int res = 0; // ���� �ִ� 6��
	
	vector<cpx> cpxVec1 = getCpxVector(vec1);
	vector<cpx> cpxVec2 = getCpxVector(vec2);
	vector<cpx> cpxVec3 = multiply(cpxVec1, cpxVec2);
	
	for (auto c : cpxVec3) {
		res = max(res, (int)c.real());
	}

	cout << res;
}