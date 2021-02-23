#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int n, m;
int map[1001][1001];

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < s.size(); j++) {
			map[i][j] = s[j] - '0';
		}
	}

	// ��ȭ�� : map[i][j] = min(map[i-1][j-1], min(map[i-1][j], map[i][j-1])) + 1
	// ���� �밢�� ���� ���簢���� ���� �� dp�� �̿���
	// ������ �ִ� ũ��(�� �� ����)�� ���Ѵٰ� ���� 
	// map[i][j]=0 �̸� ���簢�� ����� �Ұ�
	int result = 0;
	for (int i = 0; i < n; i++)
		if (map[i][0] != 0)
			result = 1;

	for (int j = 0; j < m; j++)
		if (map[0][j] != 0)
			result = 1;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (map[i][j] != 0 && map[i - 1][j - 1] != 0 && map[i][j - 1] != 0 && map[i - 1][j] != 0) {
				map[i][j] = min(map[i - 1][j - 1], min(map[i - 1][j], map[i][j - 1])) + 1;
				result = max(map[i][j], result);
			}
		}
	}

	cout << result * result;
}