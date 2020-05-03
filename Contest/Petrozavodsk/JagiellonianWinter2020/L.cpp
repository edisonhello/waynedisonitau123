#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int z; cin >> z; while (z--) {
        int n, k; cin >> n >> k;
        vector<long long> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());

        long long ans = 0;
        for (int i = 0; i < k; ++i) ans = max(ans, v[i]);
        long long sum = 0;
        for (int i = k; i < n; ++i) sum += v[i];
        ans = max(ans, sum);

        cout << ans << endl;
    }
}

