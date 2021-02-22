#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n, m;
bool map[11][11]; // false : �ٴ�, true : ��
vector<vector<pair<int, int>>>land; // �� ���� ��ġ ���
int dist[7][7];
int *parent;

void make_map()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
}

// �� ���ϱ�
void find_land()
{
	int dy[4] = { 0,0,-1,1 };
	int dx[4] = { 1,-1,0,0 };
	bool visited[11][11];
	memset(visited, false, sizeof(visited));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			
			if (map[i][j] && !visited[i][j]) {
				queue<pair<int, int>>q;
				q.push({ i,j });
				vector<pair<int, int>>v;

				while (!q.empty()) {
					int y = q.front().first;
					int x = q.front().second;
					q.pop();

					visited[y][x] = true;
					v.push_back({ y,x });

					for (int k = 0; k < 4; k++) {
						int ny = y + dy[k];
						int nx = x + dx[k];

						if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
							if (map[ny][nx] && !visited[ny][nx]) {
								q.push({ ny,nx });
							}
						}
					}
				}

				land.push_back(v);
				v.clear();
			}
		}
	}
}

// �ּ� ���� Ʈ�� �̿�
// ũ�罺Į �̿�
// ���� �� ������ ������ ������ ����ġ �� �ּڰ��� ���� ��
// ũ�罺Į �˰����� �̿��� �ּҽ���Ʈ���� ���Ѵ�.
// �׷��� �װ��� ������ ����

// p,q ���̿� �ٴٸ� �����ؾ���
bool only_sea(pair<int, int>p, pair<int, int>q)
{
	bool no_land = true;

	if (p.first == q.first) {
		if (p.second > q.second) {
			for (int i = q.second + 1; i < p.second; i++)
				if (map[p.first][i]) {
					no_land = false;
					break;
				}
		}

		else {
			for(int i=p.second+1;i<q.second;i++)
				if (map[p.first][i]) {
					no_land = false;
					break;
				}
		}
	}

	else {
		if (p.first > q.first) {
			for (int i = q.first + 1; i < p.first; i++)
				if (map[i][p.second]) {
					no_land = false;
					break;
				}
		}

		else {
			for (int i = p.first + 1; i < q.first; i++)
				if (map[i][p.second]) {
					no_land = false;
					break;
				}
		}
	}

	return no_land;
}

// �� ��� �� �̵� �ּ� �Ÿ� ���ϱ�
void cal_dist(int from, int to) // from,to:�� ��ȣ
{
	vector<pair<int, int>>v1 = land[from];
	vector<pair<int, int>>v2 = land[to];
	int d = 987654321;

	for (int i = 0; i < v1.size(); i++) {

		for (int j = 0; j < v2.size(); j++) {

			pair<int, int>p1 = v1[i];
			pair<int, int>p2 = v2[j];

			// ���� ���� ������ ��
			if ((p1.first - 1 >= 0) && (p1.first - 1 < n) && !map[p1.first - 1][p1.second]) {
				if ((p1.second == p2.second) && (p2.first + 1 >= 0) && (p2.first + 1 < n) && !map[p2.first + 1][p2.second]) {
					if ((p1.first - p2.first - 1) >= 2 && only_sea(p1, p2)) {
						d = min(d, p1.first - p2.first - 1);
					}
				}
			}

			// �Ʒ��� ���� ������ ��
			if ((p1.first + 1 >= 0) && (p1.first + 1 < n) && !map[p1.first + 1][p1.second]) {
				if ((p1.second == p2.second) && (p2.first - 1 >= 0) && (p2.first - 1 < n) && !map[p2.first - 1][p2.second]) {
					if ((p2.first - p1.first - 1) >= 2 && only_sea(p1, p2)) {
						d = min(d, p2.first - p1.first - 1);
					}
				}
			}

			// �·� ���� ������ ��
			if ((p1.second - 1 >= 0) && (p1.second - 1 < m) && !map[p1.first][p1.second - 1]) {
				if ((p1.first == p2.first) && (p2.second + 1 >= 0) && (p2.second + 1 < m) && !map[p2.first][p2.second + 1]) {
					if ((p1.second - p2.second - 1) >= 2 && only_sea(p1, p2)) {
						d = min(d, p1.second - p2.second - 1);
					}
				}
			}

			// ��� ���� ������ ��
			if ((p1.second + 1 >= 0) && (p1.second + 1 < m) && !map[p1.first][p1.second + 1]) {
				if ((p1.first == p2.first) && (p2.second - 1 >= 0) && (p2.second - 1 < m) && !map[p2.first][p2.second - 1]) {
					if ((p2.second - p1.second - 1) >= 2 && only_sea(p1, p2)) {
						d = min(d, p2.second - p1.second - 1);
					}
				}
			}
		}
	}

	if (d == 987654321) {
		dist[from][to] = 0;
		dist[to][from] = 0;
	}
	else {
		dist[from][to] = d;
		dist[to][from] = d;
	}
}

// ���Ͽ� ���ε忡 �� �Լ���
void init_parent()
{
	int size = land.size();
	parent = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
		parent[i] = i;
}

int find_parent(int node)
{
	if (parent[node] == node)
		return node;
	return find_parent(parent[node]);
}

bool cycle(int node1, int node2)
{
	node1 = find_parent(node1);
	node2 = find_parent(node2);
	if (node1 == node2)
		return true;
	else
		return false;
}

void union_parent(int node1, int node2)
{
	// �θ� ��尡 ���� ���� ����
	node1 = find_parent(node1);
	node2 = find_parent(node2);
	if (node1 < node2)
		parent[node2] = node1;
	else
		parent[node1] = node2;
}

int main()
{
	make_map();
	find_land();

	// ũ�罺Į �˰���
	// vec : �Ÿ�, {from, to}
	int land_size = land.size();
	vector<pair<int, pair<int, int>>>vec; 
	for (int i = 0; i < land_size; i++) {
		for (int j = i + 1; j < land_size; j++) {
			if (dist[i][j] != 0)
				continue;
			cal_dist(i, j);
			if(dist[i][j]!=0)
				vec.push_back({ dist[i][j],{i,j} });
		}
	}

	sort(vec.begin(), vec.end());
	int result = 0;
	int edge = 0;

	// ���Ͽ� ���ε�� ����Ŭ ���� Ȯ��
	init_parent();
	for (int i = 0; i < vec.size(); i++) {
		bool cycle_check = cycle(vec[i].second.first, vec[i].second.second);
		if (!cycle_check) {
			result += vec[i].first;
			union_parent(vec[i].second.first, vec[i].second.second);
			edge++;
		}
	}

	// Ʈ�� ���� Ȯ��
	if (land_size - 1 == edge)
		cout << result;
	else
		cout << -1;
}