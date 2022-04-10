#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

typedef unsigned int uint;

uint n;
vector<pair<pair<uint, uint>,uint>>ball; // {ũ��, ��}, ��ȣ
uint same_color[200001]; // ���� �� ����
uint bigger_size[2001]; // �� ũ�� �̻� ��
uint result[200001]; // ���
uint sum; // ��ü ����

void init()
{
	cin >> n;
	ball.push_back({ {0,0},0 });
	for (uint i = 1; i <= n; i++) {
		uint c, s;
		cin >> c >> s;
		ball.push_back({ {s,c},i });
	}

	// ũ�� �������� ���� (O(nlogn))
	sort(ball.begin(), ball.end());

	sum = 0;
}

// �� ���� ����
// ��ü ������ - (���� �� ���� �� �� + �� ũ�� �̻��ΰ� �� - ���� �� ���� ũ�� �̻��� �� ��)

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	for (int i = 1; i <= n; i++) {
		uint size = ball[i].first.first;
		uint color = ball[i].first.second;
		uint idx = ball[i].second;

		same_color[color] += size;
		bigger_size[size] += size;
		sum += size;

		result[idx] = sum - (same_color[color] + bigger_size[size] - size);

		// ���� �Ͱ� ��, ũ�� ���� ���
		// ���� ��� ��������
		if (i != 1) {
			if (size == ball[i - 1].first.first) {
				if (color == ball[i - 1].first.second) {
					uint tmp = ball[i - 1].second;
					result[idx] = result[tmp];
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		cout << result[i] << '\n';
	}
}