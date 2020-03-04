#include <bits/stdc++.h>
using namespace std;

long long parse(string s) {
    int sign = 1;
    int n = (int)s.size();
    if (s[0] == 'W') {
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'W') s[i] = 'B';
            else s[i] = 'W';
        }
        sign = -1;
    }
    s += 'B';
    int z = 0;
    while (z < n && s[z] == 'B') ++z;
    if (z == n) return sign * z * (1LL << 41);
    long long res = (z - 1) * (1LL << 41);
    for (int i = z + 1, j = 40; i < n + 1; ++i, --j) {
        if (s[i] == 'B') res += (1LL << j);
    }
    return res * sign;
}

int main() {
    int n; cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    vector<long long> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = parse(s[i]);
        // cout << "v = " << v[i] << endl;
    }
    int m = n / 2;
    map<long long, int> cc;
    for (int i = 0; i < (1 << m); ++i) {
        long long sum = 0;
        int len = 0;
        for (int j = 0; j < m; ++j) {
            if (i >> j & 1) sum += v[j], len += s[j].size();
        }
        cc[sum] = max(cc[sum], len);
    }
    int ans = 0;
    for (int i = 0; i < (1 << (n - m)); ++i) {
        long long sum = 0;
        int len = 0;
        for (int j = 0; j < n - m; ++j) {
            if (i >> j & 1) sum += v[j + m], len += s[j + m].size();
        }
        if (cc.find(-sum) != cc.end()) {
            ans = max(ans, cc[-sum] + len);
        }
    }
    cout << ans << endl;
}
