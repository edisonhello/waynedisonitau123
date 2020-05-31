#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k, w;
    cin >> n >> m >> k >> w;
    vector<int> a(m), b(m), c(m);
    vector<bool> s(n);
    vector<int> uf(n);
    vector<int> sp(m);

    function<int(int)> Find = [&](int x) {
        if (x == uf[x]) return x;
        return uf[x] = Find(uf[x]);
    };

    auto Merge = [&](int x, int y) {
        x = Find(x);
        y = Find(y);
        uf[x] = y;
    };

    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        s[x - 1] = true;
    }
    iota(uf.begin(), uf.end(), 0);
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i] >> c[i];
        a[i]--;
        b[i]--;
        Merge(a[i], b[i]);
        sp[i] = s[a[i]] != s[b[i]];
    }
    for (int i = 0; i < n; ++i) {
        if (Find(i) != Find(0)) {
            cout << "-1\n";
            return 0;
        }
    }
    vector<int> ord(m);
    iota(uf.begin(), uf.end(), 0);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return sp[i] < sp[j]; });
    int x = 0, y = 0;
    for (int i = 0; i < m; ++i) {
        if (Find(a[ord[i]]) != Find(b[ord[i]])) {
            Merge(a[ord[i]], b[ord[i]]);
            x += sp[ord[i]];
        }
    }
    sort(ord.begin(), ord.end(), [&](int i, int j) { return sp[i] > sp[j]; });
    iota(uf.begin(), uf.end(), 0);
    for (int i = 0; i < m; ++i) {
        if (Find(a[ord[i]]) != Find(b[ord[i]])) {
            Merge(a[ord[i]], b[ord[i]]);
            y += sp[ord[i]];
        }
    }
    if (w < x || w > y) {
        cout << "-1\n";
        return 0;
    }
    int cost = 200'000;

    auto Check = [&](int v) {
        iota(uf.begin(), uf.end(), 0);

        vector<int> cost(c.begin(), c.end());
        vector<int> sp(m);
        for (int i = 0; i < m; ++i) {
            sp[i] = s[a[i]] != s[b[i]];
            if (sp[i]) cost[i] += v;
        }

        vector<int> ord(m);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int i, int j) {
            if (cost[i] == cost[j]) return sp[i] < sp[j];
            return cost[i] < cost[j];
        });

        int64_t sum = 0;
        int cnt = 0;

        for (int i = 0; i < m; ++i) {
            if (Find(a[ord[i]]) != Find(b[ord[i]])) {
                Merge(a[ord[i]], b[ord[i]]);
                sum += cost[ord[i]];
                cnt += sp[ord[i]];
            }
        }
        return make_pair(sum, cnt);
    };

    for (int d = 20; d >= 0; --d) {
        auto r = Check(cost - (1 << d));
        if (r.second == w) {
            cout << r.first - 1LL * (cost - (1 << d)) * w << "\n";
            return 0;
        }
        if (r.second < w) cost -= (1 << d);
    }
    auto r = Check(cost);
    cout << r.first - 1LL * cost * w << "\n";
}

