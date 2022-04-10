#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

// ť��
// U�� - w���, D�Ʒ� - y���, F�� - r����,  
// B�� - o������, L�� - g�ʷ�, R���� - b�Ķ�
// + �ð�, - �ݽð�

int t, n;
vector<pair<char, char>>v;
char cube[6][3][3]; 
char tmp[6][3][3];
// cube : 6 - ��,�Ʒ�,��,��,��,��, 3*3 - ���� ��(0,0), ������ �Ʒ� (2,2)

void init()
{
	cin >> n;
	v.clear();
	// ȸ�� �Է�
	for (int i = 0; i < n; i++) {
		string s = "";
		cin >> s;
		v.push_back({ s[0],s[1] });
	}
}

void cube_reset()
{
	// ť�� �ʱ�ȭ
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cube[0][i][j] = 'w';
			cube[1][i][j] = 'y';
			cube[2][i][j] = 'r';
			cube[3][i][j] = 'o';
			cube[4][i][j] = 'g';
			cube[5][i][j] = 'b';
		}
	}
}

void tmp_clear()
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				tmp[i][j][k] = '.';
}

void rotate(char side, char dir)
{
	switch (side) {
	case 'U':
		if (dir == '+') {
			// ����
			tmp[0][0][0] = cube[0][2][0];
			tmp[0][0][1] = cube[0][1][0];
			tmp[0][0][2] = cube[0][0][0];
			tmp[0][1][0] = cube[0][2][1];
			tmp[0][1][1] = cube[0][1][1];
			tmp[0][1][2] = cube[0][0][1];
			tmp[0][2][0] = cube[0][2][2];
			tmp[0][2][1] = cube[0][1][2];
			tmp[0][2][2] = cube[0][0][2];
			// ����
			tmp[2][0][0] = cube[5][2][0];
			tmp[2][0][1] = cube[5][1][0];
			tmp[2][0][2] = cube[5][0][0];
			
			tmp[3][2][0] = cube[4][2][2];
			tmp[3][2][1] = cube[4][1][2];
			tmp[3][2][2] = cube[4][0][2];

			tmp[4][0][2] = cube[2][0][0];
			tmp[4][1][2] = cube[2][0][1];
			tmp[4][2][2] = cube[2][0][2];

			tmp[5][0][0] = cube[3][2][0];
			tmp[5][1][0] = cube[3][2][1];
			tmp[5][2][0] = cube[3][2][2];
			break;
		}
		else {
			// ����
			tmp[0][0][0] = cube[0][0][2];
			tmp[0][0][1] = cube[0][1][2];
			tmp[0][0][2] = cube[0][2][2];
			tmp[0][1][0] = cube[0][0][1];
			tmp[0][1][1] = cube[0][1][1];
			tmp[0][1][2] = cube[0][2][1];
			tmp[0][2][0] = cube[0][0][0];
			tmp[0][2][1] = cube[0][1][0];
			tmp[0][2][2] = cube[0][2][0];
			//����
			tmp[2][0][0] = cube[4][0][2];
			tmp[2][0][1] = cube[4][1][2];
			tmp[2][0][2] = cube[4][2][2];

			tmp[3][2][0] = cube[5][0][0];
			tmp[3][2][1] = cube[5][1][0];
			tmp[3][2][2] = cube[5][2][0];

			tmp[4][0][2] = cube[3][2][2];
			tmp[4][1][2] = cube[3][2][1];
			tmp[4][2][2] = cube[3][2][0];

			tmp[5][0][0] = cube[2][0][2];
			tmp[5][1][0] = cube[2][0][1];
			tmp[5][2][0] = cube[2][0][0];
			break;
		}
	case 'D':
		if (dir == '+') {
			// �ظ�
			tmp[1][0][0] = cube[1][2][0];
			tmp[1][0][1] = cube[1][1][0];
			tmp[1][0][2] = cube[1][0][0];
			tmp[1][1][0] = cube[1][2][1];
			tmp[1][1][1] = cube[1][1][1];
			tmp[1][1][2] = cube[1][0][1];
			tmp[1][2][0] = cube[1][2][2];
			tmp[1][2][1] = cube[1][1][2];
			tmp[1][2][2] = cube[1][0][2];
			// ����
			tmp[2][2][0] = cube[4][0][0];
			tmp[2][2][1] = cube[4][1][0];
			tmp[2][2][2] = cube[4][2][0];

			tmp[3][0][0] = cube[5][0][2];
			tmp[3][0][1] = cube[5][1][2];
			tmp[3][0][2] = cube[5][2][2];

			tmp[4][0][0] = cube[3][0][2];
			tmp[4][1][0] = cube[3][0][1];
			tmp[4][2][0] = cube[3][0][0];

			tmp[5][0][2] = cube[2][2][2];
			tmp[5][1][2] = cube[2][2][1];
			tmp[5][2][2] = cube[2][2][0];
			break;
		}
		else {
			// ����
			tmp[1][0][0] = cube[1][0][2];
			tmp[1][0][1] = cube[1][1][2];
			tmp[1][0][2] = cube[1][2][2];
			tmp[1][1][0] = cube[1][0][1];
			tmp[1][1][1] = cube[1][1][1];
			tmp[1][1][2] = cube[1][2][1];
			tmp[1][2][0] = cube[1][0][0];
			tmp[1][2][1] = cube[1][1][0];
			tmp[1][2][2] = cube[1][2][0];
			//����
			tmp[2][2][0] = cube[5][2][2];
			tmp[2][2][1] = cube[5][1][2];
			tmp[2][2][2] = cube[5][0][2];

			tmp[3][0][0] = cube[4][2][0];
			tmp[3][0][1] = cube[4][1][0];
			tmp[3][0][2] = cube[4][0][0];

			tmp[4][0][0] = cube[2][2][0];
			tmp[4][1][0] = cube[2][2][1];
			tmp[4][2][0] = cube[2][2][2];

			tmp[5][0][2] = cube[3][0][0];
			tmp[5][1][2] = cube[3][0][1];
			tmp[5][2][2] = cube[3][0][2];
			break;
		}
	case 'F':
		if (dir == '+') {
			// ����
			tmp[2][0][0] = cube[2][2][0];
			tmp[2][0][1] = cube[2][1][0];
			tmp[2][0][2] = cube[2][0][0];
			tmp[2][1][0] = cube[2][2][1];
			tmp[2][1][1] = cube[2][1][1];
			tmp[2][1][2] = cube[2][0][1];
			tmp[2][2][0] = cube[2][2][2];
			tmp[2][2][1] = cube[2][1][2];
			tmp[2][2][2] = cube[2][0][2];
			// ����
			tmp[0][2][0] = cube[4][2][0];
			tmp[0][2][1] = cube[4][2][1];
			tmp[0][2][2] = cube[4][2][2];

			tmp[1][2][0] = cube[5][2][0];
			tmp[1][2][1] = cube[5][2][1];
			tmp[1][2][2] = cube[5][2][2];

			tmp[4][2][0] = cube[1][2][0];
			tmp[4][2][1] = cube[1][2][1];
			tmp[4][2][2] = cube[1][2][2];

			tmp[5][2][0] = cube[0][2][0];
			tmp[5][2][1] = cube[0][2][1];
			tmp[5][2][2] = cube[0][2][2];
			break;
		}
		else {
			// ����
			tmp[2][0][0] = cube[2][0][2];
			tmp[2][0][1] = cube[2][1][2];
			tmp[2][0][2] = cube[2][2][2];
			tmp[2][1][0] = cube[2][0][1];
			tmp[2][1][1] = cube[2][1][1];
			tmp[2][1][2] = cube[2][2][1];
			tmp[2][2][0] = cube[2][0][0];
			tmp[2][2][1] = cube[2][1][0];
			tmp[2][2][2] = cube[2][2][0];
			//����
			tmp[0][2][0] = cube[5][2][0];
			tmp[0][2][1] = cube[5][2][1];
			tmp[0][2][2] = cube[5][2][2];

			tmp[1][2][0] = cube[4][2][0];
			tmp[1][2][1] = cube[4][2][1];
			tmp[1][2][2] = cube[4][2][2];

			tmp[4][2][0] = cube[0][2][0];
			tmp[4][2][1] = cube[0][2][1];
			tmp[4][2][2] = cube[0][2][2];

			tmp[5][2][0] = cube[1][2][0];
			tmp[5][2][1] = cube[1][2][1];
			tmp[5][2][2] = cube[1][2][2];
			break;
		}
	case 'B':
		if (dir == '+') {
			// ����
			tmp[3][0][0] = cube[3][2][0];
			tmp[3][0][1] = cube[3][1][0];
			tmp[3][0][2] = cube[3][0][0];
			tmp[3][1][0] = cube[3][2][1];
			tmp[3][1][1] = cube[3][1][1];
			tmp[3][1][2] = cube[3][0][1];
			tmp[3][2][0] = cube[3][2][2];
			tmp[3][2][1] = cube[3][1][2];
			tmp[3][2][2] = cube[3][0][2];
			// ����
			tmp[0][0][0] = cube[5][0][0];
			tmp[0][0][1] = cube[5][0][1];
			tmp[0][0][2] = cube[5][0][2];

			tmp[1][0][0] = cube[4][0][0];
			tmp[1][0][1] = cube[4][0][1];
			tmp[1][0][2] = cube[4][0][2];

			tmp[4][0][0] = cube[0][0][0];
			tmp[4][0][1] = cube[0][0][1];
			tmp[4][0][2] = cube[0][0][2];

			tmp[5][0][0] = cube[1][0][0];
			tmp[5][0][1] = cube[1][0][1];
			tmp[5][0][2] = cube[1][0][2];
			break;
		}
		else {
			// ����
			tmp[3][0][0] = cube[3][0][2];
			tmp[3][0][1] = cube[3][1][2];
			tmp[3][0][2] = cube[3][2][2];
			tmp[3][1][0] = cube[3][0][1];
			tmp[3][1][1] = cube[3][1][1];
			tmp[3][1][2] = cube[3][2][1];
			tmp[3][2][0] = cube[3][0][0];
			tmp[3][2][1] = cube[3][1][0];
			tmp[3][2][2] = cube[3][2][0];
			//����
			tmp[0][0][0] = cube[4][0][0];
			tmp[0][0][1] = cube[4][0][1];
			tmp[0][0][2] = cube[4][0][2];

			tmp[1][0][0] = cube[5][0][0];
			tmp[1][0][1] = cube[5][0][1];
			tmp[1][0][2] = cube[5][0][2];

			tmp[4][0][0] = cube[1][0][0];
			tmp[4][0][1] = cube[1][0][1];
			tmp[4][0][2] = cube[1][0][2];

			tmp[5][0][0] = cube[0][0][0];
			tmp[5][0][1] = cube[0][0][1];
			tmp[5][0][2] = cube[0][0][2];
			break;
		}
	case'L':
		if (dir == '+') {
			// ����
			tmp[4][0][0] = cube[4][2][0];
			tmp[4][0][1] = cube[4][1][0];
			tmp[4][0][2] = cube[4][0][0];
			tmp[4][1][0] = cube[4][2][1];
			tmp[4][1][1] = cube[4][1][1];
			tmp[4][1][2] = cube[4][0][1];
			tmp[4][2][0] = cube[4][2][2];
			tmp[4][2][1] = cube[4][1][2];
			tmp[4][2][2] = cube[4][0][2];
			// ����
			tmp[0][0][0] = cube[3][0][0];
			tmp[0][1][0] = cube[3][1][0];
			tmp[0][2][0] = cube[3][2][0];

			tmp[1][0][2] = cube[2][2][0];
			tmp[1][1][2] = cube[2][1][0];
			tmp[1][2][2] = cube[2][0][0];

			tmp[2][0][0] = cube[0][0][0];
			tmp[2][1][0] = cube[0][1][0];
			tmp[2][2][0] = cube[0][2][0];

			tmp[3][0][0] = cube[1][2][2];
			tmp[3][1][0] = cube[1][1][2];
			tmp[3][2][0] = cube[1][0][2];
			break;
		}
		else {
			// ����
			tmp[4][0][0] = cube[4][0][2];
			tmp[4][0][1] = cube[4][1][2];
			tmp[4][0][2] = cube[4][2][2];
			tmp[4][1][0] = cube[4][0][1];
			tmp[4][1][1] = cube[4][1][1];
			tmp[4][1][2] = cube[4][2][1];
			tmp[4][2][0] = cube[4][0][0];
			tmp[4][2][1] = cube[4][1][0];
			tmp[4][2][2] = cube[4][2][0];
			//����
			tmp[0][0][0] = cube[2][0][0];
			tmp[0][1][0] = cube[2][1][0];
			tmp[0][2][0] = cube[2][2][0];

			tmp[1][0][2] = cube[3][2][0];
			tmp[1][1][2] = cube[3][1][0];
			tmp[1][2][2] = cube[3][0][0];

			tmp[2][0][0] = cube[1][2][2];
			tmp[2][1][0] = cube[1][1][2];
			tmp[2][2][0] = cube[1][0][2];

			tmp[3][0][0] = cube[0][0][0];
			tmp[3][1][0] = cube[0][1][0];
			tmp[3][2][0] = cube[0][2][0];
			break;
		}
	case'R':
		if (dir == '+') {
			// ����
			tmp[5][0][0] = cube[5][2][0];
			tmp[5][0][1] = cube[5][1][0];
			tmp[5][0][2] = cube[5][0][0];
			tmp[5][1][0] = cube[5][2][1];
			tmp[5][1][1] = cube[5][1][1];
			tmp[5][1][2] = cube[5][0][1];
			tmp[5][2][0] = cube[5][2][2];
			tmp[5][2][1] = cube[5][1][2];
			tmp[5][2][2] = cube[5][0][2];
			// ����
			tmp[0][0][2] = cube[2][0][2];
			tmp[0][1][2] = cube[2][1][2];
			tmp[0][2][2] = cube[2][2][2];

			tmp[1][0][0] = cube[3][2][2];
			tmp[1][1][0] = cube[3][1][2];
			tmp[1][2][0] = cube[3][0][2];

			tmp[2][0][2] = cube[1][2][0];
			tmp[2][1][2] = cube[1][1][0];
			tmp[2][2][2] = cube[1][0][0];

			tmp[3][0][2] = cube[0][0][2];
			tmp[3][1][2] = cube[0][1][2];
			tmp[3][2][2] = cube[0][2][2];
			break;
		}
		else {
			// ����
			tmp[5][0][0] = cube[5][0][2];
			tmp[5][0][1] = cube[5][1][2];
			tmp[5][0][2] = cube[5][2][2];
			tmp[5][1][0] = cube[5][0][1];
			tmp[5][1][1] = cube[5][1][1];
			tmp[5][1][2] = cube[5][2][1];
			tmp[5][2][0] = cube[5][0][0];
			tmp[5][2][1] = cube[5][1][0];
			tmp[5][2][2] = cube[5][2][0];
			//����
			tmp[0][0][2] = cube[3][0][2];
			tmp[0][1][2] = cube[3][1][2];
			tmp[0][2][2] = cube[3][2][2];

			tmp[1][0][0] = cube[2][2][2];
			tmp[1][1][0] = cube[2][1][2];
			tmp[1][2][0] = cube[2][0][2];

			tmp[2][0][2] = cube[0][0][2];
			tmp[2][1][2] = cube[0][1][2];
			tmp[2][2][2] = cube[0][2][2];

			tmp[3][0][2] = cube[1][2][0];
			tmp[3][1][2] = cube[1][1][0];
			tmp[3][2][2] = cube[1][0][0];
			break;
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (tmp[i][j][k] != '.') {
					cube[i][j][k] = tmp[i][j][k];
				}
			}
		}
	}
}

void print_upside()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << cube[0][i][j];
		}
		cout << '\n';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;
	while (t--) {
		init();
		cube_reset();
		tmp_clear();

		for (int i = 0; i < v.size(); i++) {
			char side = v[i].first;
			char dir = v[i].second;
			rotate(side, dir);
			tmp_clear();
		}

		print_upside();
	}
}
