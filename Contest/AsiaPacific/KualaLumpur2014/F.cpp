#include <bits/stdc++.h>
using namespace std;

int syll(string s) {
    if (s.size() >= 6u) {
        if (s.size() == 6u) {
            for (int i = 1; i < (int)s.size(); ++i) {
                if (s[i - 1] == 'n') {
                    if (s[i] == 'g' || s[i] == 'y') return 2;
                }
            }
        }
        return 3;
    } else if (s.size() <= 3u) {
        if (s.size() == 3u && (s[0] == 'a' || s[0] == 'e' || s[0] == 'i' || s[0] == 'o' || s[0] == 'u')) return 2;
        return 1;
    } else {
        return 2;
    }
}

string last2(string s) {
    return s.substr(s.size() - 2, 2);
}

int main() {
    int t; cin >> t;
    cin.ignore();
    for (int T = 1; T <= t; ++T) {
        string s; 
        getline(cin, s);
        vector<vector<string>> vs;
        vector<string> cur;
        bool stop = 0;
        vector<string> bruh;
        string curstr;
        for (char c : s) {
            if (isalpha(c)) curstr += c;
            else if (c == ' ') {
                if (curstr.size() && !stop) bruh.push_back(curstr);
                curstr = "";
            } else if (c == '.' || c == ',') {
                if (!stop && curstr.size()) bruh.push_back(curstr);
                curstr = "";
                curstr += c;
                if (!stop) bruh.push_back(curstr);
                curstr = "";
                if (c == '.') stop = 1;
            }
        }
        if (curstr.size()) bruh.push_back(curstr);

        for (string s : bruh) {
            if (s.back() == ',' || s.back() == '.') {
                s.pop_back();
                // cur.push_back(s);
                vs.push_back(cur);
                cur.clear();
            } else {
                for (char &c : s) {
                    if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
                }
                cur.push_back(s);
            }
        }

        // for (auto v : vs) {
        //     cerr << "line: ";
        //     for (auto s : v) cerr << s << "(" << syll(s) << ") ";
        //     cerr << endl;
        // }

        int A = 0, B = 0, C = 0, D = 0;
        for (int i = 0; i < min(4, (int)vs.size()); ++i) {
            int cc = 0;
            for (string s : vs[i]) cc += syll(s);

            if (8 <= cc && cc <= 12) {
                A += 10;
            }
        }

        if ((int)vs.size() >= 3) {
            if (last2(vs[0].back()) == last2(vs[2].back())) B += 20;
            int ac = 0, bc = 0;
            for (string s : vs[0]) ac += syll(s);
            for (string s : vs[2]) bc += syll(s);
            if (ac == bc) C += 10;
        }
        if ((int)vs.size() >= 4) {
            if (last2(vs[1].back()) == last2(vs[3].back())) B += 20;
            int ac = 0, bc = 0;
            for (string s : vs[1]) ac += syll(s);
            for (string s : vs[3]) {
                bc += syll(s);
            }
            if (ac == bc) C += 10;
        }

        D = max(0, (int)vs.size() - 4) * 10;

        cout << "Case #" << T << ": ";
        cout << A << " " << B << " " << C << " " << D << " " << A + B + C - D << '\n';
    }
}
