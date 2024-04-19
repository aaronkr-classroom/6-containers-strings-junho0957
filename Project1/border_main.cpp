#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "border.h"

using namespace std;

int main() {
    vector<string> p;
    p.push_back("this is an");
    p.push_back("example");
    p.push_back("to");
    p.push_back("illustrate"); // show
    p.push_back("framing");

    ostream_iterator<string> ofile(cout, "\n");
    copy(p.begin(), p.end(), ofile);
    cout << endl;

    vector<string> f = frame(p);
    copy(f.begin(), f.end(), ofile);
    cout << endl;

    vector<string> h = hcat(frame(p), p);
    copy(h.begin(), h.end(), ofile);
    cout << endl;

    vector<string> v = vcat(p,frame(p));
    copy(v.begin(), v.end(), ofile);
    cout << endl;

  	return 0;
}