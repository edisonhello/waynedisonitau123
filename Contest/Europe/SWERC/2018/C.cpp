#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

vector<int> okset1[26][4];
vector<int> okset2[26][26][4];
vector<int> okset3[26][26][26][4];

char grid[6][6];
int answer;
int n, a, m, b;
vector<string> wordn, wordm;

vector<int> Merge(const vector<int> &va, const vector<int> &vb) {
  int i = 0, j = 0;
  vector<int> r;
  while (i < va.size() && j < vb.size()) {
    if (va[i] == vb[j]) {
      r.push_back(va[i]);
      ++i, ++j;
    } else if (va[i] < vb[j]) ++i;
    else ++j;
  }
  return r;
}

void Dfs(int now) {
  // cerr << "now " << now << " grid: " << endl;
  // for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cerr << grid[i][j] << " \n"[j == m - 1];
  if (now == m) {
    ++answer;
    return;
  }

  if (now == 0) {
    for (int i = 0; i < a; ++i) {
      for (int j = 0; j < n; ++j) grid[j][0] = wordn[i][j];
      Dfs(now + 1);
    }
  } else if (now == 1) {
    vector<int> ok = okset1[grid[0][0] - 'a'][0];
    for (int j = 1; j < n; ++j) ok = Merge(ok, okset1[grid[j][0] - 'a'][j]);

    for (int i : ok) {
      for (int j = 0; j < n; ++j) grid[j][1] = wordn[i][j];
      Dfs(now + 1);
    }
  } else if (now == 2) {
    vector<int> ok = okset2[grid[0][0] - 'a'][grid[0][1] - 'a'][0];
    for (int j = 1; j < n; ++j) ok = Merge(ok, okset2[grid[j][0] - 'a'][grid[j][1] - 'a'][j]);

    for (int i : ok) {
      for (int j = 0; j < n; ++j) grid[j][2] = wordn[i][j];
      Dfs(now + 1);
    }
  } else if (now == 3) {
    vector<int> ok = okset3[grid[0][0] - 'a'][grid[0][1] - 'a'][grid[0][2] - 'a'][0];
    for (int j = 1; j < n; ++j) ok = Merge(ok, okset3[grid[j][0] - 'a'][grid[j][1] - 'a'][grid[j][2] - 'a'][j]);

    for (int i : ok) {
      for (int j = 0; j < n; ++j) grid[j][3] = wordn[i][j];
      Dfs(now + 1);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> a >> m >> b;
  wordn.resize(a), wordm.resize(b);
  for (int i = 0; i < a; ++i) cin >> wordn[i];
  for (int i = 0; i < b; ++i) cin >> wordm[i];

  if (b < a) {
    swap(a, b);
    swap(n, m);
    swap(wordn, wordm);
  }

  for (int i = 0; i < n; ++i) for (int j = 1; j < m; ++j) {
    // cerr << "Counting posision i j " << i << ' ' << j << endl;
    if (j == 1) {
      set<char> ok[26];
      for (int k = 0; k < b; ++k) 
        ok[wordm[k][0] - 'a'].insert(wordm[k][1]);

      // cerr << "j = 1, oks " << endl;
      // for (char z = 'a'; z <= 'z'; ++z) if (ok[z - 'a'].size()) {
      //   cerr << "ok[" << z << "] = ";
      //   for (char y : ok[z - 'a']) cerr << y << ' ';
      //   cerr << endl;
      // }

      for (int k = 0; k < a; ++k) {
        for (int s1 = 'a'; s1 <= 'z'; ++s1) {
          if (ok[s1 - 'a'].count(wordn[k][i]))
            okset1[s1 - 'a'][i].push_back(k);
        }
      }
    } else if (j == 2) {
      set<char> ok[26][26];
      for (int k = 0; k < b; ++k) 
        ok[wordm[k][0] - 'a'][wordm[k][1] - 'a'].insert(wordm[k][2]);

      for (int k = 0; k < a; ++k) {
        for (int s1 = 'a'; s1 <= 'z'; ++s1) for (int s2 = 'a'; s2 <= 'z'; ++s2) {
          if (ok[s1 - 'a'][s2 - 'a'].count(wordn[k][i]))
            okset2[s1 - 'a'][s2 - 'a'][i].push_back(k);
        }
      }
    } else if (j == 3) {
      set<char> ok[26][26][26];
      for (int k = 0; k < b; ++k) 
        ok[wordm[k][0] - 'a'][wordm[k][1] - 'a'][wordm[k][2] - 'a'].insert(wordm[k][3]);

      for (int k = 0; k < a; ++k) {
        for (int s1 = 'a'; s1 <= 'z'; ++s1) for (int s2 = 'a'; s2 <= 'z'; ++s2) for (int s3 = 'a'; s3 <= 'z'; ++s3) {
          if (ok[s1 - 'a'][s2 - 'a'][s3 - 'a'].count(wordn[k][i]))
            okset3[s1 - 'a'][s2 - 'a'][s3 - 'a'][i].push_back(k);
        }
      }
    }
  }

  // for (char s1 = 'a'; s1 <= 'z'; ++s1) for (int j = 0; j < 4; ++j) {
  //   if (okset1[s1 - 'a'][j].empty()) continue;
  //   cerr << "okset1[" << s1 << "][" << j << "] = ";
  //   for (int i : okset1[s1 - 'a'][j]) cerr << i << ' ';
  //   cerr << endl;
  // }
  // for (char s1 = 'a'; s1 <= 'z'; ++s1) for (char s2 = 'a'; s2 <= 'z'; ++s2) for (int j = 0; j < 4; ++j) {
  //   if (okset2[s1 - 'a'][s2 - 'a'][j].empty()) continue;
  //   cerr << "okset2[" << s1 << "][" << s2 << "][" << j << "] = ";
  //   for (int i : okset2[s1 - 'a'][s2 - 'a'][j]) cerr << i << ' ';
  //   cerr << endl;
  // }
  // for (char s1 = 'a'; s1 <= 'z'; ++s1) for (char s2 = 'a'; s2 <= 'z'; ++s2) for (char s3 = 'a'; s3 <= 'z'; ++s3) for (int j = 0; j < 4; ++j) {
  //   if (okset3[s1 - 'a'][s2 - 'a'][s3 - 'a'][j].empty()) continue;
  //   cerr << "okset3[" << s1 << "][" << s2 << "][" << s3 << "][" << j << "] = ";
  //   for (int i : okset3[s1 - 'a'][s2 - 'a'][s3 - 'a'][j]) cerr << i << ' ';
  //   cerr << endl;
  // }

  Dfs(0);

  cout << answer << endl;
}
