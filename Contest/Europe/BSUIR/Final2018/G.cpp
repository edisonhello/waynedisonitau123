#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 400005;
vector<pair<int, int>> g[maxn], bg[maxn];
pair<int, int> edge[maxn];
vector<int> mem[maxn], meme[maxn], bel[maxn];
int dfn[maxn], low[maxn], cc, ebel[maxn], sz[maxn];
bool ins[maxn], cut[maxn];
stack<int> st;
// map<pair<int, int>, int> geteid;

int szn[maxn], szb[maxn];

void dfs(int x, int p) {
    static int tk = 1;
    dfn[x] = low[x] = ++tk;
    int ch = 0;
    for (auto &e : g[x]) if (e.first != p) {
        if (!ins[e.second]) {
            st.push(e.second);
            ins[e.second] = true;
        }
        if (dfn[e.first]) {
            low[x] = min(low[x], dfn[e.first]);
            continue;
        }
        dfs(e.first, x);
        low[x] = min(low[x], low[e.first]);
        if (low[e.first] >= dfn[x]) {
            cut[x] = true;
            ++cc;
            while (true) {
                int z = st.top(); st.pop();
                bel[edge[z].first].push_back(cc);
                bel[edge[z].second].push_back(cc);
                mem[cc].push_back(edge[z].first);
                mem[cc].push_back(edge[z].second);
                ebel[z] = cc;
                meme[cc].push_back(z);
                if (z == e.second) break;
            }
        }
    }
    if (ch == 1 && p == -1) cut[x] = false;
}

void nbdfssz(int now, int pa, int nb) {
    if (nb == 1) {
        szn[now] = 1;
        for (int i : bel[now]) if (i != pa) {
            nbdfssz(i, now, 2);
            szn[now] += szb[i];
        }
    } else {
        // szb[now] = mem[now].size();
        for (int i : mem[now]) if (i != pa) {
            nbdfssz(i, now, 1);
            szb[now] += szn[i];
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
        edge[i] = minmax(u, v);
        // geteid[edge[i]] = i;
    }
    dfs(1, 0);

    for (int i = 1; i <= n; ++i) {
        sort(bel[i].begin(), bel[i].end());
        bel[i].resize(unique(bel[i].begin(), bel[i].end()) - bel[i].begin());
        // cerr << "bel[" << i << "]: ";
        // for (int j : bel[i]) cerr << j << ' ';
        // cerr << endl;
    }
    for (int i = 1; i <= cc; ++i) {
        sort(mem[i].begin(), mem[i].end());
        mem[i].resize(unique(mem[i].begin(), mem[i].end()) - mem[i].begin());
        // cerr << "mem[" << i << "]: ";
        // for (int j : mem[i]) cerr << j << ' ';
        // cerr << endl;
    }

    nbdfssz(1, -1, 1);

    // for (int i = 1; i <= n; ++i) cerr << "szn[" << i << "] = " << szn[i] << endl;
    // for (int i = 1; i <= cc; ++i) cerr << "szb[" << i << "] = " << szb[i] << endl;

    long long ans = 0;
    for (int i = 1; i <= cc; ++i) if (meme[i].size() == 1u) {
        int ei = meme[i][0];
        int u = edge[ei].first, v = edge[ei].second;
        // cerr << "edge not in bcc id " << ei << " u v " << u << " " << v << endl;
        if (szn[u] < szn[v]) swap(u, v);
        // cerr << "answer add " << 1ll * szn[v] * (n - szn[v]) << '\n';
        ans += 1ll * szn[v] * (n - szn[v]);
    } else {
        // cerr << "----- go loop " << endl;
        int bcci = i;

        for (int ei : meme[bcci]) {
            int u = edge[ei].first, v = edge[ei].second;
            bg[u].emplace_back(v, ei);
            bg[v].emplace_back(u, ei);
        }

        vector<int> thisloop = {mem[bcci][0]};
        while (thisloop.size() == 1u || thisloop[0] != thisloop.back()) {
            for (auto &p : bg[thisloop.back()]) {
                if ((thisloop.size() == 1u || p.first != thisloop[thisloop.size() - 2]) && ebel[p.second] == bcci) {
                    thisloop.push_back(p.first);
                    break;
                }
            }
        }

        for (int i : mem[bcci]) bg[i].clear();

        thisloop.pop_back();

        // cerr << "thisloop: ";
        // for (int i : thisloop) cerr << i << ' ';
        // cerr << endl;

        int nn = thisloop.size();
        vector<int> sz(nn, 0);
        for (int i = 0; i < nn; ++i) {
            if (szn[thisloop[i]] >= szb[bcci]) sz[i] = n - szb[bcci];
            else sz[i] = szn[thisloop[i]];
        }

        // cerr << "sz: ";
        // for (int i : sz) cerr << i << ' ';
        // cerr << endl;

        vector<int> presz(nn, 0);
        presz[0] = sz[0];
        for (int i = 1; i < nn; ++i) presz[i] = presz[i - 1] + sz[i];

        // cerr << "presz: ";
        // for (int i : presz) cerr << i << ' ';
        // cerr << endl;

        auto norm = [&] (int x) {
            while (x < 0) x += nn;
            while (x >= nn) x -= nn;
            return x;
        };
        auto segget = [&] (int l, int r) {
            return presz[r] - (l ? presz[l - 1] : 0);
        };
        auto loopget = [&] (int l, int r) {
            l = norm(l), r = norm(r);
            if (l <= r) return segget(l, r);
            else return segget(l, nn - 1) + segget(0, r);
        };

        long long cur = 0;
        for (int st = nn / 2 + 1, ed = 0; st < nn; ++st, ++ed) {
            cur += 1ll * sz[st] * segget(0, ed);
        }

        // cerr << "cur init " << cur << endl;
        for (int i = 0; i < nn; ++i) {
            // cerr << "i = " << i << ", cur = " << cur << endl;
            ans += cur;
            cur -= 1ll * sz[i] * loopget(i - (nn - 1) / 2, i - 1);
            cur += 1ll * sz[i] * loopget(i + 1, i + (nn - 1) / 2);
        }

        if (nn % 2 == 0) {
            for (int i = 0; i < nn / 2; ++i) {
                ans += 1ll * sz[i] * sz[i + nn / 2] * (nn / 2);
            }
        }
    }

    cout << ans << '\n';
} 
