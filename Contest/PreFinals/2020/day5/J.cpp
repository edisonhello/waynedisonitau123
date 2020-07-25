#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t; while (t--) {
        long long k; cin >> k;
        int t = __builtin_popcountll(k - 1);
        cout << (1ll << t) << '\n';
    }
}

