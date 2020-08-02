#include <bits/stdc++.h>
using namespace std;

int p[500005];
int l[500005], r[500005];
int plug[500005];
int far[500005];
int dp[500005];

void dfs1(int now) {
  if (l[now]) dfs1(l[now]);
  if (r[now]) dfs1(r[now]);
  if (l[now] || r[now]) {
    far[now] = max(far[l[now]], far[r[now]]) + 1;

    if (far[now] == 1 && l[now] && r[now]) dp[now] = 1;
    else if (far[now] > 1) {
      if (far[l[now]] > far[r[now]]) dp[now] = dp[l[now]];
      else if (far[l[now]] < far[r[now]]) dp[now] = dp[r[now]];
      else dp[now] = 1;
    } else dp[now] = 0;
  }
}

void dfs2(int now, int rest) {
  // cerr << "dfs2 " << now << " rest " << rest << endl;
  if (!l[now] && !r[now]) {
    plug[now] = 1;
    cerr << "plug " << now << endl;
    return;
  }

  if (!l[now]) dfs2(r[now], rest);
  else if (!r[now]) dfs2(l[now], rest);
  else {
    if (rest) {
      if (far[l[now]] == far[r[now]]) dfs2(r[now], 0);
      else if (far[l[now]] < far[r[now]]) {
        if (dp[r[now]]) dfs2(r[now], 1);
        else dfs2(l[now], 1);
      } else {
        if (dp[r[now]]) dfs2(r[now], 1);
        else dfs2(l[now], 1);
      }
    } else {
      if (far[l[now]] == far[r[now]]) dfs2(r[now], 0);
      else if (far[l[now]] < far[r[now]]) {
        dfs2(r[now], 0);
      } else {
        if (dp[r[now]]) dfs2(r[now], 1);
        else dfs2(l[now], 0);
      }
    }
  }
  if (plug[l[now]]) l[now] = 0;
  if (plug[r[now]]) r[now] = 0;
  if (l[now] || r[now]) {
    far[now] = max(far[l[now]], far[r[now]]) + 1;
  } else {
    far[now] = 0;
  }

  if (far[now] == 1 && l[now] && r[now]) dp[now] = 1;
  else if (far[now] > 1) {
    if (far[l[now]] > far[r[now]]) dp[now] = dp[l[now]];
    else if (far[l[now]] < far[r[now]]) dp[now] = dp[r[now]];
    else dp[now] = 1;
  } else dp[now] = 0;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, k; cin >> n >> k;
  int root = 0;

  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
    if (p[i] == -1) root = i;
    else {
      if (p[i] < i) r[p[i]] = i;
      else l[p[i]] = i;
    }
  }

  dfs1(root);

  for (int i = 0; i < n - k; ++i) {
    cerr << "plug" << endl;
    for (int i = 1; i <= n; ++i) {
      cerr << "i = " << i << ", dp " << dp[i] << ' ' << "far = " << far[i] << endl;
    }
    dfs2(root, 0);
  }

  for (int i = 1; i <= n; ++i) cout << (!plug[i]);
  cout << endl;
}
