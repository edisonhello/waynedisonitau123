#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const int maxq = 3e5 + 5;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int n, fa[maxn * maxn], ps[maxn][maxn], rep[maxn][maxn], sz[maxn * maxn];
int ans[maxq], r[maxq], c[maxq], x[maxq], y[maxq], ok[maxq];
char s[maxn][maxn];

int query(int u, int d, int l, int r) {
    return ps[d][r] - ps[d][l - 1] - ps[u - 1][r] + ps[u - 1][l - 1];
}

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (sz[x] > sz[y]) swap(x, y);
    fa[x] = y;
    sz[y] += sz[x];
}

void solve(int l, int r, const vector<int> &qr) {
    if ((int)qr.size() == 0) return;
    if (l > r) return;
    int m = (l + r + 1) / 2;
    int k = 0;
    // printf("l = %d r = %d check m = %d\n", l, r, m);
    // for (int i = 0; i < (int)qr.size(); ++i) printf("%d ", qr[i]); puts("");
    for (int i = 1 + m; i <= n - m; ++i) {
        for (int j = 1 + m; j <= n - m; ++j) {
            rep[i][j] = -1;
            if (query(i - m, i + m, j - m, j + m) == 0) 
                rep[i][j] = k++;
        }
    }
    for (int i = 0; i < k; ++i) fa[i] = i, sz[i] = 1;
    for (int i = 1 + m; i <= n - m; ++i) {
        for (int j = 1 + m; j <= n - m; ++j) {
            if (rep[i][j] == -1) continue;
            // printf("alive i = %d j = %d\n", i, j);
            for (int p = 0; p < 4; ++p) {
                int x = i + dx[p], y = j + dy[p];
                if (x >= 1 + m && x <= n - m && y >= 1 + m && y <= n - m) {
                    if (rep[x][y] != -1) {
                        merge(rep[i][j], rep[x][y]);
                    }
                }
            }
        }
    }
    vector<int> lq, rq;
    for (int i = 0; i < (int)qr.size(); ++i) {
        int j = qr[i];
        if (::r[j] < 1 + m || ::r[j] > n - m) {
            lq.push_back(j);
            continue;
        }
        if (::c[j] < 1 + m || ::c[j] > n - m) {
            lq.push_back(j);
            continue;
        }
        if (::x[j] < 1 + m || ::y[j] > n - m) {
            lq.push_back(j);
            continue;
        }
        if (::y[j] < 1 + m || ::y[j] > n - m) {
            lq.push_back(j);
            continue;
        }
        if (rep[::r[j]][::c[j]] == -1 || rep[::x[j]][::y[j]] == -1) {
            lq.push_back(j);
            continue;
        }
        if (find(rep[::r[j]][::c[j]]) == find(rep[::x[j]][::y[j]])) {
            ok[j]++;
            rq.push_back(j);
        } else {
            lq.push_back(j);
        }
    }
    if (l == r) {
        for (int i = 0; i < (int)qr.size(); ++i) {
            if (ok[qr[i]] > 0)
                ans[qr[i]] = l * 2 + 1;
        }
        return;
    }
    solve(l, m - 1, lq);
    solve(m, r, rq);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + (s[i][j] == '#');
    }
    int q; scanf("%d", &q);
    vector<int> qr;
    for (int i = 0; i < q; ++i) {
        scanf("%d%d%d%d", &r[i], &c[i], &x[i], &y[i]);
        qr.push_back(i);
    }
    solve(0, n / 2, qr);
    for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
    return 0;
}
