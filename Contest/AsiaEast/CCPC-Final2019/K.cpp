#include <bits/stdc++.h>
using namespace std;

void Solve() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<set<pair<int, int>>> s(n);

    auto Intersect = [&](auto a, auto b) {
        int l = max(a.first, b.first);
        int r = min(a.second, b.second);
        return l - r <= 1;
    };

    auto Insert = [&](set<pair<int, int>> &a, pair<int, int> p) {
        auto it = a.upper_bound(make_pair(p.first, n + 1));
        if (it != a.begin() && Intersect(*prev(it), p)) it = prev(it);
        while (it != a.end() && Intersect(*it, p)) {
            p.first = min(p.first, it->first);
            p.second = max(p.second, it->second);
            it = a.erase(it);
        }
        a.insert(p);
    };

    vector<int> ans(n);

    function<void(int, int)> Dfs = [&](int x, int p) {
        for (int u : g[x]) {
            if (u == p) continue;
            Dfs(u, x);
            if (s[u].size() > s[x].size()) s[x].swap(s[u]);
            for (auto &p : s[u]) Insert(s[x], p);
        } 
        Insert(s[x], make_pair(x, x));
        ans[x] = (int)s[x].size();
    };

    Dfs(0, -1);
    for (int i = 0; i < n; ++i) printf("%d%c", ans[i], " \n"[i + 1 == n]);
}

int main() {
    int t;
    scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        printf("Case #%d: ", tc);
        Solve();
    }
}

