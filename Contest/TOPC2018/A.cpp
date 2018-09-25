#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] >= 'A' && s[i] <= 'Z') s[i] = (s[i] - 'A') + 'a';
        }
        bool nn = false;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'n') nn = true;
        }
        if (nn) {
            cout << "No" << endl;
            continue;
        }
        bool ac = false;
        for (int i = 0; i < s.size(); ++i) {
            if (i + 2 <= s.size()) {
                if (s.substr(i, 2) == "ac") ac = true;
            }
            if (i + 3 <= s.size()) {
                if (s.substr(i, 3) == "yes") ac = true;
            }
        }
        if (ac) cout << "Yes" << endl;
        else cout << "Unknown" << endl;
    }
}
