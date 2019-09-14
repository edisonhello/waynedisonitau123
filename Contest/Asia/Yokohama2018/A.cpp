#include <bits/stdc++.h>
using namespace std;

vector<pair<bool, string>> parse(string s) {
    vector<pair<bool, string>> res;
    for (int i = 0, j = 0; i < s.size(); i = j) {
        for (j = i; isalpha(s[i]) && isalpha(s[j]) || isdigit(s[i]) && isdigit(s[j]); ++j);
        res.emplace_back(isalpha(s[i]), s.substr(i, j - i));
    }
    return res;
}

int ToInt(string s) {
    stringstream ss(s);
    int res; ss >> res;
    return res;
}

int main() {
    int n; cin >> n;
    string t; cin >> t;
    vector<pair<bool, string>> v = parse(t);
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        vector<pair<bool, string>> w = parse(s);
        bool leq = v.size() > w.size();
        for (int j = 0; j < (int)min(v.size(), w.size()); ++j) {
            if (v[j].first != w[j].first) {
                if (v[j].first) leq = true;
                else leq = false;
                break;
            }
            if (v[j].first) {
                if (v[j].second != w[j].second) {
                    leq = v[j].second > w[j].second;
                    break;
                }
            } else {
                int a = ToInt(v[j].second);
                int b = ToInt(w[j].second);
                if (a != b) {
                    leq = a > b;
                    break;
                }
            }
        }
        if (leq) puts("-");
        else puts("+");
    }
}
