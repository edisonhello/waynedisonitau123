#include <bits/stdc++.h>
using namespace std;

void no() {
    cout << -1 << endl;
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, h; cin >> n >> m >> h;
    vector<vector<int>> s1(n, vector<int>(m, 0));
    vector<vector<int>> s2(n, vector<int>(h, 0));

    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) if (s[j] == '1') s1[i][j] = 1;
    }
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < h; ++j) if (s[j] == '1') s2[i][j] = 1;
    }

    vector<tuple<int, int, int>> mx, mn;
    for (int i = 0; i < n; ++i) {
        int sum1 = 0, sum2 = 0;
        for (int j = 0; j < m; ++j) if (s1[i][j]) ++sum1;
        for (int j = 0; j < h; ++j) if (s2[i][j]) ++sum2;
        if (sum1 == 0 && sum2 != 0) no();
        if (sum2 == 0 && sum1 != 0) no();

        vector<int> jpos, kpos;
        for (int j = 0; j < m; ++j) if (s1[i][j]) jpos.push_back(j);
        for (int k = 0; k < h; ++k) if (s2[i][k]) kpos.push_back(k);

        for (int j : jpos) for (int k : kpos) mx.emplace_back(i, j, k);
        for (int j = jpos.size() - 1, k = kpos.size() - 1; j >= 0 || k >= 0; ) {
            mn.emplace_back(i, jpos[j], kpos[k]);
            --j, --k;
            if (j < 0 && k < 0) break;
            if (j < 0) j = 0;
            if (k < 0) k = 0;
        }
    }

    sort(mn.begin(), mn.end());
    sort(mx.begin(), mx.end());
    
    cout << mx.size() << endl;
    for (auto [i, j, k] : mx) cout << i << ' ' << j << ' ' << k << '\n';
    cout << mn.size() << endl;
    for (auto [i, j, k] : mn) cout << i << ' ' << j << ' ' << k << '\n';
}

