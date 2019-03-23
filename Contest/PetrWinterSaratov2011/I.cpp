#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int sz[maxn], mx[maxn], dep[maxn], a[maxn], b[maxn], fa[maxn];
map<int, pair<int, int>> sub[maxn];
vector<int> g[maxn], pass;
char s[maxn];
bool v[maxn];

void center(int x) {
    pass.push_back(x);
    v[x] = true;
    sz[x] = 1;
    mx[x] = 0;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (v[u]) continue;
        center(u);
        sz[x] += sz[u];
        mx[x] = max(mx[x], sz[u]);
    }
}

void dfs2(int x, int s, int f = -1) {
    v[x] = true;
    s += a[x];
    b[x] = s;
    fa[x] = f;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        int tf = f == -1 ? u : f;
        if (!v[u]) {
            dep[u] = dep[x] + 1;
            dfs2(u, s, tf);
        }
    }
}

tuple<int, int, int> solve(int x) {
    dep[x] = 0;
    dfs2(x, 0);
    int m = (int)pass.size();
    int res = -1, p = -1, q = -1;
    for (int i = 0; i < m; ++i) {
        int u = pass[i];
        if (b[u] == 0) {
            if (dep[u] > res) {
                res = dep[u];
                p = x;
                q = u;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        int u = pass[i];
        if (fa[u] >= 0) 
            sub[fa[u]][b[u]] = max(sub[fa[u]][b[u]], make_pair(dep[u], u));
    }
    map<int, pair<int, int>> pref;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        for (auto it : sub[g[x][i]]) {
            if (pref.find(a[x] - it.first) != pref.end()) {
                int value = it.second.first + pref[a[x] - it.first].first;
                if (value > res) {
                    res = value;
                    p = it.second.second;
                    q = pref[a[x] - it.first].second;
                }
            }
        }
        for (auto it : sub[g[x][i]]) 
            pref[it.first] = max(pref[it.first], it.second);
    }
    pref.clear();
    for (int i = (int)g[x].size() - 1; i >= 0; --i) {
        for (auto it : sub[g[x][i]]) {
            if (pref.find(a[x] - it.first) != pref.end()) {
                int value = it.second.first + pref[a[x] - it.first].first;
                if (value > res) {
                    res = value;
                    p = it.second.second;
                    q = pref[a[x] - it.first].second;
                }
            }
        }
        for (auto it : sub[g[x][i]]) 
            pref[it.first] = max(pref[it.first], it.second);
    }
    for (int i = 0; i < m; ++i) {
        int u = pass[i];
        if (fa[u] >= 0)
            sub[fa[u]].clear();
    }
    return make_tuple(res, p, q);
}

tuple<int, int, int> dfs(int x) {
    pass.clear();
    center(x);
    int m = (int)pass.size(), c = -1;
    for (int i = 0; i < m; ++i) {
        int bg = max(m - sz[pass[i]], mx[pass[i]]);
        if (bg * 2 <= m) c = pass[i];
        v[pass[i]] = false;
    }
    assert(c >= 0);
    tuple<int, int, int> res = solve(c); 
    for (int i = 0; i < m; ++i) v[pass[i]] = false;
    v[c] = true;
    for (int i = 0; i < (int)g[c].size(); ++i) {
        int u = g[c][i];
        if (!v[u]) res = max(res, dfs(u));
    }
    return res;
}

vector<int> fin;

void dfs3(int x, int p, int y) {
    fa[x] = p;
    if (y == x) {
        while (y >= 0) {
            fin.push_back(y);
            y = fa[y];
        }
        return;
    }
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u != p) dfs3(u, x, y);
    }
}

void print(int x, int y) {
    dfs3(x, -1, y);
    printf("%d\n", (int)fin.size());
    for (int i = 0; i < (int)fin.size(); ++i)
        printf("%d%c", fin[i] + 1, " \n"[i + 1 == (int)fin.size()]);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("shoes.in", "r", stdin);
    freopen("shoes.out", "w", stdout);
#endif
    int n; scanf("%d", &n);
    scanf("%s", s);
    for (int i = 0; i < n - 1; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'L') a[i] = 1;
        else a[i] = -1;
    }
    tuple<int, int, int> ans = dfs(0);
    print(get<1>(ans), get<2>(ans));
}
