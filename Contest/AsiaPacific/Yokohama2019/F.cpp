#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
const int kMod = 1'000'000'000 + 7;
long long a[kN], b[kN], d[kN], s[kN];
int n, c[kN], e[kN], deg[kN], fa[kN][20], dep[kN], uf[kN], jt[kN], rv[kN];
bool v[kN], cy[kN], gd[kN];
long long ps[kN], ss[kN];
vector<int> g[kN], nd[kN];
vector<int> ck[kN];
map<long long, vector<int>> cc[kN];

void Dfs(int x, int p) {
    fa[x][0] = p;
    dep[x] = ~p ? dep[p] + 1 : 0;
    for (int i = 1; (1 << i) <= dep[x]; ++i)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (int u : g[x]) {
        if (cy[u] || u == p) continue;
        s[u] = s[x] + d[x];
        Dfs(u, x);
    }
}

int Jump(int x, int k) {
    for (int i = 19; i >= 0; --i) {
        if (k >> i & 1) x = fa[x][i];
    }
    return x;
}

bool IsParent(int x, int y) {
    if (dep[x] < dep[y]) return false;
    return Jump(x, dep[x] - dep[y]) == y;
}

int Find(int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
}

void Merge(int x, int y) {
    uf[Find(x)] = Find(y);
}

void Build(int r) {
    printf("Build r = %d\n", r);
    queue<int> q;
    for (int i : nd[r]) ++deg[i];
    for (int i : nd[r]) {
        if (deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int x = q.front(); q.pop();
        v[x] = true;
        if (x == n) continue;
        if (--deg[e[x]] == 0) q.push(e[x]);
    }
    vector<int> cyc;
    vector<long long> pr;
    int z = -1;
    for (int i : nd[r]) if (!v[i]) z = i;
    assert(z != -1);
    long long sc = 0;
    for (int x = z; ; ) {
        printf("x = %d sc = %lld\n", x, sc);
        rv[x] = cyc.size();
        ps[x] = sc;
        cyc.push_back(x);
        pr.push_back(d[x]);
        cy[x] = true;
        sc += d[x];
        x = e[x];
        if (x == z) break;
    }
    puts("hello");
    if (cyc.empty()) {
        puts("jizz");
        gd[r] = true;
        Dfs(n, -1);
    } else {
        ss[r] = sc;
        for (int i : cyc) ps[i] %= sc;
        for (int i : cyc) {
            long long gg = ((a[i] - ps[i]) % sc + sc) % sc;
            cc[r][gg].push_back(rv[i]);
        }
        for (auto &it : cc[r]) {
            sort(it.second.begin(), it.second.end());
        }
        ck[r] = cyc;
        for (int i = 0; i < cyc.size(); ++i) Dfs(cyc[i], -1);
    }
}

int main() {
    long long x0;
    scanf("%d%lld", &n, &x0);
    for (int i = 0; i < n; ++i) uf[i] = i;
    bool ok = false;
    for (int i = 0; i < n; ++i) {
        scanf("%lld%lld%d%lld%d", &a[i], &b[i], &c[i], &d[i], &e[i]);
        --c[i], --e[i];
        if (c[i] == n || e[i] == n) ok = true;
        Merge(i, e[i]);
        g[e[i]].push_back(i);
    }
    for (int i = 0; i < n; ++i) nd[Find(i)].push_back(i);
    if (!ok) {
        puts("-1");
        return 0;
    }
    for (int i = 0; i < n; ++i) deg[e[i]]++;
    for (int i = 0; i < n; ++i) if (Find(i) == i) Build(i);
    int cur = 0, ans = 0;
    long long x = x0;
    while (true) {
        printf("cur = %d x = %lld ans = %d\n", cur, x, ans);
        if (cur == n) break;
        int z = cur, jj = -1, tz = -1;
        while (z != -1) {
            if (a[z] == x) {
                jj = z;
                break;
            }
            if (fa[z][0] == -1) {
                tz = z;
                break;
            }
            x += d[cur];
            cur = fa[cur][0];
            (ans += 1) %= kMod;
        }
        if (jj != -1) {
            if (jt[jj]) {
                puts("-1");
                return 0;
            }
            cur = jj;
            ++jt[cur];
            x = a[cur];
            x += b[cur];
            cur = c[cur];
            (ans += 1) %= kMod;
            cout << "case1 jump to " << cur << endl;
        } else {
            cur = tz;
            int r = Find(cur);
            cout << cur << endl;
            long long qr = ((x - ps[cur]) % ss[r] + ss[r]) % ss[r];
            cout << "cur = " << cur << " x = " << x << endl;
            cout << "qr = " << qr << endl;
            if (gd[r]) {
                (ans += dep[cur]) %= kMod;
                continue;
            }
            auto it = lower_bound(cc[r][qr].begin(), cc[r][qr].end(), rv[cur]);
            if (it != cc[r][qr].end()) {
                jj = ck[r][*it];
            } else {
                if (cc[r][qr].size() != 0) jj = ck[0][cc[r][qr][0]];
            }
            if (jj == -1) {
                puts("-1");
                return 0;
            }
            if (jt[jj]) {
                puts("-1");
                return 0;
            }
            ans += ((a[jj] - x) / ss[r]) * ck[r].size() + (rv[jj] - rv[cur] + ck[r].size()) % ck[r].size();
            cout << "to cur = " << cur << " jj = " << jj << endl;
            cur = jj;
            ++jt[cur];
            (ans += 1) %= kMod;
            x = a[cur];
            x += b[cur];
            cur = c[cur];
            (ans += 1) %= kMod;
        }
    }
    printf("%d\n", ans);
    return 0;
}
