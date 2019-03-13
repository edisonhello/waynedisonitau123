#include <bits/stdc++.h>
using namespace std;

int A[105], n;

int calc(int x, const int mod) {
    int curx = 1, sum = 0;
    for (int i = 0; i < n; ++i) {
        sum = ((sum + 1ll * curx * A[i]) % mod + mod) % mod;
        curx = 1ll * curx * x % mod;
    }
    // cerr << x << " " << mod << " " << sum << endl;
    return sum;
}

bool test(int x) {
    // cerr << "test: " << x << endl;
    if (calc(x, 1000000007)) return 0;
    if (calc(x, 1000000009)) return 0;
    if (calc(x, 1000000123)) return 0;
    if (calc(x, 1000000087)) return 0;
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        cin >> n;
        for (int i = n - 1; i >= 0; --i) {
            cin >> A[i];
        }
        vector<int> ans;
        if (test(0)) ans.push_back(0);
        int idx = 0;
        while (A[idx] == 0) ++idx;
        for (int i = 1; i * i <= abs(A[idx]); ++i) {
            if (A[0] % i) continue;
            if (test(i)) ans.push_back(i);
            if (test(-i)) ans.push_back(-i);
            if (test(A[idx] / i)) ans.push_back(A[idx] / i);
            if (test(-A[idx] / i)) ans.push_back(-A[idx] / i);
        }
        sort(ans.begin(), ans.end());
        ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
        if (ans.size()) {
            cout << "Yes\n";
            for (int i : ans) {
                cout << i << " \n"[i == ans.back()];
            }
        } else cout << "No\n";
    }
}
