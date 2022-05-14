#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

vector<vector<tuple<int, int, int>>> Trim(
    vector<vector<tuple<int, int, int>>> g, vector<int64_t>& psol) {
  int N = g.size();
  vector<bool> vis(N);
  constexpr int kP = 1'000'000'000 + 123;
  vector<int> A(N), B(N), C(N), D(N);
  vector<int64_t> sol(N, -1);
  vector<vector<tuple<int, int, int>>> ng(N);
  for (int i = 0; i < N; ++i) {
    if (vis[i]) {
      continue;
    }
    vector<int> que = {i};
    vis[i] = true;
    // (Ax + B) / (Cx + D)
    A[i] = 1;
    B[i] = 0;
    C[i] = 0;
    D[i] = 1;
    for (int it = 0; it < que.size(); ++it) {
      int x = que[it];
      for (auto [u, a, b] : g[x]) {
        if (vis[u]) {
          continue;
        }
        if (a == 0) {
          int AA = 1LL * b * C[x] % kP;
          int BB = 1LL * b * D[x] % kP;
          A[u] = (AA + kP - A[x]) % kP;
          B[u] = (BB + kP - B[x]) % kP;
          C[u] = C[x];
          D[u] = D[x];
        } else if (a == 1) {
          int AA = 1LL * b * C[x] % kP;
          int BB = 1LL * b * D[x] % kP;
          A[u] = (A[x] + kP - AA) % kP;
          B[u] = (B[x] + kP - BB) % kP;
          C[u] = C[x];
          D[u] = D[x];
        } else {
          C[u] = A[x];
          D[u] = B[x];
          A[u] = 1LL * C[x] * b % kP;
          B[u] = 1LL * D[x] * b % kP;
        }
        vis[u] = true;
        que.push_back(u);
      }
    }
    int a1 = -1, b1 = -1, c1 = -1;
    int a2 = -1, b2 = -1, c2 = -1;

    auto fpow = [&](int a, int n) {
      int res = 1;
      while (n > 0) {
        if (n & 1) res = 1LL * res * a % kP;
        a = 1LL * a * a % kP;
        n >>= 1;
      }
      return res;
    };

    auto Equiv = [&](int a1, int b1, int c1, int a2, int b2, int c2) -> int {
      if (a1 == 0 && a2 == 0) {
        int t = 1LL * b1 * fpow(b2, kP - 2) % kP;
        b2 = 1LL * b2 * t % kP;
        c2 = 1LL * c2 * t % kP;
        assert(b1 == b2);
        if (c1 == c2) {
          return 1;
        } else {
          return -1;
        }
      }
      if (a1 == 0 || a2 == 0) {
        return 0;
      }
      int t = 1LL * a1 * fpow(a2, kP - 2) % kP;
      a2 = 1LL * a2 * t % kP;
      b2 = 1LL * b2 * t % kP;
      c2 = 1LL * c2 * t % kP;
      assert(a1 == a2);
      b1 = (b1 + kP - b2) % kP;
      c1 = (c1 + kP - c2) % kP;
      if (b1 == 0) {
        if (c1 == 0) {
          return 1;
        } else {
          return -1;
        }
      }
      return 0;
    };

    for (int x : que) {
      for (auto [u, a, b] : g[x]) {
        int aa = -1, bb = -1, cc = -1;
        if (a == 0) {
          aa = (1LL * A[x] * C[u] + 1LL * C[x] * A[u] + kP -
                (1LL * b * C[x] % kP * C[u] % kP)) %
               kP;
          bb = (1LL * B[x] * C[u] + 1LL * A[x] * D[u] + 1LL * B[u] * C[x] +
                1LL * A[u] * D[x] + kP -
                (1LL * b * C[x] % kP * D[u] % kP +
                 1LL * b * C[u] % kP * D[x] % kP) %
                    kP) %
               kP;
          cc = (1LL * B[x] * D[u] + 1LL * B[u] * D[x] + kP -
                (1LL * b * D[x] % kP * D[u] % kP)) %
               kP;
        } else if (a == 1) {
          A[u] = kP - A[u];
          B[u] = kP - B[u];
          aa = (1LL * A[x] * C[u] + 1LL * C[x] * A[u] + kP -
                (1LL * b * C[x] % kP * C[u] % kP)) %
               kP;
          bb = (1LL * B[x] * C[u] + 1LL * 1LL * A[x] * D[u] +
                1LL * B[u] * C[x] + 1LL * A[u] * D[x] + kP -
                (1LL * b * C[x] % kP * D[u] % kP +
                 1LL * b * C[u] % kP * D[x] % kP) %
                    kP) %
               kP;
          cc = (1LL * B[x] * D[u] + 1LL * B[u] * D[x] + kP -
                (1LL * b * D[x] % kP * D[u] % kP)) %
               kP;
          A[u] = kP - A[u];
          B[u] = kP - B[u];
        } else {
          aa = (1LL * A[x] * A[u] + kP - 1LL * b * C[x] % kP * C[u] % kP) % kP;
          bb =
              (1LL * A[x] * B[u] + 1LL * B[x] * A[u] + kP -
               (1LL * b * C[x] % kP * D[u] + 1LL * b * C[u] % kP * D[x]) % kP) %
              kP;
          cc =
              (1LL * B[x] * B[u] + (kP - 1LL * b * D[x] % kP * D[u] % kP)) % kP;
        }
        if (aa == 0 && bb == 0) {
          if (cc != 0) {
            return {};
          } else {
            continue;
          }
        }
        if (a1 == -1) {
          a1 = aa;
          b1 = bb;
          c1 = cc;
        } else if (a2 == -1) {
          int eq = Equiv(a1, b1, c1, aa, bb, cc);
          if (eq == -1) {
            return {};
          }
          if (eq == 0) {
            a2 = aa;
            b2 = bb;
            c2 = cc;
          }
        }
      }
    }

    // cerr << "root = " << i << endl;
    // cerr << "a1 = " << a1 << " b1 = " << b1 << " c1 = " << c1 << endl;
    // cerr << "a2 = " << a2 << " b2 = " << b2 << " c2 = " << c2 << endl;

    if (a1 == -1) {
      for (int x : que) {
        vis[x] = false;
      }
      que.clear();
      que = {i};
      vis[i] = true;
      for (int it = 0; it < que.size(); ++it) {
        int x = que[it];
        for (auto [u, a, b] : g[x]) {
          if (!vis[u]) {
            ng[x].emplace_back(u, a, b);
            if (a == 1) {
              b = -b;
            }
            ng[u].emplace_back(x, a, b);
            vis[u] = true;
            que.push_back(u);
          }
        }
      }
    } else {
      if (a2 == -1 && a1 != 0) {
        bool has_edge = false;
        for (int x : que) {
          vis[x] = false;
        }
        que.clear();
        que = {i};
        vis[i] = true;
        for (int it = 0; it < que.size(); ++it) {
          int x = que[it];
          for (auto [u, a, b] : g[x]) {
            if (!vis[u]) {
              ng[x].emplace_back(u, a, b);
              if (a == 1) {
                b = -b;
              }
              ng[u].emplace_back(x, a, b);
              vis[u] = true;
              que.push_back(u);
            } else if (!has_edge) {
              ng[x].emplace_back(u, a, b);
              if (a == 1) {
                b = -b;
              }
              ng[u].emplace_back(x, a, b);
              vis[u] = true;
              que.push_back(u);
              has_edge = true;
            }
          }
        }
      } else {
        int xv = -1;
        if (a1 == 0) {
          xv = 1LL * (kP - c1) * fpow(b1, kP - 2) % kP;
        } else if (a2 == 0) {
          xv = 1LL * (kP - c2) * fpow(b2, kP - 2) % kP;
        } else {
          int t = 1LL * a1 * fpow(a2, kP - 2) % kP;
          a2 = 1LL * a2 * t % kP;
          b2 = 1LL * b2 * t % kP;
          c2 = 1LL * c2 * t % kP;
          assert(a1 == a2);
          b1 = (b1 + kP - b2) % kP;
          c1 = (c1 + kP - c2) % kP;
          assert(b1 != 0);
          xv = 1LL * (kP - c1) * fpow(b1, kP - 2) % kP;
        }
        if (xv == 0) {
          return {};
        }
        for (int x : que) {
          vis[x] = false;
        }
        que.clear();
        que = {i};
        vis[i] = true;
        sol[i] = xv;
        for (int it = 0; it < que.size(); ++it) {
          int x = que[it];
          for (auto [u, a, b] : g[x]) {
            int ex = -1;
            if (a == 0) {
              if (b > sol[x]) {
                ex = b - sol[x];
              }
            } else if (a == 1) {
              if (b < sol[x]) {
                ex = sol[x] - b;
              }
            } else {
              if (b % sol[x] == 0) {
                ex = b / sol[x];
              }
            }
            if (ex == -1) {
              return {};
            }
            if (!vis[u]) {
              sol[u] = ex;
              vis[u] = true;
              que.push_back(u);
            } else {
              if (sol[u] != ex) {
                return {};
              }
            }
          }
        }
        for (int x : que) {
          psol[x] = sol[x];
        }
      }
    }
  }
  return ng;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  vector<vector<int>> dv(1'000'000 + 1);
  for (int d = 1; d <= 1'000'000; ++d) {
    for (int i = d; i <= 1'000'000; i += d) {
      dv[i].push_back(d);
    }
  }
  // cerr << "done" << endl;
  for (int tc = 1; tc <= T; ++tc) {
    int N, M;
    cin >> N >> M;
    vector<vector<tuple<int, int, int>>> g(N);
    for (int i = 0; i < M; ++i) {
      string s;
      cin >> s;
      int x = 0;
      int j = 0;
      while (j < s.size() && isdigit(s[j])) {
        x = x * 10 + (s[j] - '0');
        j++;
      }
      int type = (s[j] == '+' ? 0 : (s[j] == '-' ? 1 : 2));
      j++;
      int y = 0;
      while (j < s.size() && isdigit(s[j])) {
        y = y * 10 + (s[j] - '0');
        j++;
      }
      assert(s[j] == '=');
      j++;
      int z = 0;
      while (j < s.size() && isdigit(s[j])) {
        z = z * 10 + (s[j] - '0');
        j++;
      }
      assert(j == s.size());
      assert(1 <= x && x <= N);
      assert(1 <= y && y <= N);
      x--;
      y--;
      g[x].emplace_back(y, type, z);
      if (type == 1) z = -z;
      g[y].emplace_back(x, type, z);
    }
    vector<int64_t> psol(N, -1);
    g = Trim(g, psol);
    if (g.empty()) {
      cout << "Case " << tc << ": 0\n";
      continue;
    }
    constexpr int kP = 1'000'000'000 + 7;
    vector<bool> vis(N);
    vector<int> val(N, -1);
    int ans = 1;
    vector<int64_t> sol(N, -1);
    vector<pair<int, int64_t>> poly(N);
    vector<int> mark(N, -1);
    bool inf = false;
    vector<int64_t> tmp(N, -1);
    vector<int64_t> latest(N, -1);

    auto Simplify = [&](int root) -> tuple<int64_t, int64_t, int64_t, bool> {
      // cerr << "Simplify root = " << root << endl;
      poly[root] = {1, 0};
      mark[root] = root;
      vis[root] = true;
      vector<int> que = {root};
      for (int it = 0; it < que.size(); ++it) {
        int x = que[it];
        for (auto [u, a, b] : g[x]) {
          if (!vis[u]) {
            if (a == 0) {
              poly[u] = {-poly[x].first, b - poly[x].second};
              vis[u] = true;
              mark[u] = root;
              que.push_back(u);
            } else if (a == 1) {
              poly[u] = {poly[x].first, poly[x].second - b};
              vis[u] = true;
              mark[u] = root;
              que.push_back(u);
            }
          }
        }
      }
      int64_t ub = 1'000'000'000'000'000'000;
      int64_t lb = 1;
      int64_t sx = 1'000'000'000'000'000'000;
      bool failed = false;
      for (int x : que) {
        assert(poly[x].first == 1 || poly[x].first == -1);
        // cout << "x = " << x << " poly = " << poly[x].first << " " <<
        // poly[x].second << endl;
        if (poly[x].first == 1) {
          lb = max(lb, 1 - poly[x].second);
        } else {
          ub = min(ub, poly[x].second - 1);
        }
        for (auto [u, a, b] : g[x]) {
          if (a == 2) {
            continue;
          }
          if (a == 0) {
            int64_t g = poly[x].second + poly[u].second;
            if (poly[x].first == 1 && poly[u].first == 1) {
              if (g >= b || (b - g) % 2 != 0) {
                failed = true;
                break;
              }
              int64_t s = (b - g) / 2;
              if (sx == 1'000'000'000'000'000'000) {
                sx = s;
              } else if (sx != s) {
                failed = true;
                break;
              }
            } else if (poly[x].first + poly[u].first == 0) {
              int64_t g = poly[x].second + poly[u].second;
              if (g != b) {
                failed = true;
                break;
              }
            } else {
              if (g <= b || (g - b) % 2 != 0) {
                failed = true;
                break;
              }
              int64_t s = (g - b) / 2;
              if (sx == 1'000'000'000'000'000'000) {
                sx = s;
              } else if (sx != s) {
                failed = true;
                break;
              }
            }
          } else {
            assert(a == 1);
            int64_t g = poly[x].second - poly[u].second;
            if (poly[x].first == 1 && poly[u].first == -1) {
              if (g >= b || (b - g) % 2 != 0) {
                failed = true;
                break;
              }
              int64_t s = (b - g) / 2;
              if (sx == 1'000'000'000'000'000'000) {
                sx = s;
              } else if (sx != s) {
                failed = true;
                break;
              }
            } else if (poly[x].first - poly[u].first == 0) {
              int64_t g = poly[x].second - poly[u].second;
              if (g != b) {
                failed = true;
                break;
              }
            } else {
              if (g <= b || (g - b) % 2 != 0) {
                failed = true;
                break;
              }
              int64_t s = (g - b) / 2;
              if (sx == 1'000'000'000'000'000'000) {
                sx = s;
              } else if (sx != s) {
                failed = true;
                break;
              }
            }
          }
        }
        if (failed) {
          break;
        }
      }
      return {lb, ub, sx, failed};
    };

    vector<tuple<int64_t, int64_t, int64_t, bool>> info(N);

    vector<vector<tuple<int, int, int>>> sg(N);
    vector<vector<int>> nd(N);

    for (int i = 0; i < N; ++i) {
      if (vis[i] || psol[i] != -1) {
        continue;
      }
      vector<int> que = {i};
      vis[i] = true;
      int mult_x = -1, mult_y = -1, mult_z = -1;
      for (int it = 0; it < que.size(); ++it) {
        int x = que[it];
        for (auto [u, a, b] : g[x]) {
          if (a == 2) {
            mult_x = x;
            mult_y = u;
            mult_z = b;
          }
          if (!vis[u]) {
            vis[u] = true;
            que.push_back(u);
          }
        }
      }
      if (mult_x == -1) {
        for (int u : que) {
          vis[u] = false;
        }
        auto [lb, ub, sx, failed] = Simplify(i);
        if (failed || lb > ub) {
          ans = 0;
          break;
        }
        if (sx == 1'000'000'000'000'000'000) {
          if (ub == 1'000'000'000'000'000'000) {
            inf = true;
          } else {
            ans = 1LL * ans * ((ub - lb + 1) % kP) % kP;
            if (ub == lb) {
              for (int x : que) {
                sol[x] = poly[x].first * lb + poly[x].second;
              }
            }
          }
        } else {
          if (sx < lb || sx > ub) {
            ans = 0;
            break;
          } else {
            for (int x : que) {
              sol[x] = sx * poly[x].first + poly[x].second;
            }
          }
        }
      } else {
        // cerr << "here" << endl;
        // cerr << "que = ";
        for (int u : que) {
          // cerr << u << " ";
          vis[u] = false;
        }
        // cerr << endl;
        bool failed = false;
        for (int u : que) {
          if (!vis[u]) {
            info[u] = Simplify(u);
            if (get<3>(info[u]) || get<0>(info[u]) > get<1>(info[u])) {
              failed = true;
              break;
            }
          }
        }
        // cerr << "here" << endl;
        if (failed) {
          ans = 0;
          break;
        }
        for (int u : que) {
          assert(vis[u]);
          assert(mark[u] != -1);
          nd[mark[u]].push_back(u);
        }

        for (int x : que) {
          for (auto [u, a, b] : g[x]) {
            if (a == 2) {
              sg[mark[x]].emplace_back(x, u, b);
            }
          }
        }
        // cerr << "here" << endl;

        auto Fill = [&](int root, int x, int v) {
          int xv = 0;
          if (poly[x].first == 1) {
            xv = v - poly[x].second;
          } else {
            xv = poly[x].second - v;
          }
          auto [lb, ub, sx, failed] = info[root];
          if (xv < lb || xv > ub) {
            return false;
          }
          if (sx != 1'000'000'000'000'000'000 && sx != xv) {
            return false;
          }
          for (int u : nd[root]) {
            tmp[u] = poly[u].first * xv + poly[u].second;
          }
          return true;
        };

        auto Try = [&](int dv) {
          // cerr << "Try dv = " << dv << endl;
          vector<int> que = {mark[mult_x]};
          auto Work = [&]() {
            if (!Fill(mark[mult_x], mult_x, dv)) {
              return false;
            }
            for (int it = 0; it < que.size(); ++it) {
              int x = que[it];
              for (auto [from, to, ed] : sg[x]) {
                if (ed % tmp[from] != 0) {
                  return false;
                }
                if (tmp[to] == -1) {
                  if (!Fill(mark[to], to, ed / tmp[from])) {
                    return false;
                  }
                  que.push_back(mark[to]);
                } else {
                  if (tmp[to] * tmp[from] != ed) {
                    return false;
                  }
                }
              }
            }
            return true;
          };
          bool suc = Work();
          for (int x : que) {
            for (int u : nd[x]) {
              if (suc) latest[u] = tmp[u];
              tmp[u] = -1;
            }
          }
          return suc;
        };

        int ways = 0;
        for (int dv : dv[mult_z]) {
          if (Try(dv)) {
            if (ways == 0) {
              // cerr << "good dv = " << dv << endl;
              for (int x : que) {
                sol[x] = latest[x];
              }
            }
            ways++;
          }
        }
        ans = 1LL * ans * ways % kP;
      }
    }
    if (inf && ans != 0) {
      ans = -1;
    }
    cout << "Case " << tc << ": " << ans;
    if (ans == 1) {
      for (int i = 0; i < N; ++i) {
        if (psol[i] != -1) {
          assert(sol[i] == -1);
          sol[i] = psol[i];
        }
        cout << " " << sol[i];
      }
    }
    cout << "\n";
  }
}
