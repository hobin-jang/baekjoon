#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>

using namespace std;

int n, m, h;
bool check[11][30]; // n��° ���� �� h��° ���� ���������� ����Ǿ����� �Ǵ�
int result = 987654321;

void make_ladder()
{
	cin >> n >> m >> h;
	memset(check, false, sizeof(check));
	while (m--) {
		int a, b;
		cin >> a >> b;
		check[b][a] = true;
	}
}

bool game()
{
	// ���� �� �ڱ� �ڽ� : true
	// �ƴϸ� false

	bool res = false;

	for (int i = 1; i <= n; i++) {
		int line = i;

		for (int j = 1; j <= h; j++) {
			if (check[line][j]) {
				line++;
			}
			else {
				if (check[line - 1][j])
					line--;
				else
					continue;
			}
		}

		if (line != i) {
			res = false;
			return res;
		}
		else
			res = true;
	}

	return res;
}

// ��Ʈ��ŷ
void backtracking(int idx, int cnt)
{
	if (cnt > 3)
		return;

	if (game()) {
		result = min(result, cnt);
		return;
	}

	for (int i = idx; i <= h; i++) {
		for (int j = 1; j < n; j++) {
			// �� �ٿ� ����� �� �Ұ� 
			if (check[j][i])
				continue;
			if (check[j + 1][i])
				continue;
			if (check[j - 1][i])
				continue;

			check[j][i] = true;
			backtracking(i, cnt + 1);
			check[j][i] = false;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_ladder();
	backtracking(1, 0);
	if (result == 987654321)
		cout << -1;
	else
		cout << result;
}
