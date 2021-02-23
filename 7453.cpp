#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// A,B �� C,D �� ���� ����Ѵ�.
// C,D�� �ո� ������������ �����Ѵ�.
// lower_bound, upper_bound �Լ��� �̿��� -num �� ����� index�� ã�´�.
// lower_bound : key�� ���� �� ������ ���� ���� index�� ���Ѵ�.
// ������ key���� ū �� �� ���� ���� ������ index�� ���Ѵ�.
// upper_bound : key���� ū ���� �� ���� ���� ������ index�� ���Ѵ�.
// key (���⼭�� -num) �� ���� �� ������ �� ���� �����ϹǷ� upper - lower�� ���Ѵ�.

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	long long arr[4000][4];
	long long result = 0;
	vector<long long>cd;

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cd.push_back(arr[i][2] + arr[j][3]);
		}
	}

	sort(cd.begin(), cd.end());

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			long long num = arr[i][0] + arr[j][1];
			long long lower = lower_bound(cd.begin(), cd.end(), (-1) * num) - cd.begin();
			long long upper = upper_bound(cd.begin(), cd.end(), (-1) * num) - cd.begin();

			if ((-1) * num == cd[lower])
				result += (upper - lower);
		}
	}

	cout << result;
}