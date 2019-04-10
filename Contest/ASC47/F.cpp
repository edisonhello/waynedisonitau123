#include <bits/stdc++.h>
using namespace std;

vector<int> G[1005];
int pa[1005], clr[1005];

void dfs(int now, int p) {
    pa[now] = p;
    for (int i : G[now]) {
        if (i == p) continue;
        dfs(i, now);
    }
}

int dfs2(int now, int p) {
    if (clr[now] == 0) return now;
    for (int i : G[now]) {
        if (i == p) continue;
        int r = dfs2(i, now);
        if (r) return r;
    }
    return 0;
}

int main() {
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    clr[1] = 1;
    cout << 1 << " " << 1 << endl;
    int x, c; while (cin >> x >> c) {
        if (x == -1) break;
        clr[x] = c;
        while (x) {
            x = pa[x];
            if (!clr[x]) break;
        }
        if (x == 0) x = dfs2(1, 0);
        set<int> st;
        for (int i : G[x]) st.insert(clr[i]);
        if (!st.count(1)) clr[x] = 1;
        else if (!st.count(2)) clr[x] = 2;
        else if (!st.count(3)) clr[x] = 3;
        else if (!st.count(4)) clr[x] = 4;
        cout << x << " " << clr[x] << endl;
    }
}
