#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<string>
using namespace std;

int n, m, k;
string word = "";
int dp[101][101]; // dp[x][y] = x���� a�� y���� z�� ���� �� �ִ� ����� ��
int max_k = 1000000001; // k�� 1,000,000,000 ����

// x���� a, y���� z�� ���� �� �ִ� ���� 
// (x-1���� a, y���� z) + (x���� a, y-1���� z)
// dp[x][y] = dp[x-1][y] + dp[x][y-1]
// a��z�� ������ ����. �̷� ���� �� �ִ� ���ڿ� ����
int possible_num(int num_a, int num_z)
{
	// a�� z �� �ϳ��� ������ ���� 1��
	if (num_a == 0 || num_z == 0)
		return 1;

	if (dp[num_a][num_z] != -1)
		return dp[num_a][num_z];

	int first_case = possible_num(num_a - 1, num_z);
	int second_case = possible_num(num_a, num_z - 1);
	dp[num_a][num_z] = min(first_case + second_case, max_k);

	return dp[num_a][num_z];
}

// ���� �ܾ� �����
// skip : �ǳʶپ�� �� ��
// prev_is_a : �� �տ� a�� ���� �� ����� ��
// skip < prev_is_a : num_a-1���� a�� num_z���� z�� �ٽ� skip��ŭ ����
// �ƴ� ��� : num_a���� a�� num_z-1���� z�� skip - prev_is_a��ŭ ����

void make_word(int num_a, int num_z, int skip)
{
	if (num_a == 0) {
		for (int i = 0; i < num_z; i++)
			word += 'z';
		return;
	}
	if (num_z == 0) {
		for (int i = 0; i < num_a; i++)
			word += 'a';
		return;
	}

	int prev_is_a = possible_num(num_a - 1, num_z);

	if (skip < prev_is_a) {
		word += 'a';
		make_word(num_a - 1, num_z, skip);
	}
	else {
		word += 'z';
		make_word(num_a, num_z - 1, skip - prev_is_a);
	}

	return;
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			dp[i][j] = -1;

	bool possible = true;
	int max_possible = possible_num(n, m);

	// k��° �̹Ƿ� k-1�� ���� �༮�� ���ؾ���
	// k�� ���� �� �ִ� �ִ� ��캸�� ũ�� �� ���ص� ��
	if (k > max_possible) {
		possible = false;
		cout << -1;
	}
	else {
		make_word(n, m, k - 1);
		cout << word;
	}

}