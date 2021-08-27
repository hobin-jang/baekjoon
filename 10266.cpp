#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int n;
string s1;
string s2;

void init()
{
	cin >> n;
	s1.resize(720000);
	s2.resize(360000);

	for (int i = 0; i < 360000; i++) {
		s1[i] = '0';
		s1[i + 360000] = '0';
		s2[i] = '0';
	}

	int num;

	// s1�� 2��� �ؼ� ȯ�� Ž���� ��
	for (int i = 0; i < n; i++) {
		cin >> num;
		s1[num] = '1';
		s1[num + 360000] = '1';
	}

	// s2 �Űܰ��鼭 kmp�� Ž��
	for (int i = 0; i < n; i++) {
		cin >> num;
		s2[num] = '1';
	}
}

// Pi �迭 ����� (prefix, suffix ��ġ�ϴ� ���� ���ϱ�)
vector<int> get_pi(string s) {
	int m = s.size();
	int j = 0;
	vector<int>pi(m, 0);

	for (int i = 1; i < m; i++) {
		while ((j > 0) && (s[i] != s[j])) {
			j = pi[j - 1];
		}

		if (s[i] == s[j]) {
			j++;
			pi[i] = j;
		}
	}

	return pi;
}

// kmp �˰���
bool kmp(string s1, string s2, vector<int>& pi) {
	int n = s1.size(); // Ž�����ϴ� string
	int m = s2.size(); // Ž���� string
	int j = 0;

	for (int i = 0; i < n; i++) {
		while ((j > 0) && (s1[i] != s2[j])) {
			j = pi[j - 1];
		}

		if (s1[i] == s2[j]) {
			if (j == (m - 1)) {
				// ��ġ�ϴ� ���
				return true;
			}
			else {
				// ��ġ �� �ϴ� ���
				j++;
			}
		}
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	vector<int>pi = get_pi(s2);
	bool result = kmp(s1, s2, pi);

	if (result)
		cout << "possible";
	else
		cout << "impossible";
}