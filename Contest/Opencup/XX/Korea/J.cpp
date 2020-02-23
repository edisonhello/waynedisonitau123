#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<int> s(n), e(n), v(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &s[i], &e[i], &v[i]);
        s[i]--;
        e[i]--;
    }

    auto BuildTree = [&]() {
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int i, int j) { return e[i] - s[i] < e[j] - s[j]; });
        vector<vector<int>> g(n + 1);
        constexpr int kC = 1'000'000;
        vector<int> to(kC, -1), which(kC, -1);
        set<tuple<int, int, int>> st;
        for (int i = 0; i < n; ++i) {
            int j = ord[i];
            int p = s[j];
            auto it = st.lower_bound(make_tuple(p, -1, -1));
            while (it != st.end()) {
                if (it == st.end()) break;
                if (get<0>(*it) >= e[j]) break;
                assert(get<1>(*it) <= e[j]);
                g[j].push_back(get<2>(*it));
                it = st.erase(it);
            }
            st.insert(make_tuple(s[j], e[j], j));
        }
        for (auto it : st) {
            g[n].push_back(get<2>(it));
        }
        return g;
    };

    auto g = BuildTree();
    vector<multiset<int64_t, greater<int64_t>>> st(n + 1);

    function<void(int)> Dfs = [&](int x) {
        for (int u : g[x]) {
            Dfs(u);
            if (st[u].size() > st[x].size()) st[x].swap(st[u]);
            multiset<int64_t, greater<int64_t>> push;
            for (auto it : st[u]) {
                auto k = *st[x].begin();
                st[x].erase(st[x].begin());
                push.insert(k + it);
            }
            for (auto it : push) st[x].insert(it);
        }
        if (x != n) st[x].insert(v[x]);
        // cout << "x = " << x << "\n";
        // for (auto it : st[x]) cout << it << ' ';
        // cout << endl;
    };

    Dfs(n);
    vector<int64_t> ans(n);
    int i = 0;
    for (auto it : st[n]) {
        ans[i] = it;
        i++;
    }
    for (int i = 1; i < n; ++i) ans[i] += ans[i - 1];
    for (int i = 0; i < n; ++i) printf("%lld ", (long long)ans[i]);
    puts("");
}

