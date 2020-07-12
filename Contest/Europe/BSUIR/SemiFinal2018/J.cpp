#include <bits/stdc++.h>
#define double long double
using namespace std;

int t[50005];
double p1[50005], p2[50005];
double missprob[50005][21];
int fac[15];

int C(int n, int m) { return fac[n] / fac[m] / fac[n - m]; }
double pw(double b, int n) {
  double a = 1;
  while (n) {
    if (n & 1) a = a * b;
    b = b * b; n >>= 1;
  }
  return a;
}

int main() {
  fac[0] = 1;
  for (int i = 1; i < 15; ++i) fac[i] = fac[i - 1] * i;

  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> t[i] >> p1[i] >> p2[i];
    t[i] *= 5;
  }

  auto CalcProb = [&] (int z1, int z2, double p1, double p2) {
    return C(10, z1) * pw(p1, z1) * pw(1 - p1, 10 - z1) * 
           C(10, z2) * pw(p2, z2) * pw(1 - p2, 10 - z2);
  };
  auto ThisProb = [&] (int z1, int z2) {
    return CalcProb(z1, z2, p1[1], p2[1]);
  };

  for (int i = 2; i <= n; ++i) {
    for (int z1 = 0; z1 <= 10; ++z1) {
      for (int z2 = 0; z2 <= 10; ++z2) {
        int miss = 20 - z1 - z2;
        missprob[i][miss] += CalcProb(z1, z2, p1[i], p2[i]);
      }
    }

    for (int z = 1; z <= 20; ++z) missprob[i][z] += missprob[i][z - 1];
  }

  double ans = 0;
  for (int z1 = 0; z1 <= 10; ++z1) {
    for (int z2 = 0; z2 <= 10; ++z2) {
      double pp = ThisProb(z1, z2);
      int tt = t[1] + (20 - z1 - z2) * 60;

      // cerr << "z1 z2 pp " << z1 << ' ' << z2 << ' ' << pp << endl;

      vector<double> lp;
      for (int i = 2; i <= n; ++i) {
        if (t[i] >= tt) lp.push_back(0);
        else {
          int miss = (tt - t[i] - 1) / 60;
          miss = min(miss, 20);
          lp.push_back(missprob[i][miss]);
        }
      }
      // sort(lp.rbegin(), lp.rend());

      // cerr << "lp: ";
      // for (double i : lp) cerr << i << ' ';
      // cerr << endl;

      vector<vector<double>> dp(3, vector<double>(n + 1, 0));
      dp[0][1] = 1;
      for (int y = 0; y < 3; ++y) {
        for (int i = 2; i <= n; ++i) {
          dp[y][i] = dp[y][i - 1] * (1 - lp[i - 2]);
          if (y) dp[y][i] += dp[y - 1][i - 1] * lp[i - 2];

          // cerr << "dp y i " << y << ' ' << i << ' ' << dp[y][i] << endl;
        }
      }

      // cerr << "pp dps " << pp << ' ' << dp[0][n] + dp[1][n] + dp[2][n] << endl;
      ans += pp * (dp[0][n] + dp[1][n] + dp[2][n]);
    }
  }

  cout << fixed << setprecision(20) << ans << endl;
}
