#include <bits/stdc++.h>
#define BigInteger int64_t
using namespace std;
 
int a[30];
 
int block[30];
int blocksize[30];
int blockused[30];
 
const int mod[3] = {
    1000000007, 1000000009, 1000000123
};
 
void set_belong(int i, int id) {
    block[i] = id;
    blocksize[id]++;
}
 
// struct BigInteger {
//     vector<int> dig;
//     BigInteger() {
//         dig.push_back(0);
//     }
//     BigInteger(vector<int> &&d) : dig(move(d)) {}
//     BigInteger operator+(const BigInteger &d) const {
//         vector<int> dd(max(dig.size(), d.dig.size()));
//         for (int i = 0; i < dd.size(); ++i) {
//             if (i < dig.size()) dd[i] += dig[i];
//             if (i < d.dig.size()) dd[i] += d.dig[i];
//         }
//         int cr = 0;
//         for (int i = 0; i < dd.size(); ++i) {
//             int x = (dd[i] + cr) % 10;
//             cr = (dd[i] + cr) / 10;
//             dd[i] = x;
//         }
//         if (cr > 0) dd.push_back(cr);
//         return BigInteger(move(dd));
//     }
//     BigInteger operator*(const BigInteger &d) const {
//         vector<int> dd(dig.size() + d.dig.size() - 1);
//         for (int i = 0; i < dig.size(); ++i) {
//             for (int j = 0; j < d.dig.size(); ++j)
//                 dd[i + j] += dig[i] * d.dig[j];
//         }
//         int cr = 0;
//         for (int i = 0; i < dd.size(); ++i) {
//             int x = (dd[i] + cr) % 10;
//             cr = (dd[i] + cr) / 10;
//             dd[i] = x;
//         }
//         while (cr > 0) {
//             dd.push_back(cr % 10);
//             cr /= 10;
//         }
//         return BigInteger(move(dd));
//     }
//     BigInteger(int x) {
//         while (x > 0) {
//             dig.push_back(x % 10);
//             x /= 10;
//         }
//     }
// };
 
unordered_map<int, BigInteger> rec[30][30];
BigInteger dfs(int now, int n, int put, int prv) {
    // cout << "dfs " << now << " " << prv << endl;
    if (now > n) { return BigInteger(1); }
    if (rec[now][prv].count(put)) return rec[now][prv][put];
    BigInteger ans(0);
    if (now & 1) {
        int prun = 0;
        for (int i = n, c = 0; i >= n / 2 + 1; --i, ++c) {
            if (c % 2 == 0) prun = 0;
            if (prv >= 2 * i || i >= 2 * prv);
            else { prun = 0; continue; }
            if (put & (1 << i)) { prun = 0; continue; }
            if (a[now] == 0 || block[a[now]] == block[i]) {
                if (!prun) ans = ans + dfs(now + 1, n, put | (1 << i), i), prun = 1;
                else prun = 0;
            } else prun = 0;
        }
    } else {
        int run = 0;
        for (int i = 1; i <= n / 2; ++i) {
            if (prv >= 2 * i || i >= 2 * prv);
            else continue;
            if (put & (1 << i)) continue;
            if (a[now] == 0 || block[a[now]] == block[i]) {
                if (i <= (n / 2) / 2 && run) continue;
                ans = ans + dfs(now + 1, n, put | (1 << i), i), ++run;
            }
        }
    }
    return rec[now][prv][put] = ans;
}
 
BigInteger fac[30];
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    fac[0] = BigInteger(1);
    for (int i = 1; i < 30; ++i) fac[i] = fac[i - 1] * i;
    int n; cin >> n;
    int k = n / 2;
    int st = 0;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    // for (int i = 1; i <= n; ++i) if (a[i]) st |= 1 << a[i];
    for (int i = 1; i <= n / 2 / 2; ++i) set_belong(i, 1);
    for (int i = n / 2 / 2 + 1; i < (k & 1 ? k + 1: k + 2); ++i) set_belong(i, i);
    for (int i = (k & 1 ? k + 1 : k + 2); i <= n; ++i) set_belong(i, ((i ^ n) & 1 ? i + 1 : i));
    // for (int i = 1; i <= n; ++i) cout << i << " belongs to block " << block[i] << endl;
    for (int i = 1; i <= n; ++i) if (a[i]) ++blockused[block[a[i]]];
    // for (int i = 1; i <= n; ++i) cout << "bu = " << 
    BigInteger ans = dfs(1, n, st, n * 2);
    for (int i = 1; i <= n; ++i) ans = ans * (fac[blocksize[i] - blockused[i]]);
    // for (int i = 1; i <= n; ++i) cout << "s " << (blocksize[i] - blockused[i]) << endl;
 //   while (ans.dig.size()) cout << ans.dig.back(), ans.dig.pop_back();
    cout << ans << endl;
}
