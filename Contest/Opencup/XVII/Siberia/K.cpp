#pragma GCC optimize("O3")

#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    int t, p;
    cin >> t >> p;
    vector<int> pw(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        pw[i] = 10LL * pw[i - 1] % p;
    }
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        int d = s[i] - '0';
        pref[i + 1] = (pref[i] + 1LL * d * pw[n - 1 - i]) % p;
    }
    vector<int> r(t);
    vector<int64_t> res(t);
    vector<int> ql(t), qr(t);
    for (int i = 0; i < t; ++i) cin >> r[i];
    cc_hash_table<int, int> cnt;
    cc_hash_table<int, int> pv;
    pv[0] = 0;
    cnt[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < t; ++j) {
            int req = 1LL * r[j] * pw[n - i - 1] % p;  
            req = (pref[i + 1] + p - req);
            req >= p ? req -= p : 0;
            if (cnt.find(req) != cnt.end()) {
                res[j] += cnt[req];
                if (ql[j] == 0) {
                    ql[j] = pv[req] + 1;
                    qr[j] = i + 1;
                }
            }
        }
        cnt[pref[i + 1]]++;
        if (pv.find(pref[i + 1]) == pv.end()) {
            pv[pref[i + 1]] = i + 1;
        }
    }
    for (int i = 0; i < t; ++i) {
        cout << res[i] << " " << ql[i] << " " << qr[i] << "\n";
    }
    return 0;
}

