#include <bits/stdc++.h>
using namespace std;

vector<int> G[100005];
int dep[100005], pa[20][100005];
int Q[100005][2], tag[100005], arw[100005];
int in[100005], out[100005], dft;
int pae[100005];
long long seg[100005];
vector<int> qids[100005];

void dfs(int now, int p, int d) {
    dep[now] = d;
    pa[0][now] = p;
    in[now] = ++dft;
    for (int i = 1; i < 20; ++i) pa[i][now] = pa[i - 1][pa[i - 1][now]];
    for (int i : G[now]) if (i != p) {
        dfs(i, now, d + 1);
    }
    out[now] = dft;
}

int get_lca(int a, int b) {
    if (dep[a] > dep[b]) swap(a, b);
    for (int i = 19; i >= 0; --i) if ((dep[b] - dep[a]) & (1 << i)) {
        b = pa[i][b];
    }
    if (a == b) return a;
    for (int i = 19; i >= 0; --i) if (pa[i][a] != pa[i][b]) {
        a = pa[i][a];
        b = pa[i][b];
    }
    return pa[0][a];
}

int dfs1(int now, int pa) {
    // cerr << "dfs1 " << now << " " << pa << endl;
    int cur = tag[now];
    for (int i : G[now]) if (i != pa) {
        cur += dfs1(i, now);
    }
    pae[now] = cur;
    // cerr << "dfs1 " << "cur of " << now << " = " << cur << endl;
    return cur;
}

/* pair<long long, set<int>*> dfs2(int now, int pa) {
    cerr << "dfs2 " << now << " " << pa << endl;
    vector<set<int>*> sets;
    long long anss = 0;
    set<int> *st = new set<int>();
    for (int i : qids[now]) st->insert(i);
    for (int i : G[now]) if (i != pa) {
        auto rt = dfs2(i, now);
        anss += rt.first;
        sets.push_back(rt.second);
    }
    sort(sets.begin(), sets.end(), [](const set<int> *a, const set<int> *b) { return a->size() > b->size(); });
    for (set<int> *&p : sets) anss += p->size(); 
    if (sets.size()) anss -= sets[0]->size();
    cerr << "now processing at " << now << endl;
    if (sets.size()) {
        for (int i = 1; i < (int)sets.size(); ++i) {
            for (int j : *sets[i]) {
                if (sets[0]->count(j)) sets[0]->erase(j);
                else sets[0]->insert(j);
            }
            delete sets[i];
        }
        for (int j : *st) {
            if (sets[0]->count(j)) sets[0]->erase(j);
            else sets[0]->insert(j);
            delete st;
        }
        return make_pair(anss, sets[0]);
    } else {
        return make_pair(anss, st);
    }

} */

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0, 1);
    // cerr << "in = "; for (int i = 1; i <= n; ++i) cerr << in[i] << " "; cerr << endl;
    // cerr << "out = "; for (int i = 1; i <= n; ++i) cerr << out[i] << " "; cerr << endl;
    long long ans = 0;
    for (int i = 1; i <= m; ++i) {
        cin >> Q[i][0] >> Q[i][1];
        if (dep[Q[i][0]] > dep[Q[i][1]]) swap(Q[i][0], Q[i][1]);
        int a = Q[i][0], b = Q[i][1];
        int lca = get_lca(a, b);
        if (lca == a) {
            tag[lca] -= 1;
            tag[b] += 1;
        } else {
            tag[lca] -= 2;
            tag[a] += 1;
            tag[b] += 1;
        }
        ans += dep[a] + dep[b] - dep[lca] * 2;
        qids[a].push_back(i);
        qids[b].push_back(i);
    }
    ans *= 2;
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i) {
        // cerr << "now at i = " << i << " , pae = " << pae[i] << endl;
        auto add = [&](int l, int r, long long v) -> void {
            seg[l] += v;
            seg[r + 1] -= v;
            // cerr << "add " << l << " " << r << " " << v << endl;
        };
        if (i > 1) {
            int mx = 0;
            for (int j : G[i]) if (j != pa[0][i]) mx = max(mx, pae[j]);
            int val = -1;
            if (pae[i] > mx) val = mx;
            else val = pae[i];
            add(1, dft, val);
            add(in[i], out[i], -val);
        }
        vector<pair<int, int>> v; v.emplace_back(pae[i], pa[0][i]); v.emplace_back(0, -100);
        for (int j : G[i]) if (j != pa[0][i]) {
            v.emplace_back(pae[j], j);
        }
        sort(v.begin(), v.end(), greater<pair<int, int>>());
        for (int j : G[i]) if (j != pa[0][i]) {
            if (v[0].second == j) {
                add(in[j], out[j], v[1].first);
            } else {
                add(in[j], out[j], pae[j]);
            }
        }
    }
    for (int i = 2; i <= dft; ++i) seg[i] += seg[i - 1];
    auto get_value = [&](const int x) {
        int mx = pae[x];
        for (int i : G[x]) if (i != pa[0][x]) mx = max(mx, pae[i]);
        // return mx + seg[x];
        return seg[x];
    };
    int root = 1;
    long long mxv = get_value(1);
    for (int i = 2; i <= n; ++i) if (get_value(i) > mxv) {
        root = i;
        mxv = get_value(i);
    }
    // cerr << "root = " << root << endl;
    // cerr << "vertex value = ";
    // for (int i = 1; i <= n; ++i) cerr << seg[i] << " "; cerr << endl;
    ans -= seg[root];
    for (int i = 1; i <= n; ++i) {
        int mx = pae[i];
        for (int j : G[i]) if (j != pa[0][i]) {
            mx = max(mx, pae[j]);
        }
        ans -= mx;
    }
    // auto rt = dfs2(root, 0);
    cout << ans << endl;
}
