#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct node {
  node *ch[2];
  int cnt;

  node() : cnt(0) {
    ch[0] = ch[1] = 0;
  }
} *root;

int lim[35];

int ins(node *&root, int dep, uint32_t val) {
  if (!root) {
    root = new node();
  }

  if (root->cnt >= lim[dep]) return false;

  if (dep == 0) {
    ++root->cnt;
    return true;
  }

  int r = ins(root->ch[!!(val & (1u << (dep - 1)))], dep - 1, val);
  if (r) {
    ++root->cnt;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  for (int i = 32; i >= 0; --i) {
    cin >> lim[i];
  }

  int n; cin >> n;

  while (n--) {
    string s; cin >> s;
    uint32_t a, b, c, d;
    sscanf(s.data(), "%u.%u.%u.%u", &a, &b, &c, &d);
    uint32_t val = (a << 24) | (b << 16) | (c << 8) | d;

    int res = ins(root, 32, val);
    cout << (res ? "a" : "b") << '\n';
  }


}

