#include <bits/stdc++.h>
using namespace std;

tuple<int, int, int> get_error(vector<bitset<305>> &mp) {
  vector<int> er, ec;
  for (int i = 0; i < 305; ++i) {
    vector<int> cnt(3, 0);
    for (int j = 0; j < 305; ++j) {
      if (mp[i][j]) ++cnt[j % 3];
    }

    if (cnt[0] % 2 != cnt[1] % 2 || cnt[1] % 2 != cnt[2] % 2) {
      er.push_back(i);
    }
  }

  for (int j = 0; j < 305; ++j) {
    vector<int> cnt(3, 0);
    for (int i = 0; i < 305; ++i) {
      if (mp[i][j]) ++cnt[i % 3];
    }

    if (cnt[0] % 2 != cnt[1] % 2 || cnt[1] % 2 != cnt[2] % 2) {
      ec.push_back(j);
    }
  }

  if (er.size() > 1u || ec.size() > 1u) return make_tuple(-1, -1, -1);
  if (er.size() == 1u && ec.size() == 1u) return make_tuple(1, er[0], ec[0]);
  if (er.empty() && ec.empty()) return make_tuple(0, -1, -1);
  return make_tuple(-1, -1, -1);
}

bool go_back(vector<bitset<305>> &mp) {
  auto [error, ei, ej] = get_error(mp);
  auto omp = mp;
  
  if (error == -1) return false;

  if (error == 1) {
    mp[ei].flip(ej);

    auto [_e, _i, _j] = get_error(mp);
    if (_e != 0) {
      mp = omp;
      return false;
    }
  }

  vector<bitset<305>> tmp(305);

  for (int i = 0; i < 303; ++i) {
    for (int j = 0; j < 303; ++j) {
      if (mp[i][j]) {
        tmp[i + 1].flip(j + 1);
        mp[i].flip(j);
        mp[i].flip(j + 1);
        mp[i].flip(j + 2);
        mp[i + 1].flip(j);
        mp[i + 1].flip(j + 1);
        mp[i + 1].flip(j + 2);
        mp[i + 2].flip(j);
        mp[i + 2].flip(j + 1);
        mp[i + 2].flip(j + 2);
      }
    }
  }

  if ((mp[302] | mp[303] | mp[304]).count()) {
    mp = omp;
    return false;
  }

  mp = tmp;
  return true;
}

pair<int, int> minimal(vector<bitset<305>> &mp, int output = 0) {
  int si = 0;
  
  while (si < 305) {
    int keep = 1;
    for (int j = 0; j < 305; ++j) if (mp[si][j]) keep = 0;
    if (!keep) break;
    ++si;
  }

  int ei = 304;
  while (ei >= 0) {
    int keep = 1;
    for (int j = 0; j < 305; ++j) if (mp[ei][j]) keep = 0;
    if (!keep) break;
    --ei;
  }

  int sj = 0;
  
  while (sj < 305) {
    int keep = 1;
    for (int i = 0; i < 305; ++i) if (mp[i][sj]) keep = 0;
    if (!keep) break;
    ++sj;
  }

  int ej = 304;
  while (ej >= 0) {
    int keep = 1;
    for (int i = 0; i < 305; ++i) if (mp[i][ej]) keep = 0;
    if (!keep) break;
    --ej;
  }

  if (ej < sj) {
    cout << "#" << endl;
    exit(0);
  }

  if (output) {
    for (int i = si; i <= ei; ++i) {
      for (int j = sj; j <= ej; ++j) {
        cout << (mp[i][j] ? "#" : ".");
      }
      cout << endl;
    }
  }

  return make_pair(ei - si + 1, ej - sj + 1);
}

int main() {
  int n, m; cin >> m >> n;

  vector<string> smp(n);
  for (int i = 0; i < n; ++i) cin >> smp[i];

  vector<bitset<305>> mp(305);
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < m; ++j)
      mp[i][j] = smp[i][j] == '#';

  int min_size = m * n;
  auto min_ans = mp;

  for (int t = 0; t <= 300; ++t) {
    bool res = go_back(mp);

    if (!res) break;

    auto [_x, _y] = minimal(mp);
    if (_x * _y < min_size) {
      min_size = _x * _y;
      min_ans = mp;
      if (min_size == 1) {
        cout << "#" << endl;
        exit(0);
      }
    }
  }

  minimal(min_ans, 1);
}

