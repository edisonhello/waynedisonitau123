#include <bits/stdc++.h>
using namespace std;

vector<int> getinit() {
  vector<int> v(10005);
  iota(v.begin(), v.end(), 0);
  return v;
}

int cix = 12000;
pair<int, int> pair_rec[100005];
map<pair<int, int>, int> appear;

pair<int, int> getpair(int x) {
  return pair_rec[x];
}

int makepair(int x, int y) {
  auto p = make_pair(x, y);
  auto it = appear.find(p);
  if (it == appear.end()) {
    pair_rec[cix] = p;
    appear[p] = cix;
    return cix++;
  } else return it->second;
}

vector<int> ope(vector<int> v, string s) {
  const static vector<int> NO{-1};
  for (char c : s) {
    if (c == 'C') {
      v.push_back(v.back());
    } else if (c == 'D') {
      v.pop_back();
    } else if (c == 'L') {
      auto p = getpair(v.back());
      if (p.first == -1) return NO;
      v.pop_back();
      v.push_back(p.first);
    } else if (c == 'P') {
      int x = v.back(); v.pop_back();
      int y = v.back(); v.pop_back();
      auto z = makepair(x, y);
      v.push_back(z);
    } else if (c == 'R') {
      auto p = getpair(v.back());
      if (p.first == -1) return NO;
      v.pop_back();
      v.push_back(p.second);
    } else if (c == 'S') {
      int x = v.back(); v.pop_back();
      int y = v.back(); v.pop_back();
      v.push_back(x);
      v.push_back(y);
    } else if (c == 'U') {
      auto p = getpair(v.back());
      if (p.first == -1) return NO;
      v.pop_back();
      v.push_back(p.second);
      v.push_back(p.first);
    }
  }
  return v;
}


int main() {
  fill(pair_rec, pair_rec + 100000, make_pair(-1, -1));

  string s, t; cin >> s >> t;
  vector<int> v = getinit();
  v = ope(v, s);
  vector<int> u = getinit();
  u = ope(u, t);

  cout << (u == v ? "True" : "False") << endl;
}
