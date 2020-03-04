#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;

map<string, int> zid;

int gid(string s) {
    if (zid.find(s) != zid.end()) return zid[s];
    int res = (int)zid.size();
    return zid[s] = res;
}

bool wk[maxn];
vector<int> gd[maxn][maxn];
bool rc[maxn][maxn];


int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    string p_, q_; cin >> p_ >> q_;
    int x = gid(p_), y = gid(q_);
    int n; cin >> n;
    vector<vector<pair<int, int>>> lst;
    for (int i = 0; i < n; ++i) {
        int m; cin >> m;
        vector<pair<int, int>> z;
        for (int j = 0; j < m; ++j) {
            string a, b; cin >> a >> b;
            int u = gid(a), v = gid(b);
            gd[u][v].push_back(i);
            z.emplace_back(u, v);
        }
        lst.push_back(z);
    }

    queue<int> q;

    int m = (int)zid.size();

    function<void(int, int)> push = [&](int u, int v) {
        for (int i = 0; i < (int)gd[u][v].size(); ++i) {
            int d = gd[u][v][i];
            if (!wk[d]) {
                wk[d] = true;
                q.push(d);
            }
        }
        rc[u][v] = true;
        for (int i = 0; i < m; ++i) {
            if (rc[v][i] && !rc[u][i]) {
                rc[u][i] = true;
                push(u, i);
            }
        }
        for (int i = 0; i < m; ++i) {
            if (rc[i][u] && !rc[i][v]) {
                rc[i][v] = true;
                push(i, v);
            }
        }
    };

    push(x, y);

    while (!q.empty()) {
        int d = q.front(); q.pop();
        for (int i = 0; i < (int)lst[d].size(); ++i) {
            int u = lst[d][i].first, v = lst[d][i].second;
            push(u, v);
        }
    }

    for (int k = 0; k < m; ++k) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                rc[i][j] |= rc[i][k] && rc[k][j];
            }
        }
    }
    bool fl = false;
    for (int i = 0; i < m; ++i) fl |= rc[i][i];

    if (fl) puts("No");
    else puts("Yes");

    return 0;
}
