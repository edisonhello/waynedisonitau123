#include <bits/stdc++.h>
using namespace std;

int a[1005], len[1005], node[1005][20], val[1005][20];
int d[1005 * 20];
bitset<1005 * 20> vis;
vector<pair<int, int>> g[1005 * 20];

void addedge(int u, int v, int w) {
    // printf("add edge %d %d %d\n", u, v, w);
    g[u].emplace_back(v, w);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    int empty = 0; 
    int nn = 1;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int v = 0;
        for (char c : s) v = v * 2 + c - '0';
        a[i] = v;
        len[i] = s.size();
        for (int j = 1; j <= len[i]; ++j) {
            node[i][j] = nn++;
            val[i][j] = a[i] & ((1 << j) - 1);
            // printf("val[%d][%d] = %d, node[%d][%d] = %d\n", i, j, val[i][j], i, j, node[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) for (int j = 1; j <= len[i]; ++j) {
        for (int k = 0; k < n; ++k) if (!(i == k && j == len[i])) {
            if (len[k] < j) continue;
            int lend = len[k] - j;
            if (val[i][j] != (a[k] >> lend)) continue;
            addedge(node[k][lend], node[i][j], j);
        }
    }
    // puts("meow");
    for (int i = 0; i < n; ++i) for (int j = 1; j <= len[i]; ++j) {
        for (int k = 0; k < n; ++k) if (i != k) {
            if (len[k] > j) continue;
            int lend = j - len[k];
            if ((a[k]) != (val[i][j] >> lend)) continue;
            // printf("i %d j %d k %d lend = %d\n", i, j, k, lend);
            addedge(node[i][lend], node[i][j], j - lend);
        }
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, 0);
    memset(d, 0x3f, sizeof(d));
    d[0] = 0;
    while (pq.size()) {
        while (pq.size() && vis[pq.top().second]) pq.pop();
        if (pq.empty()) break;
        int now = pq.top().second;
        vis[now] = 1;
        for (auto &e : g[now]) {
            if (d[e.first] > e.second + d[now]) {
                d[e.first] = e.second + d[now];
                pq.emplace(d[e.first], e.first);
            }
        }
    }
    
    int mn = 0x3f3f3f3f;
    for (int i = 0; i < n; ++i) mn = min(mn, d[node[i][len[i]]]);

    if (mn == 0x3f3f3f3f) cout << 0 << endl;
    else cout << mn << endl;
}
