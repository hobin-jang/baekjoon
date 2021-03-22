#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

// ����� ����ü, ��ġ, ����, ��Ҵ��� ����
struct fish {
	int y;
	int x;
	int dir;
	bool live;
};

int result = 0;
int aqua[4][4]; // ����� ��ȣ ����
fish fishes[17]; // ����� ���� �迭 (1~16)

// ���� ��ġ + 8���� (1~8��)
int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dx[9] = { 0,0,-1,-1,-1,0,1,1,1 };

// ����� �����
void make_aquarium()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			int a, b;
			cin >> a >> b;
			aqua[i][j] = a;
			fishes[a] = { i,j,b,true };
		}
	}
}

// dfs ���� �� ���� ����� ���� ����
void copying(int new_map[][4], int exist_map[][4], fish new_fish[], fish exist_fish[])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			new_map[i][j] = exist_map[i][j];
		}
	}

	for (int i = 1; i <= 16; i++) {
		new_fish[i] = exist_fish[i];
	}
}

// ����� �ڸ� �ٲ�
void swap_fish(int num1, int num2)
{
	fish tmp = fishes[num1];

	fishes[num1].y = fishes[num2].y;
	fishes[num1].x = fishes[num2].x;

	fishes[num2].y = tmp.y;
	fishes[num2].x = tmp.x;
}

// ����� �̵�
void move_fish()
{
	for (int i = 1; i <= 16; i++) {
		if (fishes[i].live == false)
			continue;

		int y = fishes[i].y;
		int x = fishes[i].x;
		int dir = fishes[i].dir;

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		bool flag = false; // ���� ���� �������� �̵� �������� �Ǵ�

		// ���� �������� �̵� ������ ���
		if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {

			// �� ĭ�� ���
			if (aqua[ny][nx] == 0) {
				flag = true;
				fishes[i].y = ny;
				fishes[i].x = nx;
				aqua[ny][nx] = i;
				aqua[y][x] = 0;
			}

			// ��� �ƴ� ���
			else if (aqua[ny][nx] != -1) {
				flag = true;
				swap_fish(i, aqua[ny][nx]);
				swap(aqua[y][x], aqua[ny][nx]);
			}
		}

		// ���� ȸ���ؼ� ã�ƾ��ϴ� ���
		if (flag == false)
		{
			int ndir = dir + 1;
			if (ndir == 9)
				ndir = 1;
			int ny = y + dy[ndir];
			int nx = x + dx[ndir];

			// ���� ��ġ�� �� �� ������
			while (ndir != dir)
			{
				if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {

					// �� ĭ�� ���
					if (aqua[ny][nx] == 0) {
						fishes[i].y = ny;
						fishes[i].x = nx;
						aqua[ny][nx] = i;
						aqua[y][x] = 0;
						fishes[i].dir = ndir;
						break;
					}

					// ��� �ƴ� ���
					else if (aqua[ny][nx] != -1) {
						swap_fish(i, aqua[ny][nx]);
						swap(aqua[y][x], aqua[ny][nx]);
						fishes[i].dir = ndir;
						break;
					}
				}

				ndir++;
				if (ndir == 9)
					ndir = 1;
				ny = y + dy[ndir];
				nx = x + dx[ndir];
			}
		}
	}
}

// ���� ������� ���� �Ǵ� �� ���� �� ����
void make_state(int y, int x, int ny, int nx, int fish_num, bool change)
{
	// �� ����� ���� ���
	if (change == true) {
		aqua[y][x] = 0;
		aqua[ny][nx] = -1;
		fishes[fish_num].live = false;
	}

	// ���� ����
	else {
		aqua[y][x] = -1;
		aqua[ny][nx] = fish_num;
		fishes[fish_num].live = true;
	}
}

// �� (y,x)�� ���� �� dfs ����
void dfs(int y, int x, int dir, int sum)
{
	result = max(result, sum);

	// ���� ���� �����
	int copy_aqua[4][4];
	fish copy_fishes[17];
	copying(copy_aqua, aqua, copy_fishes, fishes);

	move_fish();

	for (int idx = 1; idx <= 3; idx++) {
		int ny = y + dy[dir] * idx;
		int nx = x + dx[dir] * idx;

		if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {
			if (aqua[ny][nx] == 0)
				continue;

			int fish_num = aqua[ny][nx];
			int ndir = fishes[fish_num].dir;

			// �� (ny,nx) ���� ��� dfs ����
			make_state(y, x, ny, nx, fish_num, true);
			dfs(ny, nx, ndir, sum + fish_num);
			// ������ ��� ������� ������
			make_state(y, x, ny, nx, fish_num, false);
		}
		else
			break;
	}

	// ���� ���·� �ǵ�����
	copying(aqua, copy_aqua, fishes, copy_fishes);
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_aquarium();

	// (0,0) ���� �ں��� ���
	int first_fish = aqua[0][0];
	int dir = fishes[first_fish].dir;
	fishes[first_fish].live = false;
	aqua[0][0] = -1;

	// dfs ����
	dfs(0, 0, dir, first_fish);
	cout << result;
}