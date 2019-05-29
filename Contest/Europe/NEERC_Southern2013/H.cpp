#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> v[5006][30];
int cf[5006][30];
bool vis[5006][30];

void dfs(int nx, int ny, int dis) {
    if (nx == dis) return;
    vis[nx][ny] = 1;
    for (auto &p : v[nx][ny]) {
        if (vis[p.first][p.second]) continue;
        cf[p.first][p.second] = ny;
        dfs(nx + 1, p.second, dis);
    }
}

int main() {
    int n; cin >> n;
    string s; cin >> s;
    memset(cf, -1, sizeof(cf));
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == '=') {
            for (int j = 0; j < n; ++j) v[i][j].emplace_back(i + 1, j);
        }
        if (s[i] == '<') {
            for (int j = 0; j < n; ++j) for (int k = j + 1; k < n; ++k) v[i][j].emplace_back(i + 1, k);
        }
        if (s[i] == '>') {
            for (int j = 0; j < n; ++j) for (int k = 0; k < j; ++k) v[i][j].emplace_back(i + 1, k);
        }
    }
    for (int i = 0; i < 26; ++i) dfs(0, i, (int)s.size());
    for (int i = 0; i < 26; ++i) if (cf[s.size()][i] != -1) {
        string ans;
        int nx = s.size(), ny = i;
        ans += char('a' + ny);
        while (nx > 0) {
            ny = cf[nx][ny];
            --nx;
            ans += char('a' + ny);
        }
        reverse(ans.begin(), ans.end());
        cout << ans << endl;
        exit(0);
    }
    cout << -1 << endl;
}
