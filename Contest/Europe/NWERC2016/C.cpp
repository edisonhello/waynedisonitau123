#include <bits/stdc++.h>
using namespace std;

struct shield {
    int l, u;
    double f;
} s[108];

int main() {
    int x, y; cin >> x >> y;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> s[i].l >> s[i].u >> s[i].f;
    s[n++] = shield{0, 0, 1};
    s[n++] = shield{y, y, 1};
    sort(s, s + n, [] (const shield &a, const shield &b) { return (a.l + a.u) < (b.l + b.u); });
    double sum = 0;
    for (int i = 1; i < n; ++i) {
        sum += s[i].l - s[i - 1].u;
        sum += (s[i].u - s[i].l) * s[i].f;
    }
    cout << fixed << setprecision(10) << (double)x / sum << endl;
}
