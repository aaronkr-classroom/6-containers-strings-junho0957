#ifndef GUARD_border_h
#define GUARD_border_h

#include <string>
#include <vector>

using namespace std;
string::size_type width(const vector<string>&);
vector<string>frame(const vector<string>&);


// 수직 결합 = vectrical concat
vector<string>vcat(const vector<string>&,
	const vector<string>&);

// 수평 결합 = horizontal concat
vector<string>hcat(const vector<string>&,
	const vector<string>&);
#endif
