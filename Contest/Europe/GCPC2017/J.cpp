#include <bits/stdc++.h>
using namespace std;

const int maxn = 18;
int c[maxn][maxn], h, w, n;
int fr[1 << maxn][maxn];
pair<int, int> dp[1 << maxn][maxn];
vector<string> s;
vector<int> rec[maxn];
bool v[1 << maxn][maxn];

pair<int, int> dfs(int sk, int x) {
    if (__builtin_popcount(sk) == 1) {
        if (sk & (1 << x)) return make_pair(0, s[x].size() - 1);
        return make_pair(maxn, maxn);
    } 
    if (v[sk][x]) return dp[sk][x];
    dp[sk][x] = make_pair(maxn, maxn);
    for (int i = 0; i < n; ++i) {
        if ((sk >> i & 1) == 0) continue;
        if (i == x) continue;
        pair<int, int> p = dfs(sk ^ (1 << x), i);
        if (p.second + c[i][x] < w) {
            pair<int, int> tdp = make_pair(p.first, p.second + c[i][x]);
            if (tdp < dp[sk][x]) {
                dp[sk][x] = tdp;
                fr[sk][x] = i;
            }
        } else {
            pair<int, int> tdp = make_pair(p.first + 1, s[x].size() - 1);
            if (tdp < dp[sk][x]) {
                dp[sk][x] = tdp;
                fr[sk][x] = i;
            }
        }
    }
    v[sk][x] = true;
    return dp[sk][x];
}

bool contain(const string &a, const string &b) {
    if (a.size() < b.size()) return false;
    for (int i = 0; i + b.size() <= a.size(); ++i) {
        if (a.substr(i, b.size()) == b) return true;
    }
    return false;
}

int main() {
    cin >> h >> w >> n;
    s.resize(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    while (true) {
        bool f = false;
        vector<string> t;
        for (int i = 0; i < s.size() && !f; ++i) {
            for (int j = 0; j < s.size() && !f; ++j) {
                if (i == j) continue;
                if (contain(s[i], s[j])) {
                    for (int k = 0; k < s.size(); ++k) {
                        if (k == j) continue;
                        t.push_back(s[k]);
                    }
                    f = true;
                    break;
                }
            }
        }
        if (!f) break;
        s = t;
    }
    n = s.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            c[i][j] = s[j].size();
            for (int k = 1; k <= min(s[i].size(), s[j].size()); ++k) {
                if (s[i].substr(s[i].size() - k, k) == s[j].substr(0, k)) 
                    c[i][j] = min(c[i][j], (int)s[j].size() - k);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s[i].size() > w) {
            puts("impossible");
            return 0;
        }
    }
    pair<int, int> ans = make_pair(maxn, maxn);
    int k = -1;
    for (int i = 0; i < n; ++i) {
        pair<int, int> p = dfs((1 << n) - 1, i);
        if (p < ans) ans = p, k = i;
    }
    if (ans.first >= h || ans.second >= w) {
        puts("impossible");
        return 0;
    }
    int sk = (1 << n) - 1, x = k;
    while (true) {
        rec[dp[sk][x].first].push_back(x);
        if (__builtin_popcount(sk) == 1) break;
        int y = fr[sk][x];
        sk ^= (1 << x), x = y;
    }
    for (int i = 0; i < h; ++i) reverse(rec[i].begin(), rec[i].end());
    for (int i = 0; i < h; ++i) {
        string f = "";
        for (int j = 0; j < rec[i].size(); ++j) {
            if (j == 0) f += s[rec[i][j]];
            else for (int k = s[rec[i][j]].size() - c[rec[i][j - 1]][rec[i][j]]; k < s[rec[i][j]].size(); ++k) f += s[rec[i][j]][k];
        }
        while (f.size() < w) f += 'A';
        cout << f << endl;
    }
}
