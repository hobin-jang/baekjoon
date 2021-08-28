#include<iostream>
#include<string>

using namespace std;

#define INF1 987654321
#define INF2 -987654321

int t;
int result;

// result : 0 - palin, 1 - pseudo palin, 2 - nothing, check_cnt : 0�̸� ���� �縰���, 1�̸� �����縰������� üũ ��, 2�̻��� nothing
void check_palindrome(int start_idx, int end_idx, string & s, int check_cnt) {

	if (start_idx >= end_idx) {
		if (check_cnt >= 2) {
			result = 2;
			return;
		}
		else if(check_cnt == 1) {
			result = 1;
			return;
		}
		else if (check_cnt == 0) {
			result = 0;
			return;
		}
	}

	if (s[start_idx] == s[end_idx]) {
		check_palindrome(start_idx + 1, end_idx - 1, s, check_cnt);
	}
	else {
		if (check_cnt == 0) {
			check_palindrome(start_idx + 1, end_idx, s, check_cnt + 1);
			
			// �ٸ� �� ���� ���
			if(result == 2)
				check_palindrome(start_idx, end_idx - 1, s, check_cnt + 1);
		}
		else {
			// �� �̻� ��ȸ ����, ������ ����
			check_palindrome(INF1, INF2, s, check_cnt + 1);
		}
	}

	return;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;

	string s;

	for (int i = 0; i < t; i++) {
		cin >> s;
		int s_size = s.size();

		check_palindrome(0, s_size - 1, s, 0);
		cout << result << '\n';
		s.clear();
	}
}