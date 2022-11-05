#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
// 바이너리 트리 만들면서 체크되는 노드가 몇 개인가를 계산하면됨

int n;
long long result;
map<int,int>m; // 숫자, 뎁스

void init()
{
  cin >> n;
  result = 0;

  // root 만들기
  int num;
  cin >> num;
  m.insert({num, 1});
  result += 1;
}

void calc(int num)
{
  map<int,int>::iterator iter;
  iter = m.upper_bound(num);

  int height = 0;
  
  // num이 가장 큰 경우
  if(iter == m.end()) {
    height = (--iter)->second + 1;
    result += (long long)(height);
  }
  // num이 가장 작은 경우
  else if(iter == m.begin()) {
    height = iter->second + 1;
    result += (long long)(height);
  }
  // 중간인 경우
  else {
    // upper가 가리키는 곳 왼쪽 자식으로 붙을지
    // upper의 왼쪽 자식의 오른쪽 자식으로 붙을지 모름
    // 더 깊은 쪽으로 붙음
    int upperHeight = iter->second;
    iter--;
    int tmpHeight = iter->second;
    height = max(upperHeight, tmpHeight);
    height++;
    result += (long long)(height);
  }

  m.insert({num, height}); // +1된 뎁스 추가
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();

  int num;
  for(int i = 1; i < n; i++) {
    cin >> num;
    calc(num);
  }

  cout << result;
}