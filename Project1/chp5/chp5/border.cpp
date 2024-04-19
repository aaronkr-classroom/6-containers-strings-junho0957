#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// 문자열을 주어진 구분자를 기준으로 분리하여 벡터에 저장하는 함수
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// 문자열 벡터의 최대 길이를 반환하는 함수
string::size_type width(const vector<string>& v) {
    string::size_type maxlen = 0;
    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        maxlen = max(maxlen, v[i].size());
    }
    return maxlen;
}

// 문자열 벡터에 프레임을 추가하는 함수
vector<string> frame(const vector<string>& v) {
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');

    // 상단 테두리 추가
    ret.push_back(border);

    // 문자열을 각각 별표와 공백으로 둘러싼 후 벡터에 추가
    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");
    }

    // 하단 테두리 추가
    ret.push_back(border);

    return ret;
}

// 문자열 벡터를 수직으로 결합하는 함수
vector<string> vcat(const vector<string>& top, const vector<string>& bottom) {
    vector<string> ret = top;
    for (vector<string>::const_iterator it = bottom.begin(); it != bottom.end(); ++it) {
        ret.push_back(*it);
    }
    return ret;
}

// 문자열 벡터를 수평으로 결합하는 함수
vector<string> hcat(const vector<string>& left, const vector<string>& right) {
    vector<string> ret;
    // 두 문자열 사이에 공백을 남김
    string::size_type width1 = width(left) + 1;
    // 왼쪽 문자열과 오른쪽 문자열의 요소를 살펴보는 인덱스
    vector<string>::size_type i = 0, j = 0;
    while (i != left.size() || j != right.size()) {
        // 두 문자열의 문자들을 저장할 새로운 문자열을 생성
        string s;

        // 왼쪽 문자열에서 행 하나를 복사
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
    vector<vector<string>> text_blocks; // 입력된 각 블록을 저장할 벡터
    while (getline(cin, s)) {
        vector<string> v = split(s, ' '); // 공백을 기준으로 문자열 분리
        text_blocks.push_back(v);
    }

    // 텍스트 블록에 프레임을 추가하고 수직 결합하여 결과 생성
    vector<string> result = frame(text_blocks[0]);
    for (size_t i = 1; i < text_blocks.size(); ++i) {
        vector<string> framed_block = frame(text_blocks[i]);
        result = vcat(result, framed_block);
    }

    // 결과를 파일에 저장
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