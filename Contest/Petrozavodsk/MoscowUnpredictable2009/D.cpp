#include <bits/stdc++.h>
using namespace std;

#define i128 __int128

/* template <typename T> tuple<T, T, T> extgcd(T a, T b) {
   if (!b) return make_tuple(a, 1, 0);
   T d, x, y;
   tie(d, x, y) = extgcd(b, a % b);
   return make_tuple(d, y, x - (a / b) * y);
   }

   long long fmul(long long b, long long n, long long m, long long a = 0) {
   while (n) {
   if (n & 1) a = (a + b) % m;
   b = (b + b) % m; n >>= 1;
   } return a;
   }

   i128 crt(vector<int> mod, vector<int> a) {
   i128 mult = mod[0];
   int n = (int)mod.size();
   i128 res = a[0];
   for (int i = 1; i < n; ++i) {
   i128 d, x, y;
   tie(d, x, y) = extgcd(mult, mod[i] * i128(1));
   if ((a[i] - res) % d) return -1;
   i128 new_mult = mult / __gcd(mult, i128(1) * mod[i]) * mod[i];
   res += x * ((a[i] - res) / d) % new_mult * mult % new_mult;
// res += fmul(fmul(x, ((a[i] - res) / d), new_mult), mult, new_mult);
mult = new_mult;
((res %= mult) += mult) %= mult;
}
return res;
} */

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    /* for (int i = 2; i <= 2000; ++i) {
       for (int j = 2; j <= 20000; ++j) {
       if (__gcd(i, j) != 1) pre[i][j] = 1;
       pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
       }
       }
       int n, m; cin >> n >> m;
       for (int i = 2; i <= 2000; ++i) {
       for (int j = 2; j <= 20000; ++j) {
       if (pre[i + n - 1][j + m - 1] - pre[i - 1][j + m - 1] - pre[i + n - 1][j - 1] + pre[i - 1][j - 1] == n * m) {
       cout << i << " " << j << endl;
       exit(0);
       }
       }
       } */
    /* int N = 2, M = 7;
       for (int i = 4; ; ++i) {
       for (int j = 2; i - j >= 2; ++j) {
       int n = j, m = i - j;
       bool no = false;
       for (int i = 0; i < N; ++i) {
       for (int j = 0; j < M && !no; ++j) {
       no |= __gcd(n + i, m + j) == 1;
       }
       }
       if (!no) exit((cout << n << " " << m << endl, 0));
       }
       } */
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
    {
        int n, m; cin >> n >> m;
        if (n == 1) cout << 20922789888000 << " " << 20922789888002 << endl;
        else if (n == 2) cout << 1930214 << " " << 3910712244 << endl;
        else if (n == 3) cout << 8952253471238 << " " << 10886943475680 << endl;
        else if (m == 1) cout << 20922789888002 << " " << 20922789888000 << endl;
        else if (m == 2) cout << 3910712244 << " " << 1930214 << endl;
        else if (m == 3) cout << 10886943475680 << " " << 8952253471238 << endl;
        exit(0);
    }
    /* {
       long long n = 20922789888000, m = 20922789888002;
       for (int i = 0; i < 15; ++i) assert(__gcd(n, m + i) > 1);
       n = 1930214, m = 3910712244;
       for (int i = 0; i < 2; ++i) for (int j = 0; j < 7; ++j) cerr << n + i << " , " << m + j << " , " << __gcd(n + i, m + j) << endl;
       n = 8952253471238, m = 10886943475680;
       for (int i = 0; i < 3; ++i) for (int j = 0; j < 5; ++j) cerr << n + i << " , " << m + j << " , " << __gcd(n + i, m + j) << endl; 
       }
       int n, m; cin >> n >> m;
       long long m2 = crt(vector<int>({2, 3, 5, 11, 7, 13, 593, 17, 31}), 
       vector<int>({0, 0, 4, 10, 5, 10, 588, 12, 27})); 
       long long n3 = crt(vector<int>({2, 7, 11, 3, 13, 17, 23, 5, 29, 31, 37, 41}),
       vector<int>({0, 0, 0, 2, 12, 16, 22, 3, 27, 29, 35, 39}));
       long long m3 = crt(vector<int>({2, 3, 5, 7, 13, 29, 2, 17, 31, 11, 3, 37, 2, 23, 41}),
       vector<int>({0, 0, 0, 6, 12, 28, 0, 15, 29, 8, 0, 34, 0, 19, 37}));
       if (n == 1) {
       cout << 1ll * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 << " "
       << 1ll * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 + 2 << endl;
       } else if (n == 2) {
       cout << 1930214 << " " << m2 << endl;
       } else if (n == 3) {
       cout << n3 << " " << m3 << endl;
       } else if (m == 1) {
       cout << 1ll * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 + 2 << " "
       << 1ll * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 << endl;
       } else if (m == 2) {
       cout << m2 << " " << 1930214 << endl;
       } else if (m == 3) {
       cout << m3 << " " << n3 << endl;
       } */
}
