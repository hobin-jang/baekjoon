#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cstring>

using namespace std;

int n;
map<string, int>m; // {���� ��ȣ : �� ����}
int* output;

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		m[s] = i;
	}

	output = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int idx = m[s];
		output[i] = idx;
	}
}

// �߿� ���
// map�� value(�� ����) �� ���Ͽ� 
// i��° ���� ���� ����(output)�� 
// i+1 ��°~n-1��° ���� ���� ������ �� (i>=0)
// �� ū ��� �ϳ��� ������ i��° ���� �߿��� ��

int overtake()
{
	int result = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (output[i] > output[j]) {
				result++;
				break;
			}
		}
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	cout << overtake();
}