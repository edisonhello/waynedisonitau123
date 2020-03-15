#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    constexpr int kMod = 998244353;
    vector<int> fc(n + 1, 1), iv(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        fc[i] = 1LL * fc[i - 1] * i % kMod;
    }

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    iv[n] = fpow(fc[n], kMod - 2);
    for (int i = n - 1; i > 0; --i) iv[i] = 1LL * iv[i + 1] * (i + 1) % kMod;

    auto Choose = [&](int n, int k) {
        if (n < k || k < 0) return 0LL;
        return 1LL * fc[n] * iv[k] % kMod * iv[n - k] % kMod;
    };

    int ans = 1;
    for (int i = 0; i < n; ++i) ans = (ans + ans) % kMod;
    ans = (ans + kMod - 1) % kMod;

    vector<int> pw(n + 1, 1);
    for (int i = 1; i <= n; ++i) pw[i] = (pw[i - 1] + pw[i - 1]) % kMod;

    for (int i = 0, j = 0; i < n; i = j) {
        for (; j < n && s[i] == s[j]; ++j);
        if (j - i == 1) continue;
        int left = i;
        int right = n - j;
        // cout << "j - i = " << j - i << endl;
        int mult = (pw[j - i] + kMod - (j - i + 1)) % kMod;
        // cout << "mult = " << mult << endl;
        ans += kMod - 1LL * Choose(left + right, left) * mult % kMod;
        ans %= kMod;
        // cout << "left = " << left << " right = " << right << endl;
        for (int k = 1; k < j - i; ++k) {
            if (j - i - k <= 1) break;
            int mult = (pw[j - i - k] + kMod - (j - i - k + 1)) % kMod;
            int sum = (Choose(left + right + k - 1, left - 1) + Choose(left + right + k - 1, right - 1)) % kMod;
            ans += kMod - 1LL * mult * sum % kMod;
            ans %= kMod;
        }
    }
    cout << ans << "\n";
    return 0;
}

