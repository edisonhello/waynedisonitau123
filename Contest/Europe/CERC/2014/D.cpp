#include <bits/stdc++.h>
using namespace std;

void dfs(int now, Int u, Int d) {

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<array<int, 3>> g(n + 2);        
        for (int i = 0; i < n; ++i) cin >> g[i][0] >> g[i][1] >> g[i][2];
        dfs(0, 1, 1);
    }
}
