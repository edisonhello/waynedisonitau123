#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> c(n);
    vector<int> l(m, n), r(m, -1);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        c[i]--;
        l[c[i]] = min(l[c[i]], i);
        r[c[i]] = max(r[c[i]], i);
    }
    vector<int> work(m);
    iota(work.begin(), work.end(), 0);
    sort(work.begin(), work.end(), [&](int i, int j) { return l[i] < l[j]; });

    constexpr int64_t kInf = 1'000'000'000'000'000'000;

    auto Best = [&](vector<int> a) -> int64_t {
        int n = a.size();
        vector<vector<int64_t>> dp(n, vector<int64_t>(n, -kInf));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = a[i];
        }
        vector<int> s(a.begin(), a.end());
        for (int i = 1; i < n; ++i) s[i] += s[i - 1];
        for (int k = 1; k < n; ++k) {
            for (int i = 0; i + k < n; ++i) {
                int g = s[i + k] - (i == 0 ? 0 : s[i - 1]);
                dp[i][i + k] = max(dp[i][i + k], dp[i][i + k - 1] + g);
                dp[i][i + k] = max(dp[i][i + k], dp[i + 1][i + k] + g);
            }
        }
        return dp[0][n - 1];
    };

    function<int64_t(vector<int>)> Solve = [&](vector<int> w) -> int64_t {
        if (w.empty()) return 0;
        int pv = -1;
        vector<int> tw, nw;
        for (int i = 0; i < w.size(); ++i) {
            if (r[w[i]] > pv) {
                tw.push_back(r[w[i]] - l[w[i]] + 1);
            } else {
                nw.push_back(w[i]);
            }
            pv = max(pv, r[w[i]]);
        }
        int64_t res = Best(tw);
        for (int i = 0, j = 0; i < nw.size(); i = j) {
            int exp = l[nw[i]];
            vector<int> v;
            while (j < nw.size() && l[nw[j]] <= exp) {
                v.push_back(nw[j]);
                exp = max(r[nw[j]] + 1, exp);
                j++;
            }
            res += Solve(v);
        }
        return res;
    };

    cout << Solve(work) << "\n";
    return 0;
}


