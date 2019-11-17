#include <bits/stdc++.h>
using namespace std;

int a[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {-1, 0, -1}};
set<int> all;

int v[5][5][555];
void dfs(int x, int y, int now) {
    if (x >= 4 || y >= 3 || now > 200) return;
    if (a[x][y] == -1) return;
    if (v[x][y][now]) return;
    // cerr << "dfs " << x << " " << y << " " << now << endl;
    v[x][y][now] = 1;
    all.insert(now);
    all.insert(now * 10 + a[x][y]);
    dfs(x, y, now);
    dfs(x, y, now * 10 + a[x][y]);
    dfs(x + 1, y, now);
    dfs(x + 1, y, now * 10 + a[x][y]);
    dfs(x, y + 1 , now);
    dfs(x, y + 1 , now * 10 + a[x][y]);
}

int f(int n) {
    auto it = all.lower_bound(n);
    int dl = it == all.begin() ? 99999999 : n - *prev(it);
    int dr = it == all.end() ? 99999999 : *it - n;
    if (dl <= dr) return *prev(it);
    return *it;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i = 0; i < 10; ++i) all.insert(i);
    dfs(0, 0, 0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        cout << f(n) << '\n';
    }
}
