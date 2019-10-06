#include <bits/stdc++.h>
using namespace std;

int ans2[40];

int main() {
    ans2[0] = 1;
    ans2[1] = 2;
    ans2[2] = 3;
    for (int i = 3; i <= 30; ++i) {
        int mn = (1 << i) / 2 + 1;
        for (int j = 1; j < i; ++j) mn = min(mn, ans2[j] * ans2[i - j]);
        ans2[i] = mn;
        // cout << "ans[" << i << "] = " << mn << endl;
    }
    int n; cin >> n;
    int cnt2 = 0;
    while (n % 2 == 0) n /= 2, ++cnt2;
    int ans = 1;
    for (int i = 3; i * i <= n; ++i) {
        while (n % i == 0) {
            n /= i;
            ans *= (i / 2 + 1);
        }
    }
    if (n > 1) ans *= (n / 2 + 1);
    cout << ans * ans2[cnt2] << endl;
}
