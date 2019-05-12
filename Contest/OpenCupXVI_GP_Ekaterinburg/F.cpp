#include <bits/stdc++.h>
using namespace std;

vector<int> G[355], iG[355], tp, cG[355];
bitset<355> vis;
int bel[355], djs[355];
vector<int> mem[355];
int ind[355];
bitset<355> cango[355];

void dfs1(int now) {
    vis[now] = 1;
    for (int i : G[now]) if (!vis[i]) dfs1(i);
    tp.push_back(now);
}

void dfs2(int now, int cc) {
    // cerr << "dfs2 " << now << " " << cc << '\n';
    vis[now] = 1;
    bel[now] = cc;
    mem[cc].push_back(now);
    for (int i : iG[now]) if (!vis[i]) dfs2(i, cc);
}

int F(int x) { return djs[x] == x ? x : x = F(djs[x]); }
void U(int x, int y) { djs[F(x)] = F(y); }
bool C(int x, int y) { return F(x) == F(y); }

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) djs[i] = i;
    while (m--) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        iG[v].push_back(u);
        U(u, v);
    }
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs1(i);
    reverse(tp.begin(), tp.end());
    vis.reset();
    int cc = 0; 
    for (int i : tp) if (!vis[i]) dfs2(i, ++cc);
    vector<int> cctp;
    for (int i = 0, j; i < (int)tp.size(); i = j) {
        for (j = i; j < (int)tp.size(); ++j) 
            if (bel[tp[i]] != bel[tp[j]])
                break;
        cctp.push_back(bel[tp[i]]);
        // cerr << "cctp : " << bel[tp[i]] << endl;
    }
    vector<int> nxt(cc + 5, -1);
    for (int i = 0; i < (int)cctp.size() - 1; ++i) nxt[cctp[i]] = cctp[i + 1];
    vector<pair<int, int>> ans;
    set<pair<int, int>> used;
    for (int i = 1; i <= n; ++i) {
        for (int j : G[i]) {
            // if (nxt[bel[i]] != bel[j]) continue;
            if (bel[i] == bel[j]) continue;
            if (used.count(make_pair(bel[i], bel[j]))) continue;
            used.insert(make_pair(bel[i], bel[j]));
            cG[bel[i]].push_back(bel[j]);
            ++ind[bel[j]];
        }
    }
    vector<int> tppos(cc + 5, -1);
    for (int i = 0; i < (int)cctp.size(); ++i) tppos[cctp[i]] = i;
    for (int i = 1; i <= cc; ++i) cango[i][i] = 1;
    for (int i = (int)tp.size() - 1; i >= 0; --i) {
        sort(cG[i].begin(), cG[i].end(), [&](const int &a, const int &b) { return tppos[a] < tppos[b]; });
        for (int j : cG[i]) {
            // cerr << "SCC " << i << " check " << j << endl;
            if (cango[i][j]) continue;
            cango[i] |= cango[j];
            ans.emplace_back(mem[i][0], mem[j][0]);
        }
    }
    /* queue<int> q;
    for (int i = 1; i <= cc; ++i) if (ind[i] == 0) q.push(i);
    while (q.size()) {
        int now = q.front(); q.pop();
        for (int i : cG[now]) {
            --ind[i];
            if (ind[i] == 0) {
                q.push(i);
                ans.emplace_back(mem[now][0], mem[i][0]);
            }
        }
    } */

    /* for (int i = 0, j; i < (int)tp.size(); i = j) {
        for (j = i; j < (int)tp.size(); ++j) 
            if (bel[tp[i]] != bel[tp[j]]) {
                if (C(tp[i], tp[j]))
                    ans.emplace_back(tp[i], tp[j]);
                break;
            }
    } */
    for (int i = 1; i <= cc; ++i) if (mem[i].size() > 1u) {
        for (int j = 0; j < (int)mem[i].size(); ++j) {
            int jj = (j + 1) % mem[i].size();
            ans.emplace_back(mem[i][j], mem[i][jj]);
        }
    }
    cout << n << " " << ans.size() << endl;
    for (auto p : ans) cout << p.first << " " << p.second << endl;
}
