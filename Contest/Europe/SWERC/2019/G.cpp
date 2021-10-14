#include <bits/stdc++.h>
using namespace std;

int main() {
  int S, L, N;
  cin >> S >> L >> N;
  vector<string> p(S);
  for (int i = 0; i < S; ++i) cin >> p[i];
  sort(p.begin(), p.end());
  map<string, int> ID;
  for (int i = 0; i < S; ++i) ID[p[i]] = i;

  vector<vector<int>> g(S);
  vector<vector<bool>> adj(S, vector<bool>(S));
  for (int i = 0; i < S; ++i) adj[i][i] = true;
  for (int i = 0; i < L; ++i) {
    string a, b;
    cin >> a >> b;
    int x = ID[a], y = ID[b];
    adj[x][y] = true;
    adj[y][x] = true;
  }

  vector<int> vec(N);
  for (int i = 0; i < N; ++i) {
    string s;
    cin >> s;
    vec[i] = ID[s];
  }
  vector<bool> used(N);
  priority_queue<int, vector<int>, greater<int>> pq;
  vector<vector<int>> pos(S);
  for (int i = 0; i < N; ++i) pos[vec[i]].push_back(i);
  for (int i = 0; i < S; ++i) reverse(pos[i].begin(), pos[i].end());

  vector<int> block(S);
  for (int i = 0; i < S; ++i) {
    if (pos[i].empty()) continue;
    for (int j = 0; j < S; ++j) {
      if (adj[i][j]) continue;
      if (pos[j].empty()) continue;
      if (pos[j].back() < pos[i].back()) block[i]++;
    }
    if (block[i] == 0) pq.push(i);
  }

  for (int i = 0; i < N; ++i) {
    int x = pq.top();
    pq.pop();
    cout << p[x] << " ";
    int t = pos[x].back();
    pos[x].pop_back();
    block[x] = 0;
    for (int j = 0; j < S; ++j) {
      if (adj[x][j]) continue; 
      if (pos[j].empty()) continue;
      if (pos[x].empty() || pos[x].back() > pos[j].back()) {
        --block[j];
        if (block[j] == 0) pq.push(j);
      }
    }
    if (pos[x].empty()) continue;
    for (int j = 0; j < S; ++j) {
      if (adj[x][j]) continue;
      if (pos[j].empty()) continue;
      if (pos[j].back() < pos[x].back()) block[x]++;
    }
    if (block[x] == 0) pq.push(x);
  }
  cout << "\n";
  return 0;
}
