#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> g[maxn], use, hole[maxn];
bool has[maxn], v[maxn], tk[maxn];
int ans, p[maxn];

void dfs(int x, int p) {
    v[x] = true;
    use.push_back(x);
    for (const int &u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
        if (!tk[u] && !tk[x]) {
            tk[x] = true;
            tk[u] = true;
            ++ans;
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("hidden.in", "r", stdin);
    freopen("hidden.out", "w", stdout);
#endif
    int n; scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &p[i]); --p[i];
        if (p[i] < 0) continue;
        g[p[i]].push_back(i);
        has[i] = true;
    }
    vector<int> root;
    for (int i = 0; i < n; ++i) {
        if (has[i]) continue;
        if (v[i]) continue;
        use.clear();
        dfs(i, -1);
        for (int j = 0; j < (int)use.size(); ++j) {
            int x = use[j];
            if (!tk[x]) hole[i].push_back(x);
        }
        root.push_back(i);
    }
    // printf("%d\n", ans);
    set<int> now;
    vector<int> ins;
    for (int i = 0; i < (int)hole[0].size(); ++i) now.insert(hole[0][i]);
    for (int i = 0; i < (int)root.size(); ++i) {
        int x = root[i];
        if (tk[x] && x != 0) {
            p[x] = 0;
            for (int j = 0; j < (int)hole[x].size(); ++j) now.insert(hole[x][j]);
        } else {
            if (x == 0) continue;
            ins.push_back(x);
        }
    }
    sort(ins.begin(), ins.end(), [&](int i, int j) { return hole[i].size() > hole[j].size(); });
    for (int i = 0; i < (int)ins.size(); ++i) {
        int x = ins[i];
        bool us = false;
        if (now.size() == 0) p[x] = 0;
        else p[x] = *now.begin(), now.erase(p[x]), ++ans, us = true;
        for (int j = 0; j < (int)hole[x].size(); ++j) {
            if (us && hole[x][j] == x) continue;
            now.insert(hole[x][j]);
        }
    }
    printf("%d\n", ans);
    for (int i = 1; i < n; ++i) printf("%d ", p[i] + 1); puts("");
    return 0;
}
