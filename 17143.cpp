#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int R, C, M;
int result;
int king_idx;
int dead_shark_idx; // ���ÿ��� ���� ��� ��ȣ

typedef struct shark {
	int r; int c; int s; int d; int z; int idx;
	// r,c : ��� ��ġ, s : �ӷ�, d : ����, z : ũ��, idx : ��� ��ȣ
	// ���� : 1,2,3,4 - ��, �Ʒ�, ����, ��
	// 0,1,2,3 ���� ������
}shark;

vector<shark> vec; // ����ִ� ����
shark cage[101][101]; // �츮 ���� ����

shark no_shark = { -1,-1,-1,-1,-1,-1 }; // ��� ����

map<pair<int, int>, vector<shark>> Map; // ��� ��ġ�� �� üũ��

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, 1, -1 };

void init()
{
	result = 0;
	king_idx = -1;
	cin >> R >> C >> M;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cage[i][j] = no_shark;
		}
	}

	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		r = r - 1; // index 0����
		c = c - 1;
		d = d - 1;
		shark sh = { r, c, s, d, z, i };
		vec.push_back(sh);
		cage[r][c] = sh;
	}
}

void clear_Map()
{
	Map.clear();
}

void clear_cage()
{
	for (int i = 0; i < vec.size(); i++) {
		int r = vec[i].r;
		int c = vec[i].c;
		cage[r][c] = no_shark;
	}
}

void clear_vec()
{
	vec.clear();
}

// ���ÿ� �̵�
void move_king()
{
	king_idx += 1;
}

// catch_shark���� remove ������ �� �ʿ���
/*
bool operator==(const shark sh1, const shark sh2)
{
	return sh1.c == sh2.c && sh1.d == sh2.d && sh1.idx == sh2.idx && sh1.r == sh2.r && sh1.s == sh2.s && sh1.z == sh2.z;
}
*/

// ��� ���
void catch_shark()
{
	int size = -1;
	for (int i = 0; i < R; i++) {
		if (cage[i][king_idx].z != -1) {
			size = cage[i][king_idx].z;
			dead_shark_idx = cage[i][king_idx].idx;
			cage[i][king_idx] = no_shark;

			break;
		}
	}

	if (size == -1) {
		dead_shark_idx = -1;
		return;
	}
	else {
		result += size;
		return;
	}
}

// ������ üũ
bool isWall(int dir, int r, int c)
{
	if (dir == 0) {
		if (r == 0)
			return true;
		else
			return false;
	}
	else if (dir == 1) {
		if (r == (R - 1))
			return true;
		else
			return false;
	}
	else if (dir == 2) {
		if (c == (C - 1))
			return true;
		else 
			return false;
	}
	else if (dir == 3) {
		if (c == 0)
			return true;
		else
			return false;
	}
}

int dir_change(int dir)
{
	if (dir == 0)
		return 1;
	else if (dir == 1)
		return 0;
	else if (dir == 2)
		return 3;
	else if (dir == 3)
		return 2;
}

// ��� �̵� �� ����
void move_and_eat_shark()
{
	clear_Map();
	clear_cage();

	for (int i = 0; i < vec.size(); i++) {
		shark sh = vec[i];
		int r = sh.r;
		int c = sh.c;
		int speed = sh.s;
		int dir = sh.d;
		int size = sh.z;
		int idx = sh.idx;

		// ���� �༮
		if (idx == dead_shark_idx) 
			continue;

		if (dir == 0 || dir == 1) {
		
			int rot = 2 * (R - 1);
			if (speed >= rot)
				speed %= rot;
			
			for (int j = 0; j < speed; j++) {
				int nr = r + dy[dir];
				int nc = c + dx[dir];
				if (nr < 0) {
					dir = 1;
					nr += 2;
				}
				if (nr >= R) {
					dir = 0;
					nr -= 2;
				}
				c = nc;
				r = nr;
			}
		}

		else {
			int rot = 2 * (C - 1);
			if (speed >= rot)
				speed %= rot;

			for (int j = 0; j < speed; j++) {
				int nr = r + dy[dir];
				int nc = c + dx[dir];
				if (nc < 0) {
					dir = 2;
					nc += 2;
				}
				if (nc >= C) {
					dir = 3;
					nc -= 2;
				}
				
				c = nc;
				r = nr;
			}
		
		}

		pair<int, int> p = { r, c };
		shark tmp = { r,c,speed, dir, size, idx };

		Map[p].push_back(tmp);
	}

	clear_vec();

	for (auto iter = Map.begin(); iter != Map.end(); iter++) {
		if (Map[iter->first].size() >= 2) {
			
			shark max_shark = Map[iter->first][0];

			for (int i = 1; i < Map[iter->first].size(); i++) {
				if (Map[iter->first][i].z > max_shark.z) {
					max_shark = Map[iter->first][i];
				}
			}

			Map[iter->first].clear();
			
			int r = max_shark.r;
			int c = max_shark.c;
			cage[r][c] = max_shark;
			vec.push_back(max_shark);
		}

		else if (Map[iter->first].size() == 1) {
			shark only_shark = Map[iter->first][0];
			Map[iter->first].clear();

			int r = only_shark.r;
			int c = only_shark.c;
			cage[r][c] = only_shark;
			vec.push_back(only_shark);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	while (king_idx < C) {
		
		move_king();
	
		catch_shark();

		move_and_eat_shark();
	}

	cout << result;
}