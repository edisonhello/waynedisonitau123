#include <bits/stdc++.h>
using namespace std;

int x[333], y[333];

vector<int> mem[8];
vector<pair<int, int>> edg;

bool vis[8];
bool ct[333];

void dfs(int nmask) {
    // cerr << "Dfs nmask = " << nmask << endl;
    int masks[8] = {0};
    for (int i : mem[nmask]) masks[y[i]] = i;
    // cerr << "masks[5] = " << masks[5] << endl;
    for (int i = 1; i < 8; ++i) {
        if (masks[i] != 0) {
            int nxmask = i & nmask;
            if (vis[nxmask]) continue;
            vis[nxmask] = 1;
            for (int j : mem[nxmask]) {
                // cerr << "case 1 " << masks[i] << " to " << j << endl;
                edg.emplace_back(masks[i], j);
            }
            ct[masks[i]] = 1;
            dfs(nxmask);
        }
    }

    for (int i = 1; i < 8; ++i) for (int j = 1; j < 8; ++j) {
        // if ((nmask & i) == i && (nmask & j) == j); else continue;
        // if (__builtin_popcount(i) == 1 && __builtin_popcount(j) == 1); else continue;
        if (masks[i] == 0 || masks[j] == 0) continue;
        int nxmask = (i & nmask) | (j & nmask);
        if (!vis[nxmask]); else continue;
        if (mem[nxmask].empty()) continue;
        vis[nxmask] = 1;
        edg.emplace_back(masks[i], mem[nxmask][0]);
        edg.emplace_back(masks[j], mem[nxmask][0]);
        for (int k = 1; k < (int)mem[nxmask].size(); ++k) {
            // cerr << "case 2 " << mem[nxmask][0] << " to " << mem[nxmask][k] << endl;
            edg.emplace_back(mem[nxmask][0], mem[nxmask][k]);
        }
        ct[masks[i]] = 1;
        ct[masks[j]] = 1;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int q, w, e; cin >> q >> w >> e;
        x[i] = (q) | (w << 1) | (e << 2);
        mem[x[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        int q, w, e; cin >> q >> w >> e;
        y[i] = (q) | (w << 1) | (e << 2);
    }

    for (int i : mem[7]) if (i > 1) edg.emplace_back(1, i);
    vis[7] = 1;
    dfs(7);

    for (int want = 1; want < 7; ++want) if (!vis[want] && mem[want].size() && __builtin_popcount(want) == 2) {
        for (int sa = 1; sa < 7; ++sa) if (vis[sa] && __builtin_popcount(sa) == 1 && mem[sa].size()) {
            for (int sb = 1; sb < 7; ++sb) if (vis[sb] && __builtin_popcount(sb) == 1 && (sa | sb) == want && mem[sb].size() && !vis[want]) {
                vis[want] = 1;
                edg.emplace_back(mem[sa][0], mem[want][0]);
                edg.emplace_back(mem[sb][0], mem[want][0]);
                for (int i = 1; i < (int)mem[want].size(); ++i) {
                    edg.emplace_back(mem[want][0], mem[want][i]);
                }
            }
        }
    }

    for (int i = 1; i < 8; ++i) if (mem[i].size() && !vis[i]) {
        cout << "Impossible" << endl;
        exit(0);
    }

    cout << "Possible" << endl;
    for (int i = 1; i <= n; ++i) cout << ct[i] << ' ';
    cout << endl;
    cout << edg.size() << endl;
    assert(edg.size() <= 264);
    for (auto &p : edg) cout << p.first << ' ' << p.second << '\n';
}
