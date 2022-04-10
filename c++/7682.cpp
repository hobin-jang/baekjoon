#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<string>

using namespace std;

// X�� �̱� ���̸� 1
// O�� �̱� ���̸� -1
// ������ �̱��� ���ϸ� 0
// X�� 2�� �̱�� ��� 2
// �� �� �̱�ų� O�� 2�� �̻� �̱�� ��� -2
int is_success(char map[3][3])
{
	int x = 0;
	int o = 0;
	// �� �� ���� �̰���� �Ǵ�

	if (map[0][0] == map[0][1] && map[0][1] == map[0][2]) {
		if (map[0][0] == 'X')
			x++;
		if (map[0][0] == 'O')
			o--;
	}

	if (map[1][0] == map[1][1] && map[1][1] == map[1][2]) {
		if (map[1][0] == 'X')
			x++;
		if (map[1][0] == 'O')
			o--;
	}

	if (map[2][0] == map[2][1] && map[2][1] == map[2][2]) {
		if (map[2][0] == 'X')
			x++;
		if (map[2][0] == 'O')
			o--;
	}

	if (map[0][0] == map[1][0] && map[1][0] == map[2][0]) {
		if (map[0][0] == 'X')
			x++;
		if (map[0][0] == 'O')
			o--;
	}

	if (map[0][1] == map[1][1] && map[1][1] == map[2][1]) {
		if (map[0][1] == 'X')
			x++;
		if (map[0][1] == 'O')
			o--;
	}

	if (map[0][2] == map[1][2] && map[1][2] == map[2][2]) {
		if (map[0][2] == 'X')
			x++;
		if (map[0][2] == 'O')
			o--;
	}

	if (map[0][0] == map[1][1] && map[1][1] == map[2][2]) {
		if (map[0][0] == 'X')
			x++;
		if (map[0][0] == 'O')
			o--;
	}

	if (map[0][2] == map[1][1] && map[1][1] == map[2][0]) {
		if (map[0][2] == 'X')
			x++;
		if (map[0][2] == 'O')
			o--;
	}

	// ������ �̱��� ���� ���
	if (x == 0 && o == 0)
		return 0;
	else {
		// X�� �̰��� ��
		if (x == 1 && o == 0)
			return 1;
		// O�� �̰��� ��
		else if (x == 0 && o == -1)
			return -1;
		// X�� 2�� �̰��� ��
		else if (x == 2 && o == 0)
			return 2;
		// ������ �� �Ǵ� ���
		else
			return -2;
	}
}

// ������ ������� �Ǵ�
bool check(string s)
{
	int cntx = 0;
	int cnto = 0;
	int cntd = 0;
	// X, O, dot ����
	
	char map[3][3];
	for (int i = 0; i < s.size(); i++) {
		map[i / 3][i % 3] = s[i];
		if (s[i] == 'X')
			cntx++;
		if (s[i] == 'O')
			cnto++;
		if (s[i] == '.')
			cntd++;
	}

	// �� �� ���� ���
	if (cntx < cnto)
		return false;
	
	int success = is_success(map);

	// ������ �̱��� ���� ���
	if (success == 0) {
		if (cntd > 0)
			return false;
		else {
			if (cntx == 5 && cnto == 4)
				return true;
			else
				return false;
		}
	}
	else {
		if (success == 1) {
			if (cntx == cnto + 1)
				return true;
			else
				return false;
		}
		if (success == -1) {
			if (cntx == cnto)
				return true;
			else
				return false;
		}
		if (success == 2) {
			if (cntx == 5 && cnto == 4)
				return true;
			else
				return false;
		}
		if (success == -2) {
			return false;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (1)
	{
		string s;
		cin >> s;
		if (s == "end")
			break;

		if (check(s))
			cout << "valid" << '\n';
		else
			cout << "invalid" << '\n';
	}
}
