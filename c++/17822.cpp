#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

// ȸ�� ���
// xi, di, ki
// xi ��� �� ������ di �������� kiĭ ȸ��
// di 0 : �ð� ����, 1 : �ݽð� ����
// ���ǿ� ���� ���� ������ �����ϸ鼭 ���� ���� �� ��� ã�´�.
// �׷��� �� ������ ��պ��� ū ���� 1 ����, ���� ���� 1 ���Ѵ�.

// N : ���� ����, M : ���� ���� �ʱ� ���� ����, T : ȸ�� Ƚ��
int N, M, T;
int board[51][51];

// ���ŵ� �� -1�� ó�� (���� �� �� �� ��պ��� ������ +1, ũ�� -1�̰� ���� ���� ��� 1�̻��̹Ƿ� ����� 1���� �۾��� �� ����)
#define NO -1

typedef struct rot{
	int xi, di, ki;
};

rot rotation[51];

// index ���� 1����
void init()
{
	cin >> N >> M >> T;
	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 1;i <= T;i++) {
		int x, d, k;
		cin >> x >> d >> k;
		rotation[i] = { x,d,k };
	}
}

int tmp[51] = { 0 };

void Rotation(rot r) 
{
	int x = r.xi;
	int d = r.di;
	int k = r.ki;

	// �ð� ���� ȸ��
	if (d == 0) {
		for (int i = x;i <= N;i += x) {
			for (int j = 1;j <= M;j++) {
				int idx = (j + k) % M;
				if (idx == 0)
					idx = M;
				tmp[idx] = board[i][j];
			}
			for (int j = 1;j <= M;j++) {
				board[i][j] = tmp[j];
			}
		}
	}

	// �ݽð� ���� ȸ��
	else {
		for (int i = x;i <= N;i += x) {
			for (int j = 1;j <= M;j++) {
				int idx = (j - k);
				if (idx == 0) {
					idx = M;
				}
				else if (idx < 0) {
					idx += M;
				}
				tmp[idx] = board[i][j];
			}
			for (int j = 1;j <= M;j++) {
				board[i][j] = tmp[j];
			}
		}
	}
}

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,1,-1 };
bool visited[51][51];

// bfs�� ���鼭 ������ �� ���� �ֵ� ����
// (start_y, start_x) ��ġ ���� ���� ���� �ֵ� ã��
// return�� ���� : (start_y, start_x) ���� ������ �ֵ�
vector<pair<int,int>> bfs(int start_y, int start_x)
{
	// start_y, start_x ��ġ �� -1�̸� bfs �� ���� ó��

	queue<pair<int, int>>q;
	q.push({ start_y, start_x });
	visited[start_y][start_x] = true;
	
	vector<pair<int, int>>v;
	v.push_back({ start_y, start_x });

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0;i < 4;i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 1 || ny > N)
				continue;

			if (nx == 0) {
				nx = M;
			}
			else if (nx == (M + 1)) {
				nx = 1;
			}

			if (board[ny][nx] == NO)
				continue;

			if (visited[ny][nx])
				continue;

			if (board[ny][nx] == board[y][x]) {
				visited[ny][nx] = true;
				q.push({ ny,nx });
				v.push_back({ ny,nx });
			}
		}
	}

	// ���ϵ� ���� ũ�� 1�̸� ������ �� ���� ��� : ó���ؾߵ�
	return v;
}

bool flag; // ���ŵ� �� �ִ��� ���� �Ǵ� true�� �ִ� ��
vector<pair<int, int>>remove_num; // ������ ����

void removing()
{
	flag = false;

	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			visited[i][j] = false;
		}
	}

	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			if (board[i][j] == NO)
				continue;
			if (visited[i][j] == true)
				continue;

			remove_num = bfs(i, j);

			if (remove_num.size() > 1) {
				flag = true;
				for (int a = 0;a < remove_num.size();a++) {
					pair<int, int>p = remove_num[a];
					board[p.first][p.second] = NO;
				}
			}

			remove_num.clear();
		}
	}

	return;
}

// flag == false �� ���� ����
// ��տ��� +- 1
void plus_minus()
{
	int cnt = 0;
	int sum = 0;

	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			if (board[i][j] != NO) {
				cnt++;
				sum += board[i][j];
			}
		}
	}

	if (cnt == 0)
		return;

	int r = sum % cnt;
	if (r == 0) {
		int ave = sum / cnt;
		for (int i = 1;i <= N;i++) {
			for (int j = 1;j <= M;j++) {
				if (board[i][j] == NO)
					continue;
				if (board[i][j] > ave) {
					board[i][j]--;
				}
				else if (board[i][j] < ave) {
					board[i][j]++;
				}
			}
		}
	}

	else {
		int ave = sum / cnt; // ������ ������ ���� ave = ave + 0.xxx
		for (int i = 1;i <= N;i++) {
			for (int j = 1;j <= M;j++) {
				if (board[i][j] == NO)
					continue;
				if (board[i][j] > ave) {
					board[i][j]--;
				}
				else {
					// ������ �����Ƿ� int�� ��հ� ���� ��쵵 ++
					board[i][j]++;
				}
			}
		}
	}

	return;
}

// ���ǿ� �� �����ִ��� Ȯ��
int isCnt()
{
	int cnt = 0;

	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			if (board[i][j] != NO) {
				cnt++;
				break;
			}
		}
	}
	return cnt;
}

// ���ǿ� ���� �� �� 
int sum_board()
{
	int sum = 0;
	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			if (board[i][j] != NO)
				sum += board[i][j];
		}
	}
	return sum;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int result = 0;
	bool No_number = false;

	init();

	for (int i = 1;i <= T;i++) {
		rot r = rotation[i];
		Rotation(r);

		if (isCnt() == 0) {
			result = 0;
			No_number = true;
			break;
		}

		else {
			removing();
			if (flag == false) {
				plus_minus();
			}
		}
	}

	if (No_number) {
		cout << result;
	}
	else {
		result = sum_board();
		cout << result;
	}
}

