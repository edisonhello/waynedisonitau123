#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 2000 + 5;
vector<tuple<int, int, int>> g[maxn];
vector<int> edge[maxn];
int dfn[maxn], low[maxn], tk; 
int bcid[maxn], bsz;
stack<int> st;
vector<vector<int>> vv;
map<pair<int, int>, int> etobc;
int bcec[maxn];
bool bridge[maxn], ins[maxn];
 
void dfs(int x, int p, int e) {
    dfn[x] = low[x] = tk++;
    // st.emplace(minmax(x, p));
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = get<0>(g[x][i]);
        if (u == p) continue;
        int ee = get<2>(g[x][i]);
        if (!ins[ee]) {
            ins[ee] = true;
            st.push(ee);
        }
 
        if (dfn[u] == -1) {
            dfs(u, x, ee);
            low[x] = min(low[x], low[u]);
            if (low[u] == dfn[x]) {
                while (!st.empty()) {
                    int eee = st.top(); st.pop();
                    bcid[eee] = bsz;
                    if (eee == ee) break;
                }
                bsz++;
            }
            
        } else {
            low[x] = min(low[x], dfn[u]);
        }
    }
 
    if (low[x] == dfn[x]) {
        if (e != -1)
            bridge[e] = true;
    };
}
 
vector<int> gk;
 
void dfs(int i, int s, int pf, int val, int k) {
    if ((int)gk.size() >= k) return;
    if (i == (int)vv.size()) {
        // printf("s = %d\n", s);
        gk.push_back(s);
        return;
    }
 
    pf -= vv[i][0];
    // printf("i = %d pf = %d val = %d\n", i, pf, val);
    for (int j = 0; j < (int)vv[i].size(); ++j) {
        if (s + vv[i][j] + pf >= val) break;
        dfs(i + 1, s + vv[i][j], pf, val, k);
    }
}
 
bool check(int val, int k) {
    gk.clear();
    int pf = 0;
    for (int i = 0; i < (int)vv.size(); ++i)
        pf += vv[i][0];
    dfs(0, 0, pf, val, k);
    return gk.size() < k;
}
 
int main() {
    int n, m, tc = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < m; ++i) {
            int x, y, z; scanf("%d%d%d", &x, &y, &z);
            --x, --y;
            g[x].emplace_back(y, z, i);
            g[y].emplace_back(x, z, i);
        }
 
        for (int i = 0; i < n; ++i) dfn[i] = -1;
        tk = bsz = 0;
        while (!st.empty()) st.pop();
        for (int i = 0; i < m; ++i) bridge[i] = ins[i] = false;
        dfs(0, -1, -1);
 
        for (int i = 0; i < m; ++i) edge[i].clear();
 
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < (int)g[i].size(); ++j) {
                // int u = g[i][j], w = g[i][j].second;
                int u, w, e; tie(u, w, e) = g[i][j];
                if (i > u) continue;
                // auto it = etobc.find(minmax(i, u));
                // printf("edge %d <-> %d bcid %d bcec %d\n", i, u, it->second, bcec[it->second]);
                if (bridge[e]) sum += w;
                else edge[bcid[e]].push_back(w);
                /* if (bcec[it->second] == 1) sum += w;
                else {
                    edge[it->second].push_back(w);
                } */
            }
        }
 
        // for (int i = 0; i < n; ++i) printf("%d ", bcid[i]); puts("");
 
        vv.clear();
        long long way = 1;
 
        for (int i = 0; i < bsz; ++i) {
            if (edge[i].empty()) continue;
            // printf("edge[%d].size() = %d\n", i, (int)edge[i].size());
            int s = accumulate(edge[i].begin(), edge[i].end(), 0);
            vector<int> v;
            for (int j = 0; j < (int)edge[i].size(); ++j)
                v.push_back(s - edge[i][j]);
            sort(v.begin(), v.end());
            vv.push_back(v);
            way = way * (int)v.size();
            way = min(way, 1000000000ll);
            // sort(edge[i].begin(), edge[i].end());
            // v.push_back(*max_element(edge[i].begin(), edge[i].end())); 
        }
 
        /* for (int i = 0; i < (int)vv.size(); ++i) {
            for (int j = 0; j < (int)vv[i].size(); ++j)
                printf("%d ", vv[i][j]);
            puts("");
        } */
 
        int k; scanf("%d", &k);
        // sort(v.begin(), v.end());
        // priority_queue<pair<long long, 
        int kx = 0;
        for (int d = 30; d >= 0; --d) {
            if (kx + (1 << d) > 2000000000) continue;
            if (check(kx + (1 << d), k))
                kx += (1 << d);
        }
 
        check(kx, k);
        vector<int> vs;
        if (way >= k) {
            for (int i = 0; i < (int)gk.size(); ++i)
                vs.push_back(gk[i] + sum);
            while (vs.size() < k) vs.push_back(kx + sum);
            sort(vs.begin(), vs.end());
        } else {
            for (int i = 0; i < (int)gk.size(); ++i)
                vs.push_back(gk[i] + sum);
            sort(vs.begin(), vs.end());
            while (vs.size() < k) vs.push_back(0);
        }
 
 
        unsigned ans = 0;
        for (int i = 0; i < k; ++i) ans += unsigned(i + 1) * unsigned(vs[i]);
        printf("Case #%d: %u\n", ++tc, ans);
    }
    return 0;
}
