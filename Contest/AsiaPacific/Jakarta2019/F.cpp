#include <bits/stdc++.h>
using namespace std;

const int maxn = 4005;

#define Hash array<int, 3>
const Hash mod{1000000007, 1000000009, 1000000123};

Hash operator * (const Hash v, int x) {
    return Hash{1ll * v[0] * x % mod[0], 1ll * v[1] * x % mod[1], 1ll * v[2] * x % mod[2]};
}
Hash operator * (const Hash v, const Hash w) {
    return Hash{1ll * v[0] * w[0] % mod[0], 1ll * v[1] * w[1] % mod[1], 1ll * v[2] * w[2] % mod[2]};
}
Hash operator + (const Hash a, const Hash b) {
    return Hash{a[0] + b[0] >= mod[0] ? a[0] + b[0] - mod[0] : a[0] + b[0],
                a[1] + b[1] >= mod[1] ? a[1] + b[1] - mod[1] : a[1] + b[1],
                a[2] + b[2] >= mod[2] ? a[2] + b[2] - mod[2] : a[2] + b[2]};
}
Hash operator ^ (const Hash a, const Hash b) {
    return Hash{(a[0] ^ b[0]) >= mod[0] ? (a[0] ^ b[0]) - mod[0] : a[0] ^ b[0],
                (a[1] ^ b[1]) >= mod[1] ? (a[1] ^ b[1]) - mod[1] : a[1] ^ b[1],
                (a[2] ^ b[2]) >= mod[2] ? (a[2] ^ b[2]) - mod[2] : a[2] ^ b[2]};
}

vector<int> g[maxn];

namespace solve {

int sz[maxn], mxch[maxn];

pair<Hash, int> make_hash(int now, int pa, int ROOT) {
    Hash v = {7122, 87, 7902131};
    int sz = 1;

    vector<pair<Hash, int>> hashes;
    for (int i : g[now]) if (i != pa && i != ROOT) {
        hashes.push_back(make_hash(i, now, ROOT));
    }

    sort(hashes.begin(), hashes.end());

    Hash base = {123, 345, 567};
    for (int i = 0; i < (int)hashes.size(); ++i) {
        sz += hashes[i].second;
        v = v * sz * base + (hashes[i].first ^ Hash{0x0eadbeef, 0x0012abcd, 0x01227122});
    }

    return make_pair(v, sz);
}

void dfs(int now, int pa, vector<int> &part) {
    part.push_back(now);

    sz[now] = 1;
    for (int i : g[now]) if (i != pa) {
        dfs(i, now, part);
        sz[now] += sz[i];
        if (sz[i] > sz[mxch[now]]) mxch[now] = i;
    }
}

int solve(int root) {
    vector<vector<int>> part(g[root].size());
    for (int i = 0; i < (int)g[root].size(); ++i) dfs(root, g[root][i], part[i]);
    int ssz = sz[g[root][0]];
    for (int i : g[root]) if (ssz != sz[i]) return -1;

    vector<vector<int>> cens(g[root].size());
    for (int i = 0; i < (int)g[root].size(); ++i) {
        for (int j : part[i]) if (max(sz[mxch[j]], sz[g[root][i]] - sz[j]) <= sz[g[root][i]] / 2) {
            cens[i].push_back(j);
        }
    }

    for (int i = 1; i < (int)g[root].size(); ++i) {
        bool match = false;
        for (int i1 : cens[i - 1]) for (int i2 : cens[i]) {
            if (make_hash(i1, 0, root) == make_hash(i2, 0, root)) {
                match = true;
                break;
            }
        }
        if (!match) return -1;
    }

    return g[root].size();
}


}

int sz[maxn], mxch[maxn];

void dfs(int now, int pa) {
    sz[now] = 1;
    for (int i : g[now]) if (i != pa) {
        dfs(i, now);
        sz[now] += sz[i];
        if (sz[i] > sz[mxch[now]]) mxch[now] = i;
    }
}

int main() {
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);

    int ans = -1;
    for (int i = 1; i <= n; ++i) if (max(n - sz[i], sz[mxch[i]]) <= n / 2) {
        ans = max(ans, solve::solve(i));    
    }
    cout << ans << endl;
}
