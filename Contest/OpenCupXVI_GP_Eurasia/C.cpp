#include <bits/stdc++.h>
using namespace std;

struct {
    int type;
    int lt, lv;
    int rt, rv;
} op[100005];

struct node {
    int i, type, val;
} no[200005];

map<pair<int, int>, int> toi;

vector<int> G[200005], iG[200005], tp;
vector<pair<int, int>> cG[200005];
bitset<200005> vis;
int bel[200005], ccv[200005], ccl[200005], ind[200005];

void build_node(pair<int, int> p) {
    auto it = toi.find(p);
    if (it == toi.end()) {
        int i = toi.size() + 1;
        // cerr << "build_node assign " << i << " to " << p.first << " " << p.second << endl;
        toi[p] = i;
        no[i].i = i;
        no[i].type = p.first;
        no[i].val = p.second;
    } 
}

int get_node(pair<int, int> p) {
    auto it = toi.find(p);
    return it->second;
}

void dfs1(int now) {
    // cerr << "dfs1 = " << now << endl;
    vis[now] = 1;
    for (int i : G[now]) if (!vis[i]) dfs1(i);
    tp.push_back(now);
}

void dfs2(int now, int ccn) {
    // cerr << "dfs2 " << now << " " << ccn << endl;
    vis[now] = 1;
    bel[now] = ccn;
    for (int i : iG[now]) if (!vis[i]) dfs2(i, ccn);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> op[i].type >> op[i].lt >> op[i].lv >> op[i].rt >> op[i].rv;
    for (int i = 1; i <= n; ++i) build_node(make_pair(op[i].lt, op[i].lv)), build_node(make_pair(op[i].rt, op[i].rv));
    for (int i = 1; i <= n; ++i) {
        if (op[i].type == 0) {
            int u = get_node(make_pair(op[i].lt, op[i].lv));
            int v = get_node(make_pair(op[i].rt, op[i].rv));
            G[u].push_back(v);
            // G[v].push_back(u);
            iG[v].push_back(u);
            // iG[u].push_back(v);
            // cerr << "build normal edge " << u << " to " << v << endl;
        }
    }
    int nn = toi.size();
    for (int i = 1; i <= nn; ++i) if (!vis[i]) dfs1(i);
    int cc = 0;
    reverse(tp.begin(), tp.end());
    vis.reset();
    for (int i : tp) if (!vis[i]) dfs2(i, ++cc);
    // cerr << "cc = " << cc << endl;
    // cerr << "nn = " << nn << endl;
    for (int i = 1; i <= nn; ++i) for (int j : G[i]) {
        if (bel[i] == bel[j]) continue;
        cG[bel[i]].emplace_back(bel[j], 0);
        ++ind[bel[j]];
        // cerr << "build cc edge from " << bel[i] << " to " << bel[j] << endl;
    }
    
    for (auto p : toi) {
        if (p.first.first == 0) ;
        else {
            if (ccl[bel[p.second]] && ccv[bel[p.second]] != p.first.second) exit((cout << "NO\n", 0));
            ccl[bel[p.second]] = 1;
            ccv[bel[p.second]] = p.first.second;
            // cerr << "lock " << p.second << " with " << p.first.second << endl;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (op[i].type == 1) {
            int u = bel[get_node(make_pair(op[i].lt, op[i].lv))];
            int v = bel[get_node(make_pair(op[i].rt, op[i].rv))];
            cG[u].emplace_back(v, 1);
            ++ind[v];
            // cerr << "build cc edge from " << u << " to " << v << endl;
        }
    }
    queue<int> qq;
    for (int i = 1; i <= cc; ++i) if (ind[i] == 0) qq.push(i);
    for (int i = 1; i <= cc; ++i) if (!ccl[i]) ccv[i] = -2000000000;
    while (qq.size()) {
        int now = qq.front(); qq.pop();
        for (auto p : cG[now]) {
            if (p.second) ccv[p.first] = max(ccv[p.first], ccv[now] + 1);
            else ccv[p.first] = max(ccv[p.first], ccv[now]);
            --ind[p.first];
            if (ind[p.first] == 0) qq.push(p.first);
        }
    }
    // cerr << "assign finished" << endl;
    // for (int i = 1; i <= cc; ++i) cerr << "ccv[" << i << "] = " << ccv[i] << endl;

    for (auto p : toi) {
        if (p.first.first == 0) ;
        else {
            if (ccl[bel[p.second]] && ccv[bel[p.second]] != p.first.second) exit((cout << "NO\n", 0));
            ccl[bel[p.second]] = 1;
            ccv[bel[p.second]] = p.first.second;
        }
    }

    for (int i = 1; i <= n; ++i) {
        // cerr << "checking condition " << i << endl;
        if (op[i].type == 0) {
            int u = bel[get_node(make_pair(op[i].lt, op[i].lv))];
            int v = bel[get_node(make_pair(op[i].rt, op[i].rv))];
            if (ccv[u] > ccv[v]) exit((cout << "NO\n", 0));
        }
        if (op[i].type == 1) {
            int u = bel[get_node(make_pair(op[i].lt, op[i].lv))];
            int v = bel[get_node(make_pair(op[i].rt, op[i].rv))];
            if (ccv[u] >= ccv[v]) exit((cout << "NO\n", 0));
        }
    }
    cout << "YES\n";
    for (int i = 1; i <= k; ++i) {
        int id = get_node(make_pair(0, i));
        cout << ccv[bel[id]] << '\n';
    }
}
