#include <bits/stdc++.h>
using namespace std;

int gmc[200005];
map<int, int> sgic[200005], sgis[200005];
int rcv[200005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, s; cin >> n >> m >> s;

    while (s--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) {
            sgic[x][y] = gmc[y];
            sgis[x][y] = 0;
        } else if (t == 2) {
            int dta = gmc[y] - sgic[x][y];
            rcv[x] += dta - sgis[x][y];
            sgic[x].erase(y);
            sgis[x].erase(y);
        } else if (t == 3) {
            ++gmc[y];
            ++sgis[x][y];
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (auto p : sgic[i]) {
            rcv[i] += gmc[p.first] - p.second - sgis[i][p.first];
        }
    }

    for (int i = 1; i <= m; ++i) cout << rcv[i] << '\n';
}

