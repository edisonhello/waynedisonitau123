#include <bits/stdc++.h>
using namespace std;

const int mod = 1'000'000'007;
const int ppow = 133;

int pp[100006];
int ipp[100005];

int pw(int b, int n) {
  int a = 1;
  while (n) {
    if (n & 1) a = 1ll * a * b % mod;
    b = 1ll * b * b % mod;
    n >>= 1;
  }
  return a;
}

int inv(int x) { return pw(x, mod - 2); }

int main() {
  pp[0] = 1;
  for (int i = 1; i <= 100000; ++i) pp[i] = 1ll * pp[i - 1] * ppow % mod;
  ipp[100000] = inv(pp[100000]);
  for (int i = 99999; i >= 0; --i) ipp[i] = 1ll * ipp[i + 1] * ppow % mod;
  string s;
  cin >> s;
  for (int i = 0, j = s.size() - 1; i <= j; ++i, --j) {
    if (s[i] != s[j]) {
      int offs = i;
      // cout << "offs = " << offs << endl;

      string ss = s.substr(i, j - i + 1);

      int nn = ss.size();

      vector<int> hh(nn);
      vector<int> ihh(nn);

      hh[0] = ss[0];
      for (int i = 1; i < nn; ++i) {
        hh[i] = (hh[i - 1] + ss[i] * 1ll * pp[i]) % mod;
      }
      ihh.back() = ss.back();
      for (int i = nn - 2; i >= 0; --i) {
        ihh[i] = (ihh[i + 1] + ss[i] * 1ll * pp[nn - 1 - i]) % mod;
      }

      // cout << "hh = ";
      // for (int i = 0; i < nn; ++i) {
      //   cout << hh[i] << ' ';
      // }
      // cout << endl;
      // cout << "ihh = ";
      // for (int i = 0; i < nn; ++i) {
      //   cout << ihh[i] << ' ';
      // }
      // cout << endl;

      auto gethh = [&](int l, int r) {
        // cout << "gethh " << l << ' ' << r << endl;
        return (hh[r] - (l ? hh[l - 1] : 0) + mod) * 1ll * ipp[l] % mod;
      };
      auto getihh = [&](int l, int r) {
        // cout << "getihh " << l << ' ' << r << endl;
        return (ihh[l] - (r == nn - 1 ? 0 : ihh[r + 1]) + mod) * 1ll *
               ipp[nn - 1 - r] % mod;
      };

      for (int i = 0; i < nn; ++i) {
        // cout << "i = " << i << endl;
        // cout << "flip " << 0 << " " << i << endl;
        int pos = (getihh(0, i) + gethh(i + 1, nn - 1) * 1ll * pp[i + 1]) % mod;
        int neg = (getihh(i + 1, nn - 1) + gethh(0, i) * 1ll * pp[nn - i - 1]) % mod;
        if (pos == neg) {
          cout << offs + 1 << ' ' << offs + 1 + i << endl;
          exit(0);
        }

        // cout << "flip " << i + 1 << " " << nn - 1 << endl;
        int pos2 = (gethh(0, i) + getihh(i + 1, nn - 1) * 1ll * pp[i + 1]) % mod;
        int neg2 = (gethh(i + 1, nn - 1) + getihh(0, i) * 1ll * pp[nn - i - 1]) % mod;
        if (pos2 == neg2) {
          cout << offs + 1 + (i + 1) << ' ' << offs + 1 + (nn - 1) << endl;
          exit(0);
        }
      }

      // int hlen = nn / 2;
      // // flip [0 ~ i]
      // for (int i = 0; i < hlen; ++i) {
      //   cout << "i = " << i << endl;
      //   cout << "turn l" << endl;
      //   int lval =
      //       (getihh(0, i) + gethh(i + 1, hlen - 1) * 1ll * pp[i + 1]) % mod;
      //   cout << "ihh 0 ~ " << i << " + hh " << i + 1 << " ~ " << hlen - 1
      //        << endl;
      //   int rval = getihh(nn - hlen, nn - 1);
      //   cout << "ihh " << nn - hlen << " ~ " << nn - 1 << endl;
      //   if (lval == rval) {
      //     cout << offs + 1 << ' ' << offs + i + 1 << endl;
      //     exit(0);
      //   }
      // }
      // for (int i = 0; i < hlen; ++i) {
      //   cout << "i = " << i << endl;
      //   cout << "turn r" << endl;
      //   int lval =
      //       (gethh(0, i) + getihh(i + hlen + 2, nn - 1) * 1ll * pp[i + 1]) %
      //       mod;
      //   cout << "hh 0 ~ " << i << " + ihh " << i + hlen + 2 << " ~ " << nn - 1
      //        << endl;
      //   int rval = getihh(i + 1, i + hlen);
      //   cout << "ihh " << i + 1 << " ~ " << i + hlen << endl;
      //   if (lval == rval) {
      //     cout << offs + 1 << ' ' << offs + i + 1 << endl;
      //     exit(0);
      //   }
      // }
      // for (int i = hlen; i < nn; ++i) {
      //   {
      //     int lval = getihh(i - hlen + 1, i);
      //     int rval = (getihh(0, i - hlen) +
      //                 gethh(i + 1, nn - 1) * 1ll * pp[i - hlen + 1]) %
      //                mod;
      //     if (lval == rval) {
      //       cout << offs + 1 << ' ' << offs + i + 1 << endl;
      //       exit(0);
      //     }
      //   }
      //   {
      //     int lval = gethh(0, hlen);
      //     int rval = (gethh(i + 1, nn - 1) +
      //                 getihh(hlen, i) * 1ll * pp[nn - (i + 1)]) %
      //                mod;
      //     if (lval == rval) {
      //       cout << offs + 1 << ' ' << offs + i + 1 << endl;
      //       exit(0);
      //     }
      //   }
      // }
      cout << "-1 -1" << endl;
      exit(0);
    }
  }
  cout << "1 1" << endl;
  exit(0);
}

