#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace __gnu_pbds;
using namespace std;
 
const int kN = 200'000 + 5;
const int kB = 10;
int a[kN], dp[kN];
 
int fpow(int a, int n, int p) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % p;
        a = 1LL * a * a % p;
        n >>= 1;
    }
    return res;
}
 
int Geometry(int r, int n, int p) {
    cc_hash_table<int, int> last;
    for (int i = 0; i < n; ++i) dp[i] = 0;
    for (int i = n - 1; i >= 0; --i) {
        int f = 1LL * a[i] * r % p;
        if (last.find(f) == last.end()) dp[i] = 1;
        else dp[i] = dp[last[f]] + 1;
        last[a[i]] = i;
    }
    return *max_element(dp, dp + n);
}
 
int Solve() {
    int n, p; scanf("%d%d", &n, &p);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    vector<int> v;
    for (int i = 1; i < n; ++i) {
        v.push_back(1LL * a[i] * fpow(a[i - 1], p - 2, p) % p);
        if (i >= 2) {
            v.push_back(1LL * a[i] * fpow(a[i - 2], p - 2, p) % p);
        }
    }
    sort(v.begin(), v.end());
    vector<pair<int, int>> cv;
    for (int i = 0, j = 0; i < v.size(); i = j) {
        for (j = i; j < v.size() && v[j] == v[i]; ++j);
        cv.emplace_back(j - i, v[i]);
    }
    sort(cv.begin(), cv.end(), greater<pair<int, int>>());
    int m = min((int)cv.size(), kB);
    int res = -1;
    for (int i = 0; i < m; ++i) res = max(res, Geometry(cv[i].second, n, p));
    if (res * 2 < n) res = -1;
    return res;
}
 
int main() {
    int t; scanf("%d", &t);
    while (t--) printf("%d\n", Solve());
}
