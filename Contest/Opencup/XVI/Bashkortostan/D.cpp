#include <bits/stdc++.h>
using namespace std;

int s[20][200005];

int query(int l, int r) {
    int p = 31 - __builtin_clz(r - l + 1);
    return max(s[p][l], s[p][r - (1 << p) + 1]);
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, w; cin >> n >> w;
    for (int i = 0; i < n; ++i) cin >> s[0][i];
    for (int i = 1; (1 << i) <= n; ++i) {
        for (int j = 0; j + (1 << i) <= n; ++j)
            s[i][j] = max(s[i - 1][j], s[i - 1][j + (1 << (i - 1))]);
    }
    for (int l = 1; l <= n; ++l) {
        int tot = -1;
        int L = 1, R = l;
        while (tot <= w && L <= n) {
            tot += query(L - 1, R - 1) + 1;
            L += l, R = min(n, R + l);
        }
        if (tot <= w) {
            cout << l << endl;
            exit(0);
        }
    }
    assert(false);
}
