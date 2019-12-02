#include <bits/stdc++.h>
using namespace std;

int cnt[128];
char ans[1005][1005];

char gc() {
    static int p = 0;
    // cout << "gc p = " << p << endl;
    while (cnt[p] == 0) ++p;
    --cnt[p];
    // cout << "gc p = " << p << endl;
    return p;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, l, k; cin >> n >> l >> k;
    string s; cin >> s;
    for (char c : s) ++cnt[c];
    int head = 1;
    for (int i = 1; i <= l; ++i) {
        char prv = 'a' - 1;
        for (int j = head; j <= k; ++j) {
            ans[j][i] = gc();
            if (ans[j][i] != prv) {
                head = j;
                prv = ans[j][i];
            }
        }
    }
    for (int i = 1; i <= l; ++i) for (int j = 1; j <= n; ++j) if (!ans[j][i]) ans[j][i] = gc();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= l; ++j) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}
