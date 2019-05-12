#include <bits/stdc++.h>
using namespace std;

int mn[100005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, s; cin >> n >> s;
    for (int i = 1; i <= n; ++i) mn[i] = 1000000000;
    for (int i = 1; i <= n; ++i) {
        int a, b; cin >> a >> b;
        mn[a] = min(mn[a], b);
    }
    sort(mn + 1, mn + 1 + n);
    for (int i = 1; i <= n; ++i) {
        if (s - mn[i] >= 0) {
            s -= mn[i];
        } else {
            cout << i - 1 << endl;
            exit(0);
        }
    }
    cout << n << endl;
}

