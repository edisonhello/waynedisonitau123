#include <bits/stdc++.h>
using namespace std;

string s[8];

int dfs(vector<int> c, vector<int> v, int i = 0) {
    if (i == v.size()) return 1;
    int res = 0;
    for (int j = 0; j < c.size(); ++j) {
        if (c[j] >= v[i]) {
            c[j] -= v[i];
            res += dfs(c, v, i + 1);
            c[j] += v[i];
        }
    }
    return res;
}

int main() {
    map<string, int> c;
    for (int i = 0; i < 8; ++i) {
        cin >> s[i];
        c[s[i]]++;
    }

    vector<int> cc;
    for (auto it : c) cc.push_back(it.second);

    long long ans = dfs(cc, {1, 3, 3, 1}) * 8 + dfs(cc, {2, 2, 2, 2}) * 9 + dfs(cc, {1, 1, 1, 1, 1, 1, 1, 1}) * 1 + dfs(cc, {4, 4}) * 6;
    printf("%lld\n", ans / 24);
}
