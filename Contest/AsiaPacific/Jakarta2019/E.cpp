#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
int a[kN], x[kN], y[kN];

int main() {
    int n, l, r, k;
    scanf("%d%d%d%d", &n, &l, &r, &k);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    x[n - 1] = l, y[n - 1] = r;

    auto Bound = [&](int v) {
        if (v < l) v = l;
        if (v > r) v = r;
        return v;
    };

    for (int i = n - 2; i >= 0; --i) {
        if (a[i] == a[i + 1]) {
            x[i] = x[i + 1];
            y[i] = y[i + 1];
        } else if (a[i] > a[i + 1]) {
            x[i] = Bound(x[i + 1] + 1);
            y[i] = Bound(y[i + 1] + k);
        } else {
            x[i] = Bound(x[i + 1] - k);
            y[i] = Bound(y[i + 1] - 1);
        }
    }
    if (x[0] > y[0]) {
        puts("-1");
        return 0;
    }
    vector<int> ans = {x[0]};

    auto Intersect = [&](int a, int b, int x, int y) {
        return make_pair(max(a, x), min(b, y));
    };

    for (int i = 1; i < n; ++i) {
        int v = ans.back();
        if (a[i] == a[i - 1]) {
            auto p = Intersect(v, v, x[i], y[i]);
            if (p.second < p.first) {
                puts("-1");
                return 0;
            }
            ans.push_back(p.first);
        } else if (a[i] > a[i - 1]) {
            auto p = Intersect(v + 1, v + k, x[i], y[i]);
            if (p.second < p.first) {
                puts("-1");
                return 0;
            }
            ans.push_back(p.first);
        } else {
            auto p = Intersect(v - k, v - 1, x[i], y[i]);
            if (p.second < p.first) {
                puts("-1");
                return 0;
            }
            ans.push_back(p.first);
        }
    }
    for (int u : ans) printf("%d ", u);
    puts("");
}
