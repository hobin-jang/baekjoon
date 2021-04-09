#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int n;
int arr[500001];
int tmp[500001];
long long result = 0;

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		arr[i] = num;
	}
}

// ���� ��Ʈ�� swap ���� 
// = merge ��Ʈ���� merge���������� ������ ����
// �������� ���� ��������
// ���� �迭�� ���� tmp�� ���ĵ� ������ cnt ������
// ������ �迭�� ���� tmp�� ���ĵ� ������ cnt+1
// (������ �迭�� ���� ���ĵȴٴ� ���� �ش� �� ������ ������ �迭 ����
// �̹� ���ĵ� ��Ȳ�̹Ƿ� �������� ���� ������ �迭�� ���� +1 �� �Ͱ� ����)

// �պ�, �������� �Բ� ���ϱ�
void merge(int start, int last)
{
	int mid = (start + last) / 2;
	int i = start;
	int j = mid + 1;
	int k = start;
	int cnt = 0;

	while (i <= mid && j <= last) {
		// ���� �迭�� ���� ���ĵ� ��
		if (arr[i] <= arr[j]) {
			tmp[k++] = arr[i++];
			result += (long long)cnt;
		}
		// ������ �迭�� ���� ���ĵ� ��
		else {
			tmp[k++] = arr[j++];
			cnt++;
		}
	}

	// ���� �κ� �� ������ �迭�� ���� ���ĵ� ��
	if (i > mid) {
		int s = j;
		while (s <= last) {
			tmp[k++] = arr[s++];
			cnt++;
		}
	}
	// ���� �κ� �� ���� �迭�� ���� ���ĵ� ��
	else {
		int s = i;
		while (s <= mid) {
			tmp[k++] = arr[s++];
			result += (long long)cnt;
		}
	}

	for (int t = start; t <= last; t++)
		arr[t] = tmp[t];
}

void mergesort(int start, int last)
{
	if (start < last) {
		int mid = (start + last) / 2;
		mergesort(start, mid);
		mergesort(mid + 1, last);
		merge(start, last);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	mergesort(0, n - 1);
	cout << result;
}

