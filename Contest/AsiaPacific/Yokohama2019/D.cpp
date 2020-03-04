#include <bits/stdc++.h>
using namespace std;

struct P {
    using type = int;
    type x, y, z;
};

P pa[222], pb[222];
vector<int> ga[222], gb[222];
vector<pair<int, int>> tga, tgb;

bool mapping(int n, pair<int, int> fea, pair<int, int> feb) {
    pair
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> pa[i].x >> pa[i].y >> pa[i].z;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        ga[u].push_back(v);
        ga[v].push_back(u);
        tga.emplace_back(u, v);
    }
    for (int i = 1; i <= n; ++i) cin >> pb[i].x >> pb[i].y >> pb[i].z;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        gb[u].push_back(v);
        gb[v].push_back(u);
        tgb.emplace_back(u, v);
    }

    int cnt = 0;
    for (pair<int, int> ea : tga) {
        for (pair<int, int> eb : tgb) {
            cnt += mapping(n, ea, eb);
            swap(eb.first, eb.second);
            cnt += mapping(n, ea, eb);
        }
    }
    cout << cnt << endl;
}
