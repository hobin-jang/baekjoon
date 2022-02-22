#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> vec[51]; // vec[i] : i�� �θ��� �ڽ� ����

void init()
{
	cin >> n;
	int num;
	for (int i = 0; i < n; i++) {
		cin >> num;
		if (num == -1)
			continue;
		vec[num].push_back(i);
	}
}

int dfs(int node, int parent)
{
	int ret = 0;

	vector<int>result; 
	// �� �ڽ� ��尡 ��Ʈ�� �Ǵ� ����Ʈ���� ��� 

	for (auto child : vec[node]) {
		int child_ret = dfs(child, node);
		result.push_back(child_ret);
	}

	// ��� ū �ֺ��� ���� ���Ľ��Ѿ���
	sort(result.rbegin(), result.rend());

	for (int i = 0; i < result.size(); i++) {
		ret = max(ret, result[i] + i + 1);
	}

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	
	cout << dfs(0, -1);
}