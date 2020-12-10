#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t, T = 0; cin >> t; while (t--) {
        int n; cin >> n;
        vector<long long> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        sort(v.begin(), v.end());

        auto ok = [&] (long long r) {
            long long ne = 0;
            for (int i = 0; i < n; ++i) {
                ne += max(0ll, r - v[i] - 1);
            }

            if (ne >= r) { return false; }
            return true;
        };

        long long L = 1, R = 10'000'000'000;
        while (L < R) {
            long long M = (L + R + 1) >> 1;
            if (ok(M)) L = M;
            else R = M - 1;
        }

        cout << "Case #" << (++T) << ": " << L << '\n';

    }
}

