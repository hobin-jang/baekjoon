#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

typedef long long ll;

typedef struct info {
	ll x, y; // ���� ��ġ
	ll p, q; // ���������κ��� ��� ��ġ
}info;

int n;
vector<info>dots;
stack<int>st;

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		dots.push_back({ x, y, (ll)0, (ll)0 });
	}
}

bool compare_yx(const info& dot1, const info& dot2)
{
	// y��ǥ, x��ǥ ���� ������ ����
	if (dot1.y != dot2.y) {
		return dot1.y < dot2.y;
	}
	else {
		return dot1.x < dot2.x;
	}
}

bool compare_counter_clock(const info& dot1, const info& dot2)
{
	// ���������κ��� �ݽð� ���� ����
	if (dot1.p * dot2.q != dot1.q * dot2.p) { 
		// ������ (0,0) ����� �� dot1, dot2 ���͸� ������ �ɷ�
		// �ݽð� ���� �Ǵ�
		// dot1 x dot2 > 0 => dot1, dot2 ��
		// dot1 x dot2 = 0 => ������
		// dot1 x dot2 < 0 => dot2, dot1 ��
		return dot1.p * dot2.q - dot1.q * dot2.p > 0;
	}
	else { 
		// �������� ���
		// y, x��ǥ ���� ������ 
		return compare_yx(dot1, dot2);
	}
}

void sortingDots()
{
	// y��ǥ, x��ǥ ������ �� ����
	sort(dots.begin(), dots.end(), compare_yx);

	// ������ (0�� ��) ���κ��� ��� ��ġ ���
	ll baseX = dots[0].x;
	ll baseY = dots[0].y; 

	for (int i = 1; i < dots.size(); i++) {
		dots[i].p = dots[i].x - baseX;
		dots[i].q = dots[i].y - baseY;
	}

	// ���������κ��� �ݽð���� ����
	vector<info>::iterator iter = dots.begin();
	iter++;
	sort(iter, dots.end(), compare_counter_clock);
}

bool CCW(const info& dot1, const info& dot2, const info& dot3)
{
	// �������� ��ȸ��, ��ȸ�� �Ǵ�
	// dot1, dot2, dot3 ������ input
	// dot1 to dot2 vector v1
	// dot2 to dot3 vector v2
	// v1 x v2 > 0 => ��ȸ��
	// v1 x v2 < 0 => ��ȸ��
	// v1 x v2 = 0 => ����

	// �׶��� ��ĵ �˰��򿡼��� ccw ��ȸ�� �ϴ� ��� ( > 0 )
	// �߰� �����ϹǷ� ccw > 0 �̸� true

	return dot1.x * dot2.y + dot2.x * dot3.y + dot3.x * dot1.y - (dot1.y * dot2.x + dot2.y * dot3.x + dot3.y * dot1.x) > 0;
}

void graham()
{
	int first = 0;
	int second = 1;
	int next = 2;

	st.push(first);
	st.push(second); // ù ��°, �� ��° �� 

	while (next < n) { // �� �� �� �� ����
		while (st.size() >= 2) { // ���� �� ã��
			second = st.top();
			st.pop();
			first = st.top();

			// first, second, next ccw > 0 => second �ٽ� push, break
			// ccw < 0 => ���� �� ã��

			if (CCW(dots[first], dots[second], dots[next]) == true) {
				st.push(second);
				break;
			}
		}

		// ���� �� �ֱ�
		st.push(next);
		next++;
	}

	// ���� ���� ������ ���ÿ� �ִ� ��ȣ ������ �����ϸ� ��
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	sortingDots();

	graham();

	cout << st.size();
}