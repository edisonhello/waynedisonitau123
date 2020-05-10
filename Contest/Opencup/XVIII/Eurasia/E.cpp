#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int m, n;
    cin >> m >> n;
    vector<int> A(n, -1), B(n, -1), cnt(n);
    for (int i = 0; i < m; ++i) {
        int c, p;
        cin >> c >> p;
        if (c == -1) continue;
        c--, p--;
        if (A[c] == -1) {
            assert(p == 0);
            A[c] = i;
        }
        B[c] = i;
        cnt[c]++;
    }
    for (int i = 0; i < n; ++i) {
        assert(B[i] - A[i] + 1 == cnt[i]);
    }
    vector<int> S(cnt.begin(), cnt.end());
    for (int i = 1; i < n; ++i) S[i] += S[i - 1];
    vector<int> key(n), que(n), ds;
    for (int i = 0; i < n; ++i) {
        key[i] = B[i] - S[i];
        que[i] = A[i] - (i > 0 ? S[i - 1] : 0) - 1;
        ds.push_back(key[i]);
        ds.push_back(que[i]);
    }
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < n; ++i) {
        key[i] = lower_bound(ds.begin(), ds.end(), key[i]) - ds.begin();
        que[i] = lower_bound(ds.begin(), ds.end(), que[i]) - ds.begin();
    }
    vector<int> dp(n);
    vector<int> fr(n, -1);
    int res = 0, best = -1;

    vector<pair<int, int>> fenw(ds.size() + 1, make_pair(0, -1));

    auto Update = [&](int p, pair<int, int> v) {
        for (int i = p + 1; i <= ds.size(); i += i & -i) {
            fenw[i] = max(fenw[i], v);
        }
    };

    auto Query = [&](int p) {
        pair<int, int> res{0, -1};
        for (int i = p + 1; i > 0; i -= i & -i) {
            res = max(res, fenw[i]);
        }
        return res;
    };

    for (int i = 0; i < n; ++i) {
        int pre = i > 0 ? S[i - 1] : 0;
        if (A[i] >= pre) {
            auto r = Query(que[i]);
            dp[i] = r.first + cnt[i];
            fr[i] = r.second;
            Update(key[i], make_pair(dp[i], i));
        // for (int j = 0; j < i; ++j) {
        //     if (S[i - 1] - S[j] <= A[i] - B[j] - 1) {
        //         int v = dp[j] + cnt[i];
        //         if (v > dp[i]) {
        //             dp[i] = v;
        //             fr[i] = j;
        //         }
        //     }
        // }
            if (m - 1 - B[i] >= S[n - 1] - S[i]) {
                if (dp[i] > res) {
                    res = dp[i];
                    best = i;
                } 
            }
        }
    }
    vector<bool> keep(n);
    for (int i = best; i != -1; i = fr[i]) keep[i] = true;
    int ptr = 0;
    vector<pair<int, int>> ed;
    for (int i = 0; i < n; ++i) {
        if (keep[i]) {
            assert(ptr <= A[i]);
            ptr = B[i] + 1;
            continue;
        }
        for (int j = 0; j < cnt[i]; ++j) {
            int p = A[i] + j;
            assert(p != ptr);
            ed.emplace_back(p, ptr);
            ptr++;
        }
    }
    assert(ed.size() == S[n - 1] - res);
    vector<bool> used(m);
    vector<vector<int>> g(m);
    vector<int> deg(m);
    for (int i = 0; i < ed.size(); ++i) {
        int x = ed[i].first;
        int y = ed[i].second;
        g[x].push_back(y);
        deg[y]++;
    }
    vector<vector<int>> ans;
    for (int i = 0; i < m; ++i) {
        if (g[i].empty() || used[i]) continue;
        if (deg[i] > 0) continue;
        vector<int> chain;
        int x = i;
        while (true) {
            chain.push_back(x);
            used[x] = true;
            if (g[x].empty()) break;
            assert(g[x].size() == 1);
            x = g[x][0];
        }
        ans.push_back(chain);
    }
    for (int i = 0; i < m; ++i) {
        if (g[i].empty() || used[i]) continue;
        vector<int> cycle;
        int x = i;
        while (true) {
            cycle.push_back(x);
            if (used[x]) break;
            used[x] = true;
            assert(g[x].size() == 1);
            x = g[x][0];
        }
        ans.push_back(cycle);
    }
    cout << S[n - 1] - res << " " << ans.size() << "\n";
    for (auto &v : ans) {
        cout << v.size();
        for (int u : v) cout << " " << u + 1;
        cout << "\n";
    }
    return 0;
}

