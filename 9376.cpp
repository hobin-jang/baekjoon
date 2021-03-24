#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;

int t, h, w;
char map[102][102]; // ���� �ٱ��� '.'���� �����, �����¿� 2�� �þ
pair<int, int>crime[3]; // ������ ��ġ 
bool visited[3][102][102]; // �湮 ����

// ���, ����1,2 �� �ش� ��ġ���� �� ��
// ���� �� ���� �ּ� ����
int door_count[3][102][102];
int inf = 987654321; // door_count�� inf�� (���� �ִ� 1���� ����)

// �̵�
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

// ����̴� (0,0)�� �ִ� �˼��� ����
// �˼��� �ش� ��ġ���� ���� �� ���� �ּ� ������ 3�� ���� �� ����
// �� ���� �ּڰ��� ���� ���Ѵ�. 
// �ش� ��ġ�� ���� ��� -2 (3�� �� �������Ƿ�)

// �켱���� ť �̿��ؼ� bfs ������ 
// (�׳� ť�� �ص� �������, �ּڰ� ���ϴ� �Ŷ� �켱���� ť�� �ð��� �� ����)
// ���� �ּ� ������ ����� �ϹǷ� {�� ����, {y,x}} �� �� 
// �� ������ ���������ǵ��� �켱���� ť ���� (top�� ���� ���� ��)
// �˼����� �ش� ��ġ �湮 �߰ų� ���̸� pass
// �׷��� �ʴٸ� ���� ���� ������ ������ �ش� ������ ������Ʈ, ť�� �ֱ�

// h,w �Է�, �ʱ�ȭ
void init()
{
	cin >> h >> w;

	for (int i = 0; i <= h + 1; i++) {
		for (int j = 0; j <= w + 1; j++) {
			map[i][j] = '.';
			door_count[0][i][j] = inf;
			door_count[1][i][j] = inf;
			door_count[2][i][j] = inf;
			visited[0][i][j] = false;
			visited[1][i][j] = false;
			visited[2][i][j] = false;
		}
	}

	crime[0] = { -1,-1 };
	crime[1] = { -1,-1 };
	crime[3] = { 0,0 };
}

// ���� �����
void make_map()
{
	// ���� �ٱ� '.'���� ä���
	for (int i = 0; i <= h + 1; i++) {
		map[i][0] = '.';
		map[i][w + 1] = '.';
	}
	for (int i = 0; i <= w + 1; i++) {
		map[0][i] = '.';
		map[h + 1][i] = '.';
	}
	
	// ���� �����
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> map[i][j];
			if (map[i][j] == '$') {
				if (crime[0].first == -1)
					crime[0] = { i,j };
				else
					crime[1] = { i,j };
			}
		}
	}
}

// idx��° ������ door_count ��� (bfs)
void calculate_door(int idx)
{
	// �켱���� ť : {�� ����, {y, x}}, �� ������ ���� �������� (top:���� ����)
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > >pq;
	// �׳� ť, ������ �켱���� ť�� �� ������ �׳� ť�� �ص� ��.
	// queue<pair<int, pair<int, int>>>pq;

	int now_y = crime[idx].first;
	int now_x = crime[idx].second;

	pq.push({ 0,{now_y,now_x} });
	visited[idx][now_y][now_x] = true;
	door_count[idx][now_y][now_x] = 0;

	while (!pq.empty())
	{
		int cnt = pq.top().first;
		int y = pq.top().second.first;
		int x = pq.top().second.second;

		//int cnt = pq.front().first;
		//int y = pq.front().second.first;
		//int x = pq.front().second.second;

		pq.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			// �� �ȿ� ���� ��
			if (ny >= 0 && ny <= (h + 1) && nx >= 0 && nx <= (w + 1)) {
				
				// ���� ���
				if (map[ny][nx] == '*')
					continue;

				// �̹� �湮�� ��쵵 �� ���� ��� ����

				// ������ ���
				int next_cnt = cnt;
				// ���� ĭ�� ���� ��� ���� ��+1
				if (map[ny][nx] == '#')
					next_cnt++;

				// ���� ĭ�� �� �������� �� ���� ����
				// ���� ���� ������Ʈ, ť�� �ֱ�
				if (door_count[idx][ny][nx] > next_cnt) {
					door_count[idx][ny][nx] = next_cnt;
					visited[idx][ny][nx] = true;
					pq.push({ next_cnt,{ny,nx} });
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;
	while (t--)
	{
		init();
		make_map();

		for (int idx = 0; idx < 3; idx++)
			calculate_door(idx);

		// �ּڰ� ���ϱ�
		// ��� ��ġ���� �˼����� �� ������ �� ����
		// �� �� �ּ��� ���� �� (��� �ش� ��ġ�� �� �� �����Ƿ� ���� ���)
		// �ش� ��ġ�� ���� ��� -2 (3�� ��� ���� �����̹Ƿ�)
		int result = inf;

		for (int i = 0; i <= h + 1; i++) {
			for (int j = 0; j <= w + 1; j++) {
				// ���̸� ��� ���ص� ��
				if (map[i][j] == '*')
					continue;

				// �ش� ��ġ�� �� ���̶� �� ���� �� ��
				if (visited[0][i][j] == false || visited[1][i][j] == false || visited[2][i][j] == false)
					continue;

				int sum = 0;
				for (int k = 0; k < 3; k++)
					sum += door_count[k][i][j];

				// ������ ���� ���
				if (map[i][j] == '#')
					sum -= 2;

				result = min(result, sum);
			}
		}

		cout << result << '\n';
	}
}