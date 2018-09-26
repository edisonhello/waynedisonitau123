#include <bits/stdc++.h>
using namespace std;

long long det(const vector<vector<int>> &v) {
    if (v.size() == 1) return v[0][0];
    if (v.size() == 2) {
        return v[0][0] * 1ll * v[1][1] - v[0][1] * 1ll * v[1][0];
    }
    long long c = 1;
    int n = v.size();
    long long ret = 0;
    for (int i = 0; i < n; ++i) {
        vector<vector<int>> g;
        for (int j = 1; j < n; ++j) {
            g.push_back(vector<int>());
            for (int k = 0; k < n; ++k) {
                if (k == i) continue;
                g.back().push_back(v[j][k]);
            }
        }
        assert(g.size() == n - 1);
        if (v[0][i] != 0) {
            ret += c * 1ll * v[0][i] * det(g);
        }
        c *= -1;
    }
    return ret;
}

void sol() {
    int n; cin >> n;
    vector<vector<int>> v(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) cin >> v[i][j];
    long long trace = 0;
    for (int i = 0; i < n; ++i) trace += v[i][i];
    cout << trace << "\t" << det(v) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) sol();
}

