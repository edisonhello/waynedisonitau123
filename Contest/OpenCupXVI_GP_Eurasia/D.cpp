#include <bits/stdc++.h>
using namespace std;

struct L {
    int w, c;
} l[100005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int d, n; cin >> d >> n;
    for (int i = 1; i <= n; ++i) {
        int a, b, c; cin >> a >> b >> c;
        l[i].w = a * b;
        l[i].c = a * c;
    }
    sort(l + 1, l + 1 + n, [&](const L &a, const L &b) { return a.w < b.w; });
    vector<L> v; v.push_back(l[1]);
    for (int i = 2; i <= n; ++i) {
        if (l[i].c < v.back().c) continue;
        v.push_back(l[i]);
    }
    auto ok = [&] (double ww) {
        double nd = d;
        for (L l : v) {
            if (l.c <= ww) continue;
            double ll = (l.c - ww) / l.w;
            nd -= ll;
            ww  = l.c;
            if (nd < 0) break;
        }
        if (nd > 0) return false;
        return true;
    };
    double L = 0, R = 1e7;
    while (R - L > 1e-7) {
        double M = (L + R) / 2;
        if (ok(M)) L = M;
        else R = M;
    }
    cout << fixed << setprecision(10) << L << endl;
}
