#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int GetGenerator(int p) {
  vector<int> vis(p, 0);
  for (int i = 1; ; ++i) {
    fill(vis.begin(), vis.end(), 0);
    int vc = 0;
    int now = 1;
    while (true) {
      now = (now * i) % p;
      if (vis[now]) break;
      vis[now] = 1;
      ++vc;
    }
    if (vc == p - 1) {
      return i;
    }
  }
  assert(0);
}

bitset<200005> mask;

bitset<200005> rot(bitset<200005> &bs, int i, int n) {
  return ((bs << i) | (bs >> (n - i))) & mask;
  // return ((bs << i) | (bs >> (n - i)));
}

int up[200005];
int gpw[200005];

int can[200005];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  // P = 2? 
  int P, N;
  cin >> P >> N;

  for (int i = 0; i < P - 1; ++i) {
    mask[i] = 1;
  }

  int g = GetGenerator(P);
  // cerr << "g = " << g << endl;

  up[1] = 0;
  gpw[0] = 1;
  for (int now = g % P, u = 1; now != 1; now = (1ll * now * g) % P, ++u) {
    up[now] = u;
    gpw[u] = now;
    // cerr << "g^" << u << " = " << now << endl;
  }
  gpw[P - 1] = 1;

  int hasst = 0;
  vector<int> st(P, 0), mu(P, 0);
  // st.push_back(1);

  int mu0 = 0;
  for (int i = 0; i < N; ++i) {
    int t, a;
    cin >> t >> a;
    if (t == 0) {
      st[a] = 1;
      hasst = 1;
    }
    else {
      if (a == 0) mu0 = 1;
      else mu[up[a]]++;
    }
  }

  for (int i = 0; i < P; ++i) {
    auto dfs = [&](auto dfs, int now) -> void {
      if (mu[now] <= 2) return;
      int to = now * 2 % (P - 1);
      int add = (mu[now] - 1) / 2;
      mu[to] += add;
      mu[now] -= add * 2;
      dfs(dfs, to);
    };
    dfs(dfs, i);
  }


  bitset<200005> posi;
  bitset<200005> ok;

  if (hasst) {
    posi[0] = 1;

    for (int i = 0; i < P; ++i) {
      while (mu[i] > 0) {
        --mu[i];
        posi |= rot(posi, i, P - 1);
      }
      if ((i & 1023) == 0) {
        if (posi.count() == P - 1) break;
      }
    }

    // for (int i = 0; i <= P - 1; ++i) {
    //   if (posi[i]) {
    //     cerr << "posible g^" << i << endl;
    //   }
    // }

    if (mu0) can[0] = 1;

    for (int i = 0; i < P; ++i) {
      if (st[i]) {
        if (i == 0) {
          can[0] = 1;
        } else {
          int u = up[i];
          ok |= rot(posi, u, P - 1);
        }
      }
      if ((i & 1023) == 0) {
        if (ok.count() == P - 1) break;
      }
    }
  } else {
    if (!mu0) {
      int sum = 0;
      for (int i = 0; i < P; ++i) {
        while (mu[i] > 0) {
          sum += i;
          sum %= (P - 1);
          --mu[i];
        }
      }
      ok[sum] = 1;
    } else {
      can[0] = 1;
    }
  }


  for (int i = 0; i < P - 1; ++i) {
    if (ok[i]) {
      // cerr << "ok " << i << " val " << gpw[i] << endl;
      can[gpw[i]] = 1;
    }
  }

  int cant = 0;
  for (int i = 0; i < P; ++i) {
    if (!can[i]) {
      // cerr << "cant to " << i << endl;
      ++cant;
    }
  }
  cout << cant << endl;

}

