#include<iostream>
#include<vector>
#include<string>
#include<bitset>
#include<algorithm>

using namespace std;

int n, k;
vector<string>words; // �ܾ�� ����
bool learn[26]; // ���ĺ� ������ ������� ����
int result = 0;

void init()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		words.push_back(s);
	}

	// a, t, i, n, c�� ������ �������
	learn[0] = true;
	learn['t' - 'a'] = true;
	learn['i' - 'a'] = true;
	learn['n' - 'a'] = true;
	learn['c' - 'a'] = true;
}

// idx : ���ĺ� ��ġ, cnt : ��� ���ĺ� ����
void dfs(int idx, int cnt)
{
	// k���� ���ڸ� �� ��� ���
	if (cnt == k) {
		int res = 0;
		for (int i = 0; i < n; i++) {
			string s = words[i];
			bool check = true;

			// ó�� 4����, ������ 4���ڴ� ����
			for (int j = 4; j < s.size() - 4; j++) {
				int num = s[j] - 'a';

				// �� ��� ���� �����ϴ� ���
				if (learn[num] == false) {
					check = false;
					break;
				}
			}

			if (check == true)
				res++;
		}
		result = max(result, res);
	}

	// ���� �� �� ��� ���
	else {
		for (int i = idx; i < 26; i++) {
			if (learn[i] == false) {
				learn[i] = true;
				dfs(i, cnt + 1);
				learn[i] = false;
			}
		}
	}

	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	// a,n,t,i,c�� ������ ���
	if (k < 5) {
		cout << 0;
		return 0;
	}
	
	// a,n,t,i,c �� ������ k-5�� �н� ����
	k -= 5;
	dfs(0, 0);
	cout << result;
}