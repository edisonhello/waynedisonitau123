#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
      cin >> grid[i];
    }
    vector<set<pair<int, int>>> horz(N);
    vector<set<pair<int, int>>> vert(M);
    for (int i = 0; i < N; ++i) {
      for (int j = 0, k = 0; j < M; j = k) {
        if (grid[i][j] == '.') {
          k = j + 1;
        } else {
          while (k < M && grid[i][k] == '#') {
            k++;
          }
          horz[i].emplace(j, k);
        }
      }
    }
    for (int i = 0; i < M; ++i) {
      for (int j = 0, k = 0; j < N; j = k) {
        if (grid[j][i] == '.') {
          k = j + 1;
        } else {
          while (k < N && grid[k][i] == '#') {
            k++;
          }
          vert[i].emplace(j, k);
        }
      }
    }
    cout << "Case #" << tc << ":\n";

    while (Q--) {
      int t, x, y;
      cin >> t >> x >> y;
      x--;
      y--;
      if (t == 1) {
        if (grid[x][y] == '#') {
          {
            auto iter = horz[x].lower_bound(make_pair(y, M + 1));
            assert(iter != horz[x].begin());
            iter = prev(iter);
            int l = iter->first, r = iter->second;
            horz[x].erase(iter);
            if (l < y) horz[x].emplace(l, y);
            if (y + 1 < r) horz[x].emplace(y + 1, r);
          }
          {
            auto iter = vert[y].lower_bound(make_pair(x, N + 1));
            assert(iter != vert[y].begin());
            iter = prev(iter);
            int l = iter->first, r = iter->second;
            vert[y].erase(iter);
            if (l < x) vert[y].emplace(l, x);
            if (x + 1 < r) vert[y].emplace(x + 1, r);
          }
          grid[x][y] = '.';
        } else {
          {
            int l = y, r = y + 1;
            if (y > 0 && grid[x][y - 1] == '#') {
              auto iter = prev(horz[x].lower_bound(make_pair(y - 1, M + 1)));
              l = iter->first;
              horz[x].erase(iter);
            }
            if (y + 1 < M && grid[x][y + 1] == '#') {
              auto iter = prev(horz[x].lower_bound(make_pair(y + 1, M + 1)));
              r = iter->second;
              horz[x].erase(iter);
            }
            horz[x].emplace(l, r);
          }
          {
            int l = x, r = x + 1;
            if (x > 0 && grid[x - 1][y] == '#') {
              auto iter = prev(vert[y].lower_bound(make_pair(x - 1, N + 1)));
              l = iter->first;
              vert[y].erase(iter);
            }
            if (x + 1 < N && grid[x + 1][y] == '#') {
              auto iter = prev(vert[y].lower_bound(make_pair(x + 1, N + 1)));
              r = iter->second;
              vert[y].erase(iter);
            }
            vert[y].emplace(l, r);
          }
          grid[x][y] = '#';
        }
      } else {
        int ans = 0;
        if (grid[x][y] == '.') {
          cout << "0\n";
          continue;
        }
        {
          auto iter = horz[x].lower_bound(make_pair(y, M + 1));
          assert(iter != horz[x].begin());
          iter = prev(iter);
          ans = max(ans, iter->second - iter->first);
          int l = iter->first, r = iter->second;
          {
            // cout << "here" << endl;
            vector<int> up(M), order(r - l);
            for (int i = l; i < r; ++i) {
              auto it = prev(vert[i].lower_bound(make_pair(x, N + 1)));
              up[i] = it->first;
            }
            iota(order.begin(), order.end(), l);
            sort(order.begin(), order.end(),
                 [&](int i, int j) { return up[i] > up[j]; });
            set<int> s(order.begin(), order.end());
            for (int row = x - 1, j = 0; row >= 0; --row) {
              while (j < order.size() && up[order[j]] > row) {
                s.erase(order[j]);
                j++;
              }
              auto it = horz[row].lower_bound(make_pair(y, M + 1));
              if (it != horz[row].begin()) {
                it = prev(it);
                if (it->first <= y && it->second > y) {
                  int ll = max(l, it->first);
                  int rr = min(r, it->second);
                  auto lit = s.lower_bound(ll);
                  auto rit = s.lower_bound(rr);
                  if (lit != rit) {
                    int lll = *lit;
                    int rrr = *prev(rit);
                    if (lll <= y && rrr >= y) {
                      ans = max(ans, (rrr - lll + 1) * (x - row + 1));
                    }
                  }
                }
              }
            }
          }
          {
            // cout << "here" << endl;
            vector<int> down(M), order(r - l);
            for (int i = l; i < r; ++i) {
              auto it = prev(vert[i].lower_bound(make_pair(x, N + 1)));
              down[i] = it->second;
            }
            iota(order.begin(), order.end(), l);
            sort(order.begin(), order.end(),
                 [&](int i, int j) { return down[i] < down[j]; });
            set<int> s(order.begin(), order.end());
            for (int row = x + 1, j = 0; row < N; ++row) {
              while (j < order.size() && down[order[j]] <= row) {
                s.erase(order[j]);
                j++;
              }
              auto it = horz[row].lower_bound(make_pair(y, M + 1));
              if (it != horz[row].begin()) {
                it = prev(it);
                if (it->first <= y && it->second > y) {
                  int ll = max(l, it->first);
                  int rr = min(r, it->second);
                  auto lit = s.lower_bound(ll);
                  auto rit = s.lower_bound(rr);
                  if (lit != rit) {
                    int lll = *lit;
                    int rrr = *prev(rit);
                    if (lll <= y && rrr >= y) {
                      ans = max(ans, (rrr - lll + 1) * (row - x + 1));
                    }
                  }
                }
              }
            }
          }
        }
        {
          auto iter = vert[y].lower_bound(make_pair(x, N + 1));
          assert(iter != vert[y].begin());
          iter = prev(iter);
          ans = max(ans, iter->second - iter->first);
          int l = iter->first, r = iter->second;
          {
            vector<int> left(N), order(r - l);
            // cout << "here" << endl;
            for (int i = l; i < r; ++i) {
              auto it = prev(horz[i].lower_bound(make_pair(y, M + 1)));
              left[i] = it->first;
            }
            // cout << "done" << endl;
            iota(order.begin(), order.end(), l);
            sort(order.begin(), order.end(),
                 [&](int i, int j) { return left[i] > left[j]; });
            set<int> s(order.begin(), order.end());
            for (int col = y - 1, j = 0; col >= 0; --col) {
              // cout << "col = " << col << endl;
              while (j < order.size() && left[order[j]] > col) {
                s.erase(order[j]);
                j++;
              }
              auto it = vert[col].lower_bound(make_pair(x, N + 1));
              if (it != vert[col].begin()) {
                it = prev(it);
                if (it->first <= x && it->second > x) {
                  int ll = max(l, it->first);
                  int rr = min(r, it->second);
                  auto lit = s.lower_bound(ll);
                  auto rit = s.lower_bound(rr);
                  if (lit != rit) {
                    int lll = *lit;
                    int rrr = *prev(rit);
                    if (lll <= x && rrr >= x) {
                      ans = max(ans, (rrr - lll + 1) * (y - col + 1));
                    }
                  }
                }
              }
            }
          }
          {
            vector<int> right(N), order(r - l);
            for (int i = l; i < r; ++i) {
              auto it = prev(horz[i].lower_bound(make_pair(y, M + 1)));
              right[i] = it->second;
            }
            iota(order.begin(), order.end(), l);
            sort(order.begin(), order.end(),
                 [&](int i, int j) { return right[i] < right[j]; });
            set<int> s(order.begin(), order.end());
            for (int col = y + 1, j = 0; col < M; ++col) {
              while (j < order.size() && right[order[j]] <= col) {
                s.erase(order[j]);
                j++;
              }
              auto it = vert[col].lower_bound(make_pair(x, N + 1));
              if (it != vert[col].begin()) {
                it = prev(it);
                if (it->first <= x && it->second > x) {
                  int ll = max(l, it->first);
                  int rr = min(r, it->second);
                  auto lit = s.lower_bound(ll);
                  auto rit = s.lower_bound(rr);
                  if (lit != rit) {
                    int lll = *lit;
                    int rrr = *prev(rit);
                    if (lll <= x && rrr >= x) {
                      ans = max(ans, (rrr - lll + 1) * (col - y + 1));
                    }
                  }
                }
              }
            }
          }
        }
        cout << ans << "\n";
      }
    }
  }
}

