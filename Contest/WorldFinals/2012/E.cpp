#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int kN = 75;
const int kC = 6;
bitset<kN> adj[kN];
char s[kN + 1];
int ans, g[kC], v[kC], od[kN];

void Dfs(int x, int c, int n, bitset<kN> bs) {
    // printf("x = %d c = %d ans = %d\n", x, c, ans);
    if (c >= ans) return;
    // printf("really c = %d\n", c);
    if (bs.count() == n) {
        ans = c; 
        // printf("ans = %d\n", ans);
        for (int i = 0; i < c; ++i) v[i] = g[i];
        return;
    }
    if (c == kC) return;
    for (int i = x; i < n; ++i) {
        if ((bs | adj[od[i]]) == bs) continue;
        g[c] = od[i];
        Dfs(i + 1, c + 1, n, bs | adj[od[i]]);
    }
}

void Solve(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < kN; ++j) adj[i][j] = false;
    }
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0; j < n; ++j) {
            if (s[j] == '1') adj[i][j] = true;
            else adj[i][j] = false;
        }
        adj[i][i] = true;
    }
    iota(od, od + n, 0);
    random_shuffle(od, od + n);
    ans = kC + 1;
    Dfs(0, 0, n, bitset<kN>());
    assert(ans <= kC);
    printf("%d", ans);
    sort(v, v + ans);
    for (int i = 0; i < ans; ++i) printf(" %d", v[i] + 1);
    puts("");
    // bitset<kN> bs;
    // for (int i = 0; i < ans; ++i) bs |= adj[v[i]];
    // assert(bs.count() == n);
}

int main() {
    int n, tc = 0;
    while (scanf("%d", &n) != EOF) {
        printf("Case %d: ", ++tc);
        Solve(n);
    }
}

