#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int kN = 200'000 + 5;
vector<pair<int, long long>> pr1[kN], pr2[kN];
vector<int> g[kN], pf;
int a[kN], b[kN], c[kN], sz[kN], mk[kN];
bool v[kN];

void DfsSz(int x) {
    v[x] = true;
    sz[x] = 1;
    mk[x] = 0;
    pf.push_back(x);
    for (int u : g[x]) {
        if (v[u]) continue;
        DfsSz(u);
        sz[x] += sz[u];
        mk[x] = max(mk[x], sz[u]);
    }
}

void Dfs2(int x, int p, int f, int z, long long sum, vector<pair<int, long long>> *pr) {
    z = max(z, b[x]), sum += a[x];
    pr[f].emplace_back(z, sum);
    for (int u : g[x]) {
        if (u == p || v[u]) continue;
        Dfs2(u, x, f, z, sum, pr);
    }
}

int fw[kN];
vector<pair<int, int>> hist;

void Modify(int p, int v) {
    for (int i = p + 1; i < kN; i += i & -i) {
        fw[i] += v;
        hist.emplace_back(i, v);
    }
}

void Revert() {
    for (auto u : hist) fw[u.first] -= u.second;
    hist.clear();
}

int Query(int p) {
    int res = 0;
    for (int i = p + 1; i > 0; i -= i & -i)
        res += fw[i];
    return res;
}

long long Solve(int x) {
    for (int u : g[x]) {
        if (v[u]) continue;
        Dfs2(u, x, u, b[x], a[x], pr1);
    }
    for (int u : g[x]) {
        if (v[u]) continue;
        Dfs2(u, x, u, -1, 0, pr2);
    }
    vector<pair<int, long long>> fr1, fr2;
    long long res = 0;
    for (int u : g[x]) {
        if (v[u]) continue;
        sort(pr1[u].begin(), pr1[u].end());
        sort(pr2[u].begin(), pr2[u].end());
        for (auto p : pr2[u]) fr2.push_back(p);
        for (auto p : pr1[u]) {
            if (c[p.first] * 2 < p.second) res++;
            fr1.push_back(p);
        }
    }
    // fr1.emplace_back(b[x], a[x]);
    vector<long long> ds;
    sort(fr1.begin(), fr1.end());
    sort(fr2.begin(), fr2.end());
    for (auto &p : fr2) ds.push_back(p.second);
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    long long ares = 0, bres = 0;
    int add = 0;
    for (int i = 0, j = 0; i < fr1.size(); ++i) {
        while (j < fr2.size() && fr2[j].first < fr1[i].first) {
            int p = lower_bound(ds.begin(), ds.end(), fr2[j].second) - ds.begin();
            Modify(p, 1);
            ++j, ++add;
        }
        long long r = 2 * c[fr1[i].first] - fr1[i].second;
        int p = upper_bound(ds.begin(), ds.end(), r) - ds.begin() - 1;
        if (fr1[i].first == b[x]) ares += add - Query(p);
        else bres += add - Query(p);
    }
    Revert();
    for (int u : g[x]) {
        if (v[u]) continue;
        int add = 0;
        for (int i = 0, j = 0; i < pr1[u].size(); ++i) {
            while (j < pr2[u].size() && pr2[u][j].first < pr1[u][i].first) {
                int p = lower_bound(ds.begin(), ds.end(), pr2[u][j].second) - ds.begin();
                Modify(p, 1);
                ++j, ++add;
            }
            long long r = 2 * c[pr1[u][i].first] - pr1[u][i].second;
            int p = upper_bound(ds.begin(), ds.end(), r) - ds.begin() - 1;
            if (pr1[u][i].first == b[x]) ares -= add - Query(p);
            else bres -= add - Query(p);
        }
        Revert();
    }
    res += ares / 2 + bres;
    // printf("Solve x = %d res = %lld ares = %lld bres = %lld\n", x, res, ares, bres);
    // ds.clear();
    // for (auto &p : fr1) ds.push_back(p.second);
    // sort(ds.begin(), ds.end());
    // ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    // add = 0;
    // for (int i = 0, j = 0; i < fr2.size(); ++i) {
    //     while (j < fr1.size() && fr1[j].first < fr2[i].first) {
    //         int p = lower_bound(ds.begin(), ds.end(), fr1[j].second) - ds.begin();
    //         Modify(p, 1);
    //         ++j, ++add;
    //     }
    //     long long r = 2 * c[fr2[i].first] - fr2[i].second;
    //     int p = upper_bound(ds.begin(), ds.end(), r) - ds.begin() - 1;
    //     res += add - Query(p);
    // }
    // Revert();
    // for (int u : g[x]) {
    //     if (v[u]) continue;
    //     add = 0;
    //     for (int i = 0, j = 0; i < pr2[u].size(); ++i) {
    //         while (j < pr1[u].size() && pr1[u][j].first < pr2[u][i].first) {
    //             int p = lower_bound(ds.begin(), ds.end(), pr1[u][j].second) - ds.begin();
    //             Modify(p, 1);
    //             ++j, ++add;
    //         }
    //         long long r = 2 * c[pr2[u][i].first] - pr2[u][i].second;
    //         int p = upper_bound(ds.begin(), ds.end(), r) - ds.begin() - 1;
    //         res -= add - Query(p);
    //     }
    //     Revert();
    // }
    for (int u : g[x]) pr1[u].clear(), pr2[u].clear();
    return res;
}

long long Dfs(int x, int p) {
    pf.clear();
    DfsSz(x);
    int m = pf.size(), c = -1;
    for (int i = 0; i < pf.size(); ++i) {
        int u = pf[i];
        if (max(mk[u], m - sz[u]) * 2 <= m) c = u;
        v[u] = false;
    }
    assert(c != -1);
    v[c] = true;
    long long ans = Solve(c);
    for (int u : g[c]) {
        if (!v[u]) ans += Dfs(u, c);
    }
    return ans;
}

inline int Getchar() {
    const int kBuf = 4096;
    static char buf[kBuf];
    static char *p = buf, *end = buf;
    if (p == end) {
        if ((end = buf + fread(buf, 1, kBuf, stdin)) == buf) return -1;
        p = buf;
    }
    return *p++;
}

inline int ReadInt() {
    char c;
    while (c = Getchar(), !isdigit(c));
    int res = c & 15;
    while (c = Getchar(), isdigit(c)) res = res * 10 + (c & 15);
    return res;
}

int main() {
    int t = ReadInt();
    while (t--) {
        int n = ReadInt();
        vector<pair<int, int>> vv;
        for (int i = 0; i < n; ++i) {
            a[i] = ReadInt();
            vv.emplace_back(a[i], i);
            v[i] = false;
        }
        sort(vv.begin(), vv.end());
        for (int i = 0; i < n; ++i) b[vv[i].second] = i;
        for (int i = 0; i < n; ++i) c[i] = vv[i].first;
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n - 1; ++i) {
            int u = ReadInt();
            int v = ReadInt();
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        printf("%lld\n", Dfs(0, -1));
    }
    return 0;
}
