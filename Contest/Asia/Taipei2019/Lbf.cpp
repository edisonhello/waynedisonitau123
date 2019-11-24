#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<long long, long long>

int sgn(int x) {
    if (x == 0) return x;
    if (x > 0) return 1;
    return -1;
}

pair<int, int> ps[2000];
pii operator - (pii a, pii b) { return pii(a.first - b.first, a.second - b.second); }
int operator ^ (pii a, pii b) { return a.first * b.second - a.second * b.first; }

int calc(int a, int b, int c) {
    return abs((ps[b] - ps[a]) ^ (ps[c] - ps[a]));
}

int calc(int a, int b, int c, int d) {
    return (ps[a] ^ ps[b]) + (ps[b] ^ ps[c]) + (ps[c] ^ ps[d]) + (ps[d] ^ ps[a]);
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) cin >> ps[i].first >> ps[i].second;
        int ans = 0;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (j != i) 
            for (int k = 0; k < n; ++k) if (k != i && k != j) 
                for (int l = 0; l < n; ++l) if (l != i && l != j && l != k) {
                    ans = max(ans, calc(i, j, k, l));
                }
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) for (int k = j + 1; k < n; ++k) for (int l = k + 1; l < n; ++l) {
            ans = max(ans, calc(i, j, k, l));
        }
        
        if (ans % 2 == 0) cout << ans / 2 << endl;
        else cout << ans / 2 << ".5" << endl;
    }
}
