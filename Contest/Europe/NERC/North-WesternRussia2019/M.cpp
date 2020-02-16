#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

void Solve() {
    int n; scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    cc_hash_table<int, int> cnt;
    for (int i = 0; i < n; ++i) cnt[a[i]]++;
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        cnt[a[i]]--;
        for (int j = 0; j < i; ++j) {
            int diff = a[i] - a[j];
            if (cnt.find(a[i] + diff) != cnt.end()) res += cnt[a[i] + diff];
        }
    }
    printf("%lld\n", res);
}

int main() {
    int t; scanf("%d", &t);
    while (t--) Solve();
}

