  #include <bits/stdc++.h>
  using namespace std;
   
  int n, t;
   
  vector<int> a[1000006];
  int cnt[1000006];
   
  long long check(int m) {
      // cerr << "check " << m << endl;
      for (int i = 1; i <= 1000000; ++i) cnt[i] = 0, a[i].clear();
   
      long long time = 1ll * t * (m - 1);
      for (int i = 1; i <= m; ++i) a[1].push_back(i);
      int ct = 1;
      int nn = n;
      while (nn) {
          if (a[ct].empty()) ++ct;
          else {
              --nn;
              if (ct + a[ct].back() <= 1000000)
                  a[ct + a[ct].back()].push_back(a[ct].back());
              ++cnt[a[ct].back()];
              a[ct].pop_back();
              time += ct;
          }
      }
      // cerr << "time " << time << endl;
      return time;
  }
   
  int main() {
      cin >> n >> t;
      int L = 1, R = n;
      while (R - L > 5) {
          int M = (L + R) >> 1;
          int M2 = M + 1;
          if (check(M) <= check(M2)) R = M2;
          else L = M;
      }
      int best = -1;
      long long time = LLONG_MAX;
      for (int i = L; i <= R; ++i) {
          long long z = check(i);
          if (z < time) {
              time = z;
              best = i;
          }
      }
   
      check(best);
      cout << time << '\n' << best - 1 << endl;
      int pre = 0;
      for (int i = 1; i < best; ++i) cout << (pre += cnt[i]) << " \n"[i == best - 1];
  }
