#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const int inf = 1e9 + 1;
bool w[maxn][maxn], v[maxn * maxn];
int a[maxn][maxn], color[maxn * maxn], n, m;
vector<int> g[maxn * maxn];

void add_edge(int x, int y) {
    g[x].push_back(y);
    g[y].push_back(x);
}

long long solve(int s) {
    queue<int> q;
    q.push(s);
    v[s] = true;
    color[s] = 0;

    bool bip = true, cc = true;
    long long sum = 0;
    int sz = 0, c[2] = {0, 0}, z = -1, rv[2] = {inf, inf};
    vector<int> p[2];

    while (!q.empty()) {
        int x = q.front(); q.pop();
        sum += a[x / m][x % m];
        c[color[x]]++;
        rv[color[x]] = min(rv[color[x]], a[x / m][x % m]);
        sz++;
        if (w[x / m][x % m]) {
            if (z == -1) z = color[x];
            else if (z != color[x]) cc = false;
        }
        p[color[x]].push_back(x);
        for (int u : g[x]) {
            if (!v[u]) {
                v[u] = true;
                color[u] = (color[x] ^ 1);
                q.push(u);
            } else {
                if (color[u] == color[x]) bip = false;
            }
        }
    }

    if (sz == 1) return 0;
    if (!bip || !cc) return sum;
    if (z != -1) {
        bool ok = true;
        for (int u : p[z]) ok &= w[u / m][u % m];
        if (ok && c[z ^ 1] == c[z] * 3 + 1) return sum - rv[z ^ 1];
    }
    return sum;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("greetings.in", "r", stdin);
    freopen("greetings.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) scanf("%d", &a[i][j]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == -1) continue;
            if (i > 0 && a[i - 1][j] != -1) add_edge(i * m + j, (i - 1) * m + j);
            if (j > 0 && a[i][j - 1] != -1) add_edge(i * m + j, i * m + (j - 1));
            if (i > 0 && j > 0 && i + 1 < n && j + 1 < m) {
                if (a[i - 1][j] >= 0 && a[i + 1][j] >= 0 && a[i][j - 1] >= 0 && a[i][j + 1] >= 0 &&
                        a[i - 1][j - 1] == -1 && a[i - 1][j + 1] == -1 && a[i + 1][j - 1] == -1 && a[i + 1][j + 1] == -1) {
                    w[i][j] = true;
                }
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < n * m; ++i) {
        if (v[i]) continue;
        ans += solve(i);
    }

    printf("%lld\n", ans);
}
