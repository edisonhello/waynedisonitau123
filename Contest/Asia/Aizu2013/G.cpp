  #include <bits/stdc++.h>
  using namespace std;
   
  const int maxn = 1e6 + 5;
  int x[maxn], y[maxn], z[maxn], dp[maxn];
   
  struct Fenwick {
      vector<int> ds;
      vector<int> bit;
      
      void Insert(int p) { ds.push_back(p); }
   
      void Compile() {
          sort(ds.begin(), ds.end());
          ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
          bit.resize(ds.size() + 1, 0);
      }
   
      void Add(int p, int v) {
          p = lower_bound(ds.begin(), ds.end(), p) - ds.begin();
          for (int i = p + 1; i < (int)bit.size(); i += i & -i)
              bit[i] = max(bit[i], v);
      }
   
      int Query(int p) {
          p = lower_bound(ds.begin(), ds.end() p) - ds.begin() - 1;
          int res = 0;
          for (int i = p + 1; i > 0; i -= i & -i)
              res = max(res, bit[i]);
          return res;
      }
  };
   
  int main() {
      int m, n, A, B; 
      while (scanf("%d%d%d%d", &m, &n, &A, &B) != EOF) {
          if (!m && !n && !A && !B) break;
          for (int i = 0; i < m; ++i) scanf("%d%d%d", &x[i], &y[i], &z[i]);
   
          /* auto Rng = [&]() {
              static int a = A, b = B, C = ~(1 << 31), M = (1 << 16) - 1;
              a = 36969 * (a & M) + (a >> 16);
              b = 18000 * (b & M) + (b >> 16);
              return (C & ((a << 16) + b)) % 1000000;
          }; */
          int a = A, b = B, C = ~(1 << 31), M = (1 << 16) - 1;
          auto Rng = [&] () {
              a = 36969 * (a & M) + (a >> 16);
              b = 18000 * (b & M) + (b >> 16);
              return (C & ((a << 16) + b)) % 1000000;
          };
   
          for (int i = 0; i < n; ++i) {
              x[i + m] = Rng();
              y[i + m] = Rng();
              z[i + m] = Rng();
          }
          vector<int> od(n + m);
          iota(od.begin(), od.end(), 0);
          sort(od.begin(), od.end(), [&](int i, int j) {
              return x[i] < x[j];
          });
   
          // for (int i = 0; i < n + m; ++i) 
          //     printf("%d %d %d\n", x[od[i]], y[od[i]], z[od[i]]);
   
          vector<int> ds(y, y + n + m);
          sort(ds.begin(), ds.end());
          ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
          for (int i = 0; i < n + m; ++i) {
              y[i] = lower_bound(ds.begin(), ds.end(), y[i]) - ds.begin();
          }
   
          vector<Fenwick> st(ds.size() * 4);
   
          function<void(int, int, int, int, int)> Insert = [&](int l, int r, int y, int z, int o) {
              st[o].Insert(z);
              if (r - l == 1) return;
              if (y < (l + r) >> 1)
                  Insert(l, (l + r) >> 1, y, z, o * 2 + 1);
              else
                  Insert((l + r) >> 1, r, y, z, o * 2 + 2);
          };
   
          function<void(int, int, int, int, int, int)> Modify = [&](int l, int r, int y, int z, int v, int o) {
              st[o].Add(z, v);
              if (r - l == 1) return;
              if (y < (l + r) >> 1)
                  Modify(l, (l + r) >> 1, y, z, v, o * 2 + 1);
              else
                  Modify((l + r) >> 1, r, y, z, v, o * 2 + 2);
          };
   
          function<int(int, int, int, int, int, int)> Query = [&](int l, int r, int ql, int qr, int z, int o) {
              if (l >= qr || ql >= r) return 0;
              if (l >= ql && r <= qr) return st[o].Query(z);
              return max(Query(l, (l + r) >> 1, ql, qr, z, o * 2 + 1),
                         Query((l + r) >> 1, r, ql, qr, z, o * 2 + 2));
          };
   
          for (int i = 0; i < n + m; ++i) Insert(0, ds.size(), y[i], z[i], 0);
          for (int i = 0; i < (int)ds.size() * 4; ++i) st[i].Compile();
          for (int i = 0, j = 0; i < n + m; ++i) {
              while (j < n + m && x[od[j]] < x[od[i]]) {
                  Modify(0, ds.size(), y[od[j]], z[od[j]], dp[od[j]], 0);
                  ++j;
              }
              if (y[od[i]] == 0) dp[od[i]] = 1;
              else dp[od[i]] = Query(0, ds.size(), 0, y[od[i]], z[od[i]], 0) + 1;
          }
          int ans = *max_element(dp, dp + n + m);
          printf("%d\n", ans);
      }
      return 0;
  }
