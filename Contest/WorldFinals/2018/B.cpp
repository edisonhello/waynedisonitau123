#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  getline(cin, s);
  bool first = true;
  bool has_comma = false;
  vector<string> words;
  vector<bool> fs, ls;
  unordered_map<string, vector<int>> ind;
  vector<int> period;
  vector<int> comma;
  for (int i = 0, j = 0; i < s.size(); i = j) {
    if (!isalpha(s[i])) {
      j = i + 1;
      continue;
    }
    while (j < s.size() && isalpha(s[j])) j++;
    words.push_back(s.substr(i, j - i));
    ind[s.substr(i, j - i)].push_back(words.size() - 1);
    fs.push_back(first);
    if (j < s.size() && s[j] == ',') {
      comma.push_back(words.size() - 1);
      has_comma = true;
    } else {
      has_comma = false;
    }
    if (j < s.size() && s[j] == '.') {
      period.push_back(words.size() - 1);
      ls.push_back(true);  
      first = true;
    } else {
      ls.push_back(false);
      first = false;
    }
  }
  vector<int> que = comma;
  vector<bool> has_comma_(words.size());
  {
    for (int u : comma) has_comma_[u] = true;
    unordered_set<string> B, A;
    while (!que.empty()) {
      int x = que.back();
      que.pop_back();
      if (!A.count(words[x])) {
        A.insert(words[x]);
        for (int i : ind[words[x]]) {
          if (!ls[i]) {
            if (!has_comma_[i]) {
              has_comma_[i] = true;
              que.push_back(i);
            }  
          }
        }
      }
      if (x + 1 < words.size() && !B.count(words[x + 1])) {
        B.insert(words[x + 1]);
        for (int i : ind[words[x + 1]]) {
          if (!fs[i]) {
            if (i > 0 && !has_comma_[i - 1]) {
              has_comma_[i - 1] = true;
              que.push_back(i - 1);
            }  
          }
        }
      }
    }
  }
  reverse(period.begin(), period.end());
  bool has = false;
  for (int i = 0; i < words.size(); ++i) {
    if (i > 0) cout << " ";
    cout << words[i];
    if (has_comma_[i]) {
      cout << ",";
    }
    if (!period.empty() && period.back() == i) {
      cout << ".";
      period.pop_back();
    }
  }
  cout << "\n";
  return 0;
}

