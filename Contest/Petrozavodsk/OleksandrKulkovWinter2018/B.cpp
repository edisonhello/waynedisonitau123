#include <bits/stdc++.h>
using namespace std;
int n;
int f[10], g[10];

void dfs2(int now) {
    if (now == n) solve();
    else for (int i = 0; i < n; ++i) {
        g[now] = i;
        dfs2(now + 1);
    }
}

void dfs1(int now) {
    if (now == n) dfs2();
    else for (int i = 0; i < n; ++i) {
        f[now] = i;
        dfs1(now + 1);
    }
}

int main() {
    cin >> n;
    dfs1(0);
}
