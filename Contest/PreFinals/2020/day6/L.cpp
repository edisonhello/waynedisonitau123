#include <bits/stdc++.h>
using namespace std;

long long c[1005];
long long bit[25009];

void Add(int x, long long y) {
    for (; x < 25009; x += x & -x)
        bit[x] = max(bit[x], y);
}

long long Query(int x) {
    long long r = 0;
    for (; x; x -= x & -x)
        r = max(r, bit[x]);
    return r;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int m, n; cin >> m >> n;
    for (int i = 1; i <= m; ++i) cin >> c[i];
    vector<tuple<int, int, long long>> segs;
    for (int i = 0; i < n; ++i) {
        int s, e; cin >> s >> e;
        int t; cin >> t;
        segs.emplace_back(s, e, 1ll * (e - s) * c[t]);
    }

    sort(segs.begin(), segs.end());

    for (auto &t : segs) {
        int s, e; long long cc; tie(s, e, cc) = t;
        Add(e, Query(s) + cc);
    }

    cout << Query(20000) << '\n';
}

