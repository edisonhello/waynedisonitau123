#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> st[4000006];

bool find(pair<int, int> p) {
    int z = p.first + p.second;
    auto it = lower_bound(st[z].begin(), st[z].end(), p);
    return it != st[z].end() && *it == p;
}

bool find(int x, int y) { return find(make_pair(x, y)); }

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        x += 1000000, y += 1000000;
        st[x + y].push_back(make_pair(x, y));
    }
    for (int z = 0; z < 4000006; ++z) sort(st[z].begin(), st[z].end());
    long long ans = 0;
    for (int z = 0; z < 4000006; ++z) {
        if (st[z].size() <= 350) {
            for (int i = 0; i < (int)st[z].size(); ++i) {
                for (int j = i + 1; j < (int)st[z].size(); ++j) {
                    if (find(st[z][i].first, st[z][j].second) && 
                            find(st[z][j].first, st[z][i].second)) ++ans;
                }
            }
        } else {
            for (int y = 0; y < z; ++y) {
                for (int i = 0; i < (int)st[y].size(); ++i) {
                    if (find(st[y][i].first, z - st[y][i].first) && 
                            find(z - st[y][i].second, st[y][i].second) && 
                            find(z - st[y][i].second, z - st[y][i].first)) ++ans;
                }
            }
        }
    }
    cout << ans << endl;
}
