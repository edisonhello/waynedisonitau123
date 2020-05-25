#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    constexpr int kC = 10'000'000;
    vector<int> cnt(kC + 1);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cnt[a[i]] = 1;
    }
    sort(a.begin(), a.end());
    for (int i = n - 1; i >= 0; --i) {
        bool ok = true;
        for (int j = a[i] + a[i]; j <= kC; j += a[i]) {
            if (cnt[j]) {
                ok = false;
                break;
            }
        }
        if (!ok) cnt[a[i]] = 2;
    }
    for (int i = 0; i < n; ++i) {
        if (cnt[a[i]] == 1) {
            cout << a[i] << " ";
        }
    }
    cout << "\n";
}
