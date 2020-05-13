#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    constexpr int kM = 173554;
    map<vector<int>, string> rep;
    int m;
    cin >> m;
    assert(m == kM);
    for (int i = 0; i < kM; ++i) {
        string t;
        cin >> t;
        vector<int> ch(26);
        for (char c : t) ch[c - 'a']++;
        if (rep.find(ch) == rep.end()) {
            rep[ch] = t;
        }
    }
    map<vector<int>, int> dp;
    map<vector<int>, int> fr;

    vector<int> ch(26);
    rep[ch] = ".";

    function<int(vector<int>)> Dfs = [&](vector<int> x) {
        if (*max_element(x.begin(), x.end()) == 0) return 1;
        if (dp.find(x) != dp.end()) return dp[x];
        int res = 1, f = -1;
        for (int i = 0; i < 26; ++i) {
            if (x[i] > 0) {
                x[i]--;
                if (rep.find(x) != rep.end()) {
                    int d = Dfs(x) + 1;
                    if (d > res) {
                        res = d;
                        f = i;
                    }
                }
                x[i]++;
            }
        }
        dp[x] = res;
        if (f != -1) fr[x] = f;
        return res;
    };

    for (int i = 0; i < n; ++i) {
        vector<int> ch(26);
        for (char c : s[i]) ch[c - 'a']++;
        auto orig = ch;
        int res = Dfs(ch);
        cout << res << "\n";
        vector<string> v;
        while (true) {
            if (ch == orig) {
                v.push_back(s[i]);
            } else {
                assert(rep.find(ch) != rep.end());
                v.push_back(rep[ch]);
            }
            if (fr.find(ch) == fr.end()) break;
            int b = fr[ch];
            assert(ch[b] > 0);
            ch[b]--;
        }
        for (int i = 0; i < v.size(); ++i) {
            if (i > 0) {
                cout << " -> ";
            }
            cout << v[i];
        }
        cout << endl;
    }
    return 0;
}

