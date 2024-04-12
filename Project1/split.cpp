//split.cpp
#include<cctype>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<string>split(const string& s) {
	vector<string>ret;
	typedef string::size_type string_size; // 파이썬 as 처럼
	string_size i = 0; // int 대신 string::size_type 사용

	// 불변성: 지금까지 [원래의i, 현재의i) 범위에 있는 
	// 문자들을 처리
	while (i != s.size()) {
		// 선행하는 공백들을 무시
		// 불변성: [원래의i, 현재의i) 범위에 있는 
	    // 문자들은 모두 공백
		while (i != s.size() && isspace(s[i])) {
			++i;
		}
        
		// 순서상 다음 단어의 끝을 찾음
		string_size j = i;

		// 불변성: [원래의j, 현재의j) 범위에 있는 
		// 문자들은 공백이 아님
		while (j != s.size() && !isspace(s[j])) {
			j++;
		}

		// 공백이 아닌 문자들을 찾았을 때
		if (i != j) {
			// i에서부터 j-i개의 문자들을 s에 복사
			ret.push_back(s.substr(i, j - 1));
			i = j;
		}
	}
	return ret;
}

int main() {
	string s;

	// 문자열을 한 행씩 입력받아 분할
	while (getline(cin, s)) {
		vector<string> v = split(s);

		// 벡터 v에 저장한 단어를 각각 출력 
		for (vector<string>::size_type i = 0;
			i != v.size(); i++) {
			cout << v[i] << endl;
		}
	}
	return 0;
}