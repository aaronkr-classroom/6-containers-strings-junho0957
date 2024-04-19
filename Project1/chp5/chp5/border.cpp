#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// ���ڿ��� �־��� �����ڸ� �������� �и��Ͽ� ���Ϳ� �����ϴ� �Լ�
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// ���ڿ� ������ �ִ� ���̸� ��ȯ�ϴ� �Լ�
string::size_type width(const vector<string>& v) {
    string::size_type maxlen = 0;
    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        maxlen = max(maxlen, v[i].size());
    }
    return maxlen;
}

// ���ڿ� ���Ϳ� �������� �߰��ϴ� �Լ�
vector<string> frame(const vector<string>& v) {
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');

    // ��� �׵θ� �߰�
    ret.push_back(border);

    // ���ڿ��� ���� ��ǥ�� �������� �ѷ��� �� ���Ϳ� �߰�
    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");
    }

    // �ϴ� �׵θ� �߰�
    ret.push_back(border);

    return ret;
}

// ���ڿ� ���͸� �������� �����ϴ� �Լ�
vector<string> vcat(const vector<string>& top, const vector<string>& bottom) {
    vector<string> ret = top;
    for (vector<string>::const_iterator it = bottom.begin(); it != bottom.end(); ++it) {
        ret.push_back(*it);
    }
    return ret;
}

// ���ڿ� ���͸� �������� �����ϴ� �Լ�
vector<string> hcat(const vector<string>& left, const vector<string>& right) {
    vector<string> ret;
    // �� ���ڿ� ���̿� ������ ����
    string::size_type width1 = width(left) + 1;
    // ���� ���ڿ��� ������ ���ڿ��� ��Ҹ� ���캸�� �ε���
    vector<string>::size_type i = 0, j = 0;
    while (i != left.size() || j != right.size()) {
        // �� ���ڿ��� ���ڵ��� ������ ���ο� ���ڿ��� ����
        string s;

        // ���� ���ڿ����� �� �ϳ��� ����
        if (i != left.size()) {
            s = left[i++];
        }
        s += string(width1 - s.size(), ' ');
        if (j != right.size()) {
            s += right[j++];
        }
        ret.push_back(s);
    }
    return ret;
}

int main() {
    string s;
    vector<vector<string>> text_blocks; // �Էµ� �� ����� ������ ����
    while (getline(cin, s)) {
        vector<string> v = split(s, ' '); // ������ �������� ���ڿ� �и�
        text_blocks.push_back(v);
    }

    // �ؽ�Ʈ ��Ͽ� �������� �߰��ϰ� ���� �����Ͽ� ��� ����
    vector<string> result = frame(text_blocks[0]);
    for (size_t i = 1; i < text_blocks.size(); ++i) {
        vector<string> framed_block = frame(text_blocks[i]);
        result = vcat(result, framed_block);
    }

    // ����� ���Ͽ� ����
    ofstream outFile("out.txt");
    if (outFile.is_open()) {
        for (const string& line : result) {
            outFile << line << endl;
        }
        outFile.close();
        cout << "Output saved to out.txt" << endl;
    }
    else {
        cerr << "Unable to open file for writing" << endl;
        return 1;
    }

    return 0;
}