#include <bits/stdc++.h>
using namespace std;
#define ZZ 30

int a[200005], b[200005];

int an[40][200005], o[40][200005];
int typ[40][200005];
// 0 => no extra
// 1 => need extra place
// 2 => alive if init = 1

int last[40], happy[40], happy_if[40], extend_if[40];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) cin >> b[i];

  for (int z = ZZ; z >= 0; --z) {
    last[z] = 0;
    for (int i = n; i >= 1; --i) {
      if (a[i] & (1 << z)) {
        last[z] = i;
        break;
      }
      // o[z][i] = o[z][i + 1];
      // an[z][i] = an[z][i + 1];
      // if (b[i] == 1) ++o[z][i];
      // else ++an[z][i];
    }
    for (int i = last[z] + 1; i <= n + 1; ++i) {
      o[z][i] = o[z][i - 1];
      an[z][i] = an[z][i - 1];
      if (b[i] == 1)
        ++o[z][i];
      else
        ++an[z][i];
      // cout << "z i o an " << z << ' ' << i << ' ' << o[z][i] << ' ' << an[z][i] << endl;
    }

    int can_happy = 1;
    extend_if[z] = n + 1;
    for (int i = last[z]; i >= 1; --i) {
      int has = !!(a[i] & (1 << z));
      if (has && b[i]) {
        happy[z] |= can_happy;
      } else if (has && !b[i]) {
        if (!happy_if[z]) happy_if[z] = i;
      } else if ((!has) && b[i]) {
      } else {
        extend_if[z] = i;
        can_happy = 0;
      }
    }
  }

  while (q--) {
    int x, k;
    cin >> x >> k;
    int ans = 0;
    int or_to = n + 1;
    for (int z = ZZ; z >= 0; --z) {
      // cerr << "z = " << z << " or_to = " << or_to << " k = " << k << endl;
      int need = 0;
      int to = 0;
      int hasz = !!(x & (1 << z));

      if (or_to <= last[z] + 1) {
        // cerr << "here happy " << happy[z] << endl;
        if (happy[z] == 1) {
          need = 0;
          to = or_to;
        } else if (or_to <= happy_if[z]) {
          need = 0;
          to = or_to;
        } else if (or_to <= extend_if[z] && hasz) {
          need = 0;
          to = or_to;
        } else if (or_to <= last[z]) {
          need = 0;
          to = or_to;
        } else if (last[z] >= 1) {
          need = 1;
          to = or_to - 1;
        } else {
          need = INT_MAX;
        }
      } else {
        need = an[z][or_to - 1];
        to = last[z] + 1;
        // cerr << "here need to " << need << ' ' << to << endl;
        // cerr << "hasz extend_if happy " << hasz << ' ' << extend_if[z] << ' ' << happy[z] << endl;
        if (hasz && extend_if[z] == n + 1) {
          ;
        } else if (happy[z]) {
          ;
        } else {
          // cerr << "here2" << endl;
          if (last[z] == 0) {
            if (hasz) ;
            else {
              need = INT_MAX; 
            }
          } else {
            // cerr << "need to " << need << ' ' << to << endl;
            ++need;
            --to;
          }
        }
      }

      // cerr << "need = " << need << endl;
      if (need <= k) {
        k -= need;
        ans |= (1 << z);
        or_to = to;
      }
    }

    cout << ans << '\n';
  }
}

