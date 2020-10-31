#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; 
    for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        sort(v.begin(), v.end(), greater<int>());
        int tot = 0;
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 2) continue;
            tot += v[i];
        }
        cout << tot << '\n';
    }
}

