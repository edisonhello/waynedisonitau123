#include <bits/stdc++.h>
using namespace std;


int main() {
  ios_base::sync_with_stdio(0); 
  int n, k;
  cin >> n >> k;

  vector<int> g(n);
  vector<vector<int>> ig(n);
  for (int i = 0; i < n; ++i) {
    cin >> g[i];
    --g[i];
    ig[g[i]].push_back(i);
  }

  auto is_end = [&](int x) { return ig[x].size() == 0; };

  vector<int> visit_by(n, -1);
  stack<int> dfs_stk;

  vector<vector<int>> loops;

  auto init_dfs = [&](auto f, int now, int pa, int by) -> void {
    // cerr << "init_dfs " << now << ' ' << pa << ' ' << by << endl;
    if (visit_by[now] == by) {
      vector<int> loop;
      while (dfs_stk.top() != now) {
        loop.push_back(dfs_stk.top());
        dfs_stk.pop();
      }
      loop.push_back(now);
      loops.push_back(loop);
      return;
    } 
    else if (visit_by[now] != -1) return;
    else {
      visit_by[now] = by;
      dfs_stk.push(now);
      f(f, g[now], now, by);
    }
  };

  for (int i = 0; i < n; ++i) if (is_end(i)) {
    while (dfs_stk.size()) dfs_stk.pop();
    init_dfs(init_dfs, i, -1, i);
  }

  for (int i = 0; i < n; ++i) {
    if (visit_by[i] == -1) {
      while (dfs_stk.size()) dfs_stk.pop();
      init_dfs(init_dfs, i, -1, i);
    }
  }


  vector<int> loop_id(n, -1);
  vector<int> ilpos(n, -1);
  for (int i = 0; i < (int)loops.size(); ++i) {
    for (int j = 0; j < (int)loops[i].size(); ++j) {
    // for (int j : loops[i]) {
      loop_id[loops[i][j]] = i;
      ilpos[loops[i][j]] = j;
    }
  }

  vector<int> ans(n);

  for (auto &v : loops) {
    for (int i : v) {
      // cerr << "v size " << v.size() << " k " << k << endl;
      if ((int)v.size() > k) ans[i] += k + 1;
      else ans[i] += v.size();
      // cerr << i << " ans init " << ans[i] << endl;
    }
  }

  vector<int> into_loop_len(n, -1), into_who(n, -1);
  for (auto &v : loops) {
    for (int i : v) {
      for (int j : ig[i]) {
        // cerr << "ig connect i j " << i << ' ' << j << " loop id " << loop_id[j] << endl;
        if (loop_id[j] == -1) {
          auto dfs = [&](auto dfs, int now, int from, int dep) -> void {
            into_loop_len[now] = dep;
            into_who[now] = from;
            for (int i : ig[now]) {
              dfs(dfs, i, from, dep + 1);
            }
          };
          dfs(dfs, j, i, 1);
        }
      }
    }
  }

  vector<vector<int>> loop_ans_pre(loops.size());
  for (int i = 0; i < (int)loops.size(); ++i) {
    loop_ans_pre[i].resize(loops[i].size(), 0);
  }

  for (int i = 0; i < n; ++i) if (loop_id[i] == -1) {
    int into = into_who[i];
    int len = into_loop_len[i];
    if (len > k) continue;
    int trav_loop = k - len;
    int lid = loop_id[into];
    int pos = ilpos[into];

    if (trav_loop + 1 >= (int)loops[lid].size()) {
      loop_ans_pre[lid][0]++;
    } else {
      if (trav_loop >= pos + 1) {
        ++loop_ans_pre[lid][0];
        if (pos != (int)loops[lid].size() - 1) --loop_ans_pre[lid][pos + 1];

        trav_loop -= (pos);
        ++loop_ans_pre[lid][loops[lid].size() - trav_loop];
      } else {
        // cerr << "lid " << lid << endl;
        // cerr << "pos trav_loop " << pos << ' ' << trav_loop << endl;
        // cerr << "pos + 1 - trav_loop = " << pos + 1 - trav_loop << endl;
        ++loop_ans_pre[lid][pos - trav_loop];
        if (pos != (int)loops[lid].size() - 1) --loop_ans_pre[lid][pos + 1];
      }
    }
  }

  for (int i = 0; i < (int)loops.size(); ++i) {
    for (int j = 1; j < (int)loops[i].size(); ++j) {
      loop_ans_pre[i][j] += loop_ans_pre[i][j - 1];
    }
    for (int j = 0; j < (int)loops[i].size(); ++j) {
      // cerr << loops[i][j] << " add loop answer " << loop_ans_pre[i][j] << endl;
      ans[loops[i][j]] += loop_ans_pre[i][j];
    }
  }

  vector<int> tree_ans(n, 0);
  vector<vector<int>> dp(n);
  for (int i = 0; i < n; ++i) if (loop_id[i] != -1) {
    for (int j : ig[i]) if (loop_id[j] == -1) {
      auto dfs = [&](auto dfs, int now) -> void {
        tree_ans[now] = 1;

        for (int i : ig[now]) {
          dfs(dfs, i);

          if (dp[i].size() > dp[now].size()) dp[now].swap(dp[i]);
          for (int j = 0; j < (int)dp[i].size(); ++j) {
            dp[now][dp[now].size() - dp[i].size() + j] += dp[i][j];
          }

          tree_ans[now] += tree_ans[i];
        }
        dp[now].push_back(1);
        if ((int)dp[now].size() - (k + 2) >= 0)
          tree_ans[now] -= dp[now][dp[now].size() - (k + 2)];
      };

      dfs(dfs, j);
    }
  }

  for (int i = 0; i < n; ++i) {
    ans[i] += tree_ans[i];
    // cerr << i << " add tree answer " << tree_ans[i] << endl;
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << '\n';
  }

}

