#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

string S, T;

void init()
{
	cin >> S >> T;
}
// T�� �������� �������� A�� A ���ְ�
// B�� ���ְ� ������ �ݺ�
// S ������ 1, �ƴϸ� 0

int calculate(string str) {
	int len = str.size();
	if (str == S)
		return 1;
	else if (len == S.size() && str != S)
		return 0;
	else {
		if (str[len - 1] == 'A')
			return calculate(str.substr(0, len - 1));
		else {
			string substr = str.substr(0, len - 1);
			string reversestr(substr.rbegin(), substr.rend());
			return calculate(reversestr);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	init();
	cout << calculate(T);
}