#include <bits/stdc++.h>
using namespace std;

int64_t Solve() {
    int n, m;
    cin >> n >> m;
    vector<int64_t> x(n), y(n), a(m), b(m);
    int64_t t = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        t ^= x[i];
        y[i] ^= x[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i];
        t ^= a[i];
        b[i] ^= a[i];
    }
    vector<int64_t> basis;
    for (int i = 0; i < m; ++i) {
        int64_t v = b[i];
        for (int64_t u : basis) v = min(v, v ^ u);
        if (v > 0) basis.push_back(v);
    }

    sort(basis.rbegin(), basis.rend());

    auto Reduce = [&](int64_t v) {
        for (int64_t u : basis) {
            v = min(v ^ u, v);
        }
        return v;
    };

    t = Reduce(t);
    for (int i = 0; i < n; ++i) y[i] = Reduce(y[i]);
    basis.clear();
    for (int i = 0; i < n; ++i) {
        int64_t v = y[i];
        for (int64_t u : basis) v = min(v, u ^ v);
        if (v > 0) basis.push_back(v);
    }
    sort(basis.rbegin(), basis.rend());
    for (int64_t u : basis) t = max(t, u ^ t);
    return t;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) cout << Solve() << "\n";
}

