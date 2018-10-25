#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
map<string, vector<int>> fa;
string f[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> f[i];
        for (int j = 0; j < f[i].size(); ++j) {
            string k = "";
            for (int r = j; r < f[i].size(); ++r) {
                k += f[i][r];
                fa[k].push_back(i);
            }
        }
    }
    for (auto &it : fa) {
        sort(it.second.begin(), it.second.end());
        it.second.resize(unique(it.second.begin(), it.second.end()) - it.second.begin());
    }
    int q; cin >> q;
    while (q--) {
        string s; cin >> s;
        if (fa.find(s) == fa.end()) {
            cout << 0 << " -" << '\n';
        } else {
            cout << fa[s].size() << ' ' << f[fa[s][0]] << '\n';
        }
    }
}
