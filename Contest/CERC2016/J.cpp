#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
int a[maxn], no[maxn];
vector<int> g[maxn];
map<int, int> wo[maxn], wr[maxn];
long long dp[maxn], s[maxn];
char st[20];

map<pair<int, int>, vector<int>> path;

long long solve(int l, int r) {
    vector<int> &t = path[make_pair(l, r)];
    int lr = wo[l].find(r) == wo[l].end() ? 1e9 + 1 : wo[l][r];
    int rl = wo[r].find(l) == wo[r].end() ? 1e9 + 1 : wo[r][l];
    int lrl = wr[l].find(r) == wr[l].end() ? 2e9 + 1 : wr[l][r];
    int rlr = wr[r].find(l) == wr[r].end() ? 2e9 + 1 : wr[r][l];
    lr = min(lr, lrl);
    rl = min(rl, rlr);
    if (lr + rl <= lrl && lr + rl <= rlr) {
        long long res = 0;
        for (int i = 0; i < (int)t.size(); ++i)
            res += t[i] ? lr : rl;
        return res;
    }
    lrl = min(lrl, lr + rl);
    rlr = min(rlr, lr + rl);
    int x = 0, y = 0;
    for (int i = 0; i < (int)t.size(); ++i) {
        if (t[i]) ++x;
        else ++y;
    }
    if (y < x) {
        swap(x, y);
        for (int i = 0; i < (int)t.size(); ++i) t[i] ^= 1;
        swap(lr, rl);
        swap(lrl, rlr);
    }
    long long res = 0;
    if (lrl < rlr) {
        set<int> b;
        for (int i = 0; i < (int)t.size(); ++i) 
            if (t[i] == 0) b.insert(i);
        int got = x;
        for (int i = 0; i < (int)t.size(); ++i) {
            if (t[i] == 1) {
                auto it = b.lower_bound(i);
                if (it == b.end()) ;
                else res += lrl, b.erase(it), --got;
            }
        }
        assert((int)b.size() >= got);
        res += rl * 1ll * ((int)b.size() - got) + got * 1ll * rlr;
    } else {
        set<int> b;
        for (int i = 0; i < (int)t.size(); ++i) 
            if (t[i] == 0) b.insert(i);
        int got = x;
        for (int i = (int)t.size() - 1; i >= 0; --i) {
            if (t[i] == 1) {
                auto it = b.lower_bound(i);
                if (it == b.begin()) ;
                else res += rlr, b.erase(prev(it)), got--;
            }
        }
        assert((int)b.size() >= got);
        res += rl * 1ll * ((int)b.size() - got) + 1ll * got * lrl;
    }
    return res;
}

int main() {
    int n, d; scanf("%d%d", &n, &d);
    for (int i = 0; i < d; ++i) scanf("%d", &a[i]), --a[i];
    for (int i = 0; i < d - 1; ++i) {
        path[minmax(a[i], a[i + 1])].push_back(a[i] < a[i + 1]);
    }
    int m; scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int x, y, d; scanf("%d%d%s%d", &x, &y, st, &d);
        --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
        if (st[0] == 'O') {
            if (wo[x].find(y) == wo[x].end())
                wo[x][y] = d;
            else
                wo[x][y] = min(wo[x][y], d);
        } else {
            if (wr[x].find(y) == wr[x].end())
                wr[x][y] = d;
            else 
                wr[x][y] = min(wr[x][y], d);
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end());
        g[i].resize(unique(g[i].begin(), g[i].end()) - g[i].begin());
        for (int j = 0; j < (int)g[i].size(); ++j) {
            int y = g[i][j];
            if (i < y) {
                if (path.find(make_pair(i, y)) == path.end()) continue;
                ans += solve(i, y);
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
