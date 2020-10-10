#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];

    sort(v.begin(), v.end());
    auto getmn = [&] () {
        long long ans = 0;
        for (int i = 1; i < (int)v.size() - 1; ++i) {
            if (v[i] < 0) {
                ans += v[i] * 1ll * v.back();
            } else {
                ans += v[i] * 1ll * v[0];
            }
        }
        ans += v[0] * 1ll * v.back();
        return (ans % mod + mod) % mod;
    };
    auto getmx = [&] () {
        long long ans = 0;
        vector<int> pos, neg;
        for (int i : v) {
            if (i >= 0) pos.push_back(i);
            else neg.push_back(i);
        }
        sort(pos.begin(), pos.end());
        sort(neg.begin(), neg.end());
        reverse(neg.begin(), neg.end());
        for (int i = 0; i < (int)pos.size() - 1; ++i) {
            ans += 1ll * pos[i] * pos.back();
        }
        for (int i = 0; i < (int)neg.size() - 1; ++i) {
            ans += 1ll * neg[i] * neg.back();
        }

        if (pos.size() && neg.size()) ans += pos[0] * 1ll * neg[0];
        return (ans % mod + mod) % mod;
    };
    cout << getmn() << ' ' << getmx() << endl;
}
