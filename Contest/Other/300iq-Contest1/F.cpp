#include <bits/stdc++.h>
using namespace std;


int djs[100005];

int F(int x) { return x == djs[x] ? djs[x] : djs[x] = F(djs[x]); }
void U(int x, int y) {
    djs[F(x)] = F(y);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) djs[i] = i;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        U(u, v);
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) if (djs[i] == i) ++cnt;

    cout << m - (n - cnt) << endl;
}

