#include <bits/stdc++.h>
using namespace std;

void build_answer(string s, int sz) {
    int n = s.size();
    cout << "YES" << endl;
    cout << sz + 1 << endl;
    cout << 1 << endl;
    cout << n % sz + 1 << endl;
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (j == s[i] - 'a') cout << (i + 1) % sz + 1 << " ";
            else cout << sz + 1 << " ";
        } cout << endl;
    }
    for (int i = 0; i < 26; ++i) cout << sz + 1 << " "; cout << endl;
    int count = 0;
    for (char c : s) if (c == s[0]) ++count;
    cout << count + 2 << endl;
    cout << 1 << endl;
    cout << count + 1 << endl;
    for (int i = 0; i <= count; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (j == s[0] - 'a') cout << i + 2 << " ";
            else cout << i + 1 << " ";
        } cout << endl;
    }
    for (int i = 0; i < 26; ++i) cout << count + 2 << " "; cout << endl;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("decomposable.in", "r", stdin);
    freopen("decomposable.out", "w", stdout);
#endif
    string s; while (cin >> s) {
        for (char &c : s) c -= 'a';
        int n = s.size();
        if ([&]() -> bool {
            for (int i = 1; i < n; ++i) if (s[i] != s[i - 1]) return false;
            return true;
        }()) {
            cout << "NO" << endl;
        } else {
            vector<vector<int>> dfa, dfb;
            {
                vector<int> v(26, 0);
                v[s[0]] = 1;
                int nx = 0;
                while (s[nx] == s[0]) ++nx;
                v[s[nx]] = 2;
                dfa.push_back(v);
                int idx = 3;
                while (nx < n) {
                    ++nx;
                    vector<int> v(26, 0);
                    v[s[nx]] = idx;
                    ++idx;
                    dfa.push_back(v);
                }
            } {
                for (int i = 0; i < n; ++i) {
                    bool same = true;
                    for (int j = i; j < n; ++j) if (s[j] != s[i]) same = false;
                    if (same) {
                        vector<int> v(26, 0);
                        v[s[i]] = dfb.size() + 1;
                        dfb.push_back(v);
                        break;
                    } else {
                        vector<int> v(26, 0);
                        v[s[i]] = dfb.size() + 2;
                        dfb.push_back(v);
                    }
                }
            }
            auto output = [&] (vector<vector<int>> &v) -> void {
                for (vector<int> &vv : v) for (int &i : vv) if (!i) i = v.size() + 1;
                cout << v.size() + 1 << endl;
                cout << 1 << endl;
                cout << v.size() << endl;
                for (vector<int> &vv : v) {
                    for (int &i : vv) cout << i << " ";
                    cout << endl;
                }
                for (int i = 0; i < 26; ++i) cout << v.size() + 1 << " "; cout << endl;
            };
            cout << "YES" << endl;
            output(dfa);
            output(dfb);
        }
    }
}
