#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> g[maxn], mem[maxn];
bool v[maxn];
stack<int> st;
int dfn[maxn], low[maxn];
int bcc[maxn], sz, tk;
vector<vector<int>> ans;

void dfs(int x, int p) {
    v[x] = true;
    st.push(x);
    dfn[x] = low[x] = tk++;
    for (const int &u : g[x]) {
        if (u == p) continue;
        if (~dfn[u]) {
            low[x] = min(low[x], dfn[u]);
            continue;
        }
        dfs(u, x);
        low[x] = min(low[x], low[u]);
    }
    if (low[x] == dfn[x]) {
        while (true) {
            int u = st.top(); st.pop();
            bcc[u] = sz;
            if (u == x) break;
        }
        ++sz;
    }
}

#define lock sdjfhio

int fr[maxn];
bitset<maxn> vis;
set<int> memem;
vector<int> pa3;
bool lock;

void mdfs(int now, int pa, int start) {
    if (lock) return;
    // cout << "mdfs " << now << " pa " << pa << endl;
    pa3.push_back(now);
    if (memem.find(now) != memem.end()) {
        lock = true;
        return;
    }
    vis[now] = true;
    for (int i : g[now]) {
        if (bcc[i] != bcc[now]) continue;
        if (i == pa) continue;
        if (vis[i]) continue;
        if (lock) return;
        // cout << "i : " << i << endl;
        if (memem.find(i) != memem.end() && i != start) {
            lock = true;
            pa3.push_back(i);
        } else if (i != start) {
            mdfs(i, now, start);
        }
    }
    if (!lock) pa3.pop_back();
}

void go(int bid) {
    if (mem[bid].size() == 1u) return;
    // cout << "go: " << bid << endl;
    for (int i : mem[bid]) fr[i] = 0, vis[i] = false;
    int now = mem[bid][0];
    vis[now] = true;
    vector<int> lmem;
    while (true) {
        // cout << "now: " << now << endl;
        for (int i : g[now]) {
            if (i == fr[now]) continue;
            if (bcc[now] != bcc[i]) continue;
            if (vis[i]) {
                lmem.push_back(i);
                // cout << "lmem push " << i << endl;
                int x = now;
                do {
                    lmem.push_back(x);
                    // cout << "lmem push " << x << endl;
                    x = fr[x];
                } while (x != i);
                break;
            }
            fr[i] = now;
            now = i;
            vis[now] = true;
            break;
        }
        if (lmem.size()) break;
    }
    memem.clear(); pa3.clear(); lock = false;
    for (int i : mem[bid]) vis[i] = false;
    for (int i : lmem) memem.insert(i);
    for (int i = 0; i < int(lmem.size()); ++i) {
        int pre = (i == 0 ? int(lmem.size()) - 1 : i - 1);
        int bak = (i == int(lmem.size()) - 1 ? 0 : i + 1);
        for (int j : g[lmem[i]]) {
            if (j == lmem[pre]) continue;
            if (j == lmem[bak]) continue;
            if (bcc[j] != bcc[i]) continue;
            if (pa3.size()) continue;
            pa3.push_back(lmem[i]);
            // cout << "start to go " << lmem[i] << " to " << j << endl;
            mdfs(j, lmem[i], lmem[i]);
            if (pa3.size() == 1u) {
                pa3.clear(); 
                continue;
            }
            ans.push_back(pa3);
            ans.push_back(vector<int>());
            for (int z = i; ; ++z) {
                if (z == int(lmem.size())) z = 0;
                ans.back().push_back(lmem[z]);
                if (ans.back().back() == pa3.back()) break;
            }
            ans.push_back(vector<int>());
            for (int z = i; ; --z) {
                if (z < 0) z = int(lmem.size()) - 1;
                ans.back().push_back(lmem[z]);
                if (ans.back().back() == pa3.back()) break;
            }
        }
    }
}

int main() {
    freopen("grand.in", "r", stdin);
    freopen("grand.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < m; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            --x, --y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        for (int i = 0; i < n; ++i) {
            v[i] = false;
            dfn[i] = -1;
        }
        tk = sz = 0;
        for (int i = 0; i < n; ++i) {
            if (v[i]) continue;
            dfs(i, -1);
        }
        for (int i = 0; i < n; ++i) mem[i].clear();
        for (int i = 0; i < n; ++i) mem[bcc[i]].push_back(i);
        ans.clear();
        for (int i = 0; i < sz; ++i) {
            if (ans.size()) continue;
            go(i);
        }
        if (ans.empty()) printf("-1\n");
        else {
            printf("%d %d\n", ans[0][0] + 1, ans[0].back() + 1);
            for (int i = 0; i < 3; ++i) {
                printf("%d", int(ans[i].size()));
                for (int z : ans[i]) printf(" %d", z + 1);
                puts("");
            }
        }
    }
    return 0;
}
