#include <bits/stdc++.h>
using namespace std;

map<pair<string, int>, unsigned long long> dp;

bool suffix(const string &a, const string &b) {
    assert((int)a.size() >= (int)b.size());
    bool suf = true;
    for (int i = (int)a.size() - (int)b.size(), j = 0; i < (int)a.size(); ++i, ++j) {
        suf &= a[i] == b[j];
    }
    return suf;
}

bool place(string known, int n, string ask) {
    if ((int)known.size() + (int)ask.size() <= n)
        return true;
    int overlap = (int)known.size() + (int)ask.size() - n;
    bool res = true;
    for (int i = (int)known.size() - overlap; i < (int)known.size(); ++i)
        res &= known[i] == ask[i - (int)known.size() + overlap];
    return res;
}

unsigned long long solve(string pref, int n) {
    if (dp.find(make_pair(pref, n)) != dp.end())
        return dp[make_pair(pref, n)];
    unsigned long long res = 0;
    vector<string> pass;
    if (pref.size() == n) {
        for (int i = 1; i < n; ++i) {
            if (suffix(pref, pref.substr(0, i))) 
                return 1;
        }
        return 0;
    }
    for (int i = 1; i <= n ; ++i) {
        if (i <= (int)pref.size()) {
            bool seen = false;
            for (int j = 0; j < (int)pass.size(); ++j)
                seen |= suffix(pref.substr(0, i), pass[j]);
            if (!seen) {
                if (place(pref, n, pref.substr(0, i)))
                    res += n - i - (int)pref.size() >= 0 ? (1ull << (n - i - (int)pref.size())) : 1;
            }
            pass.push_back(pref.substr(0, i));
        } else {
            if (i * 2 > n) continue;
            res += ((1ull << (i - (int)pref.size())) - solve(pref, i)) * (1ull << (n - i - i));
        }
    }
    return dp[make_pair(pref, n)] = res;
}


int main() {
#ifdef ONLINE_JUDGE
    freopen("borderless.in", "r", stdin);
    freopen("borderless.out", "w", stdout);
#endif
    
    int n; unsigned long long k;
    while (cin >> n >> k) {
        string ans = "";
        --k;
        for (int i = 1; i <= n; ++i) {
            unsigned long long x = (1ull << (n - i)) - solve(ans + 'a', n);
            if (x <= k) {
                k -= x;
                ans += 'b';
            } else {
                ans += 'a';
            }
        }
        cout << ans << endl;
    }
    return 0;
}
        
