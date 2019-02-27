#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const int maxq = 3e5 + 5;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int n, fa[maxn * maxn], ps[maxn][maxn], rep[maxn][maxn], sz[maxn * maxn], fat[maxn][maxn];
int ans[maxq], r[maxq], c[maxq], x[maxq], y[maxq], ok[maxq];
char s[maxn][maxn];
vector<pair<int, int>> rad[maxn];

int query(int u, int d, int l, int r) {
    // u = max(u, 1); l = max(l, 1);
    // d = min(u, n); r = min(r, n);
    return ps[d][r] - ps[d][l - 1] - ps[u - 1][r] + ps[u - 1][l - 1];
}

int find(int x) {
    if (x == fa[x]) return x;
    return find(fa[x]);
}

void merge(int x, int y, stack<pair<int*, int>> &hist) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (sz[x] > sz[y]) swap(x, y);
    hist.emplace(&fa[x], fa[x]);
    hist.emplace(&sz[y], sz[y]);
    fa[x] = y;
    sz[y] += sz[x];
}


void solve(int l, int r, const vector<int> &qr) {
    if (qr.empty()) return;
    // cout << "solve " << l << " " << r << " have ";
    // for (int i : qr) cout << i << " , ";
    int m = (l + r + 1) >> 1;
    // cout << " m = " << m << endl;
    stack<pair<int*, int>> hist;
    for (int f = m, x, y; f <= r; ++f) {
        for (auto &p : rad[f]) {
            tie(x, y) = p;
            if (x > 1 && fat[x - 1][y] != -1 && fat[x - 1][y] >= fat[x][y]) merge(rep[x - 1][y], rep[x][y], hist);
            if (y > 1 && fat[x][y - 1] != -1 && fat[x][y - 1] >= fat[x][y]) merge(rep[x][y - 1], rep[x][y], hist);
            if (x < n && fat[x + 1][y] != -1 && fat[x + 1][y] >= fat[x][y]) merge(rep[x + 1][y], rep[x][y], hist);
            if (y < n && fat[x][y + 1] != -1 && fat[x][y + 1] >= fat[x][y]) merge(rep[x][y + 1], rep[x][y], hist);
        }
    }
    vector<int> vql, vqr;
    for (int i : qr) {
        if (find(rep[::r[i]][::c[i]]) == find(rep[::x[i]][::y[i]])) {
            ans[i] = m * 2 + 1;
            vqr.push_back(i);
            // cout << i << " fit in " << m << " , ans = " << ans[i] << endl;
        } else {
            vql.push_back(i);
        }
    }
    if (l == r) return;
    while (hist.size()) {
        *hist.top().first = hist.top().second;
        hist.pop();
    }
    solve(m, r, vqr);
    for (int f = m, x, y; f <= r; ++f) {
        for (auto &p : rad[f]) {
            tie(x, y) = p;
            if (x > 1 && fat[x - 1][y] != -1 && fat[x - 1][y] >= fat[x][y]) merge(rep[x - 1][y], rep[x][y], hist);
            if (y > 1 && fat[x][y - 1] != -1 && fat[x][y - 1] >= fat[x][y]) merge(rep[x][y - 1], rep[x][y], hist);
            if (x < n && fat[x + 1][y] != -1 && fat[x + 1][y] >= fat[x][y]) merge(rep[x + 1][y], rep[x][y], hist);
            if (y < n && fat[x][y + 1] != -1 && fat[x][y + 1] >= fat[x][y]) merge(rep[x][y + 1], rep[x][y], hist);
        }
    }
    solve(l, m - 1, vql);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + (s[i][j] == '#');
    }
    int k = 0;
    for (int i = 0; i < maxn * maxn; ++i) fa[i] = i, sz[i] = 1;
    memset(rep, -1, sizeof(rep));
    memset(fat, -1, sizeof(fat));
    stack<pair<int*, int>> hist;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i][j] == '#') continue;
            rep[i][j] = k++;
            if (i - 1 >= 1 && rep[i - 1][j] >= 0) merge(rep[i - 1][j], rep[i][j], hist);
            if (j - 1 >= 1 && rep[i][j - 1] >= 0) merge(rep[i][j - 1], rep[i][j], hist);
            int L = 0, R = n / 2;
            while (L < R) {
                int M = (L + R + 1) >> 1;
                if (i - M >= 1 && i + M <= n && j - M >= 1 && j + M <= n && query(i - M, i + M , j - M, j + M) == 0) L = M;
                else R = M - 1;
            }
            fat[i][j] = L;
            // cout << "fat of " << i << " " << j << " = " << fat[i][j] << endl;
            rad[L].emplace_back(i, j);
        }
    }
    int q; scanf("%d", &q);
    vector<int> qr;
    for (int i = 0; i < q; ++i) {
        scanf("%d%d%d%d", &r[i], &c[i], &x[i], &y[i]);
        if (find(rep[r[i]][c[i]]) != find(rep[x[i]][y[i]])) continue;
        qr.push_back(i);
    }
    for (int i = 0; i < maxn * maxn; ++i) fa[i] = i, sz[i] = 1;
    solve(0, n / 2, qr);
    for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
    return 0;
}
