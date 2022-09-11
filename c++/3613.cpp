#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string s;
string ans;

vector<int>cpp; // _ ��ġ ����
vector<int>java; // �빮�� ��ġ ���� 

void init()
{
    cin >> s;
}

bool errorCheck()
{
    // ù ���� �빮��
    if (s[0] >= 'A' && s[0] <= 'Z')
        return true;
    // ù ���� _ �̰ų� ������ _ 
    if (s[0] == '_' || s[s.size() - 1] == '_')
        return true;

    // _ ��ġ Ȯ��
    vector<int> idx;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '_')
            idx.push_back(i);
    }

    // _ ���� ���
    if (idx.size() == 0)
        return false;
    // _ 1���� ��� �߰��� �빮�� �ֳ� Ȯ��
    if (idx.size() == 1) {
        string tmp1 = s.substr(0, idx[0]);
        string tmp2 = s.substr(idx[0] + 1, 100);
        for (int i = 0; i < tmp1.size(); i++) {
            if (tmp1[i] >= 'A' && tmp1[i] <= 'Z')
                return true;
        }
        for (int i = 0; i < tmp2.size(); i++) {
            if (tmp2[i] >= 'A' && tmp2[i] <= 'Z')
                return true;
        }
        // ������ not error
        return false;
    }

    // _ ���� 2�� �̻� 
    for (int i = 0; i < idx.size() - 1; i++) {
        if (idx[i] + 1 == idx[i + 1])
            return true;
    }

    // _ ���̿� �빮�� ����
    string tmp;
    tmp = s.substr(0, idx[0]);
    for (int i = 0; i < tmp.size(); i++) {
        if (tmp[i] >= 'A' && tmp[i] <= 'Z')
            return true;
    }

    for (int i = 0; i < idx.size() - 1; i++) {
        int diff = idx[i + 1] - idx[i] - 1;
        tmp = s.substr(idx[i] + 1, diff);
        for (int j = 0; j < tmp.size(); j++) {
            if (tmp[j] >= 'A' && tmp[j] <= 'Z')
                return true;
        }
    }

    tmp = s.substr(idx[idx.size() - 1] + 1, 100);
    // �ִ� 100�����̹Ƿ� ���������� ����
    for (int i = 0; i < tmp.size(); i++) {
        if (tmp[i] >= 'A' && tmp[i] <= 'Z')
            return true;
    }

    return false;
}

// _�� �빮�� ��ġ Ȯ�� 
void indexCheck()
{
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '_')
            cpp.push_back(i);
    }

    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            java.push_back(i);
    }
}

// cpp or java check 
bool isCpp()
{
    if (cpp.size() == 0)
        return false;
    return true;
}

// �ҹ��ڸ� �ִ� ���
bool onlyLower()
{
    if (cpp.size() == 0 && java.size() == 0)
        return true;
    return false;
}

// cpp -> java 
void cppToJava()
{
    // ù _���� ���
    string tmp = s.substr(0, cpp[0]);
    ans = "";
    ans += tmp;

    // �߰� ��� 
    for (int i = 0; i < cpp.size() - 1; i++) {
        int diff = cpp[i + 1] - cpp[i] - 1;
        tmp = s.substr(cpp[i] + 1, diff);
        char c = tmp[0];
        int upperDiff = (int)('A' - 'a');
        tmp[0] = c + upperDiff;
        ans += tmp;
    }

    // ������ _���� ���������� ��� (�ִ� 100����)
    tmp = s.substr(cpp[cpp.size() - 1] + 1, 100);
    tmp[0] += (int)('A' - 'a');
    ans += tmp;
}

void javaToCpp()
{
    // ù �빮�ڱ��� ��� 
    string tmp = s.substr(0, java[0]);
    ans = "";
    ans += tmp;
    ans += "_";

    // �߰� ��� 
    for (int i = 0; i < java.size() - 1; i++) {
        int diff = java[i + 1] - java[i];
        tmp = s.substr(java[i], diff);
        char c = tmp[0];
        int lowerDiff = (int)('A' - 'a');
        tmp[0] = c - lowerDiff;
        ans += tmp;
        ans += "_";
    }

    // ������ ��� 
    tmp = s.substr(java[java.size() - 1], 100);
    char c = tmp[0];
    tmp[0] = c - (int)('A' - 'a');
    ans += tmp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    if (errorCheck())
        cout << "Error!";
    else {
        indexCheck();

        if (onlyLower()) {
            cout << s;
            return 0;
        }

        if (isCpp()) {
            cppToJava();
            cout << ans;
        }
        else {
            javaToCpp();
            cout << ans;
        }
    }

    return 0;
}