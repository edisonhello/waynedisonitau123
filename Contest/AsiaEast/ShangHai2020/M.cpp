#include <bits/stdc++.h>
using namespace std;

struct node {
    unordered_map<string, node*> mp;
    int ig, nig;
    node(): ig(0), nig(0) {}
};

vector<string> input() {
    string s; cin >> s;
    vector<string> v;
    string cur;
    for (char c : s) {
        if (c == '/') v.push_back(cur), cur = "";
        else cur += c;
    }
    v.push_back(cur);
    return v;
}

void insert(node *now, vector<string> &v, int id, int add) {
    if (add == 1) now->ig++;
    else now->nig++;

    if (id == v.size()) {
        return;
    }

    auto it = now->mp.find(v[id]);
    node *pt;
    if (it == now->mp.end()) {
        pt = now->mp[v[id]] = new node();
    } else {
        pt = it->second;
    }
    insert(pt, v, id + 1, add);
}

int dfs(node *now) {
    if (now->ig == 0) return 0;
    if (!now->nig) return 1;
    int ans = 0;
    for (auto p : now->mp) {
        ans += dfs(p.second);
    }
    return ans;
}

void del(node *now) {
    for (auto p : now->mp) del(p.second);
    delete now;
}


void solve() {
    int n, m; cin >> n >> m;

    node *root = new node();
    while (n--) {
        auto v = input();
        insert(root, v, 0, 1);
    }
    while (m--) {
        auto v = input();
        insert(root, v, 0, -1);
    }
    
    int ans = 0;
    for (auto p : root->mp) {
        ans += dfs(p.second);
    }
    cout << ans << '\n';

    del(root);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) solve();
}

