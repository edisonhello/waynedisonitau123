#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int c[1004][1004];
int p28[10005];

int solve(const vector<long long> &dig, int idx) {
    if (idx == dig.size()) {
        return 1;
    }

    return (dig[idx] * (dig[idx] + 1) / 2 * 1ll * p28[dig.size() - 1 - idx] % mod + 1ll * (dig[idx] + 1) * solve(dig, idx + 1) % mod) % mod;
    
}

int go(long long x) {
    vector<long long> dig;
    long long n = x;
    while (x) {
        dig.push_back(x % 7);
        x /= 7;
    }
    reverse(dig.begin(), dig.end());
    n %= mod;
    long long sv = solve(dig, 0);
    // cerr << "solve = " << sv << endl;
    return (((n + 1) * (n + 2) / 2 % mod - sv) % mod + mod) % mod;
}

int main() {
    // int n = 100;
    // c[0][0] = 1;
    // cout << c[0][0] << endl;
    // for (int i = 1; i <= 100; ++i) {
    //     for (int j = 0; j <= i; ++j) {
    //         c[i][j] = c[i - 1][j];
    //         if (j) c[i][j] += c[i - 1][j - 1];
    //         c[i][j] %= 7;
    //         // cout << c[i][j] << ' ';
    //         cout << (c[i][j] ? ' ' : 'o') ;
    //     }
    //     cout << endl;
    // }

    p28[0] = 1;
    for (int i = 1; i <= 10000; ++i) p28[i] = p28[i - 1] * 28ll % mod;

    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; for (int ts = 1; ts <= t; ++ts) {
        long long x; cin >> x;
        cout << "Case " << ts << ": " << go(x) << '\n';
    }
}
