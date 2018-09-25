

#include <bits/stdc++.h>
using namespace std;

int ans, n;

void dfs(int x, int last, long long s, long long p) {
    int rem = n - x;
    if (p - s > rem) return;
    if (x && p - s == rem) {
        ++ans;
    }
    if (x == n) return;
    for (int i = last; i <= n; ++i) dfs(x + 1, i, s + i, p * i);
}

int main() {
#ifndef LOCAL
    freopen("sump.in", "r", stdin);
    freopen("sump.out", "w", stdout);
#endif
    cin >> n;
    vector<int> v(n);
    dfs(0, 2, 0, 1);
    cout << ans << endl;
}
