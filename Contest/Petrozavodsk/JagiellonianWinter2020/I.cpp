#include <bits/stdc++.h>
using namespace std;

void Solve() {
    string s;
    cin >> s;
    vector<string> res;
    while (!s.empty()) {
        int n = s.size();
        bool z = true;
        for (int i = 1; i < n; ++i) z &= s[i] == '0';
        if (n > 1 && s[0] == '1' && z) {
            string t = string(n - 1, '9');
            res.push_back(t);
            res.push_back("1");
            break;
        }
        string t = "";
        for (int i = 0; i < n / 2; ++i) {
            t += s[i]; 
        }
        if (n & 1) t += s[n / 2];
        for (int i = n / 2 - 1; i >= 0; --i) {
            t += s[i];
        }
        if (t > s) {
            if ((n & 1) && t[n / 2] > '0') {
                t[n / 2]--;
            } else {
                for (int i = n / 2 - 1; i >= 0; --i) {
                    if (t[i] > '0') {
                        t[i]--;
                        assert(t[n - 1 - i] > '0');
                        t[n - 1 - i]--;
                        break;
                    }
                }
            }
        }
        assert(t <= s);
        res.push_back(t);
        for (int i = n - 1; i >= 0; --i) {
            int a = s[i] - '0';
            int b = t[i] - '0';
            if (a < b) {
                for (int j = i - 1; j >= 0; --j) {
                    if (s[j] > '0') {
                        s[j]--;
                        a += 10;
                        for (int k = j + 1; k < i; ++k) s[k] += 9;
                        break;
                    }
                }
            }
            assert(a >= b);
            s[i] = (a - b) + '0';
        }
        int p = 0;
        while (p < n && s[p] == '0') p++;
        s = s.substr(p);
    }
    cout << res.size() << "\n";
    for (auto &s : res) cout << s << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
}

