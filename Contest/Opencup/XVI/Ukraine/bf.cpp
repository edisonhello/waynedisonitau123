#include <bits/stdc++.h>
using namespace std;

bool mp[555][555];

int main() {
    int n, m; cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        for (int i = -n; i <= n; ++i) {
            if (u + i > 0 && u + i <= n && v + i > 0 && v + i <= n) mp[u + i][v + i] = 1;
            if (u - i > 0 && u - i <= n && v + i > 0 && v + i <= n) mp[u - i][v + i] = 1;
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= n; ++j)
            if (!mp[i][j])
                ++cnt;
    cout << cnt << endl;
}
