#include <bits/stdc++.h>
using namespace std;

void unbound() {
    cout << "unbounded" << endl;
    exit(0);
}

set<int> g[52];
bool vis[52];
int ind[52];

void dfs(int now, int fr) {
    vis[now] = 1;
    for (int i : g[now]) if (i != fr) {
        if (vis[i]) unbound();
        dfs(i, now);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < 8; j += 2) {
            for (int k = 0; k < 8; k += 2) if (j != k) {
                if (s[j] == '0') continue;
                if (s[k] == '0') continue;
                int jj = s[j] - 'A' + (s[j + 1] == '+' ? 0 : 26);
                int kk = s[k] - 'A' + (s[k + 1] == '+' ? 26 : 0);
                g[jj].insert(kk);
            }
        }
    }
    
    for (int i = 0; i < 52; ++i) if (g[i].count(i)) unbound();
    for (int i = 0; i < 52; ++i) for (int j : g[i]) if (g[j].count(i)) unbound();
    for (int i = 0; i < 52; ++i) for (int j : g[i]) ++ind[j];

    queue<int> q;
    for (int i = 0; i < 52; ++i) if (ind[i] == 0) q.push(i);

    int cnt = 0;
    while (q.size()) {
        int now = q.front(); q.pop();
        ++cnt;
        for (int j : g[now]) {
            --ind[j];
            if (ind[j] == 0) q.push(j);
        }
    }

    if (cnt != 52) unbound();

    cout << "bounded" << endl;
}
