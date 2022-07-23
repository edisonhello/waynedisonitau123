#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  mt19937 rng(0x7122);
  uniform_int_distribution<uint64_t> dis;

  int N;
  cin >> N;
  vector<int> clr(2 * N);
  vector<uint64_t> rnd(N);

  for (int i = 0; i < N; ++i) {
    int x, y;
    cin >> x >> y;
    clr[x - 1] = i;
    clr[y - 1] = i;
  }
  for (int i = 0; i < N; ++i) {
    rnd[i] = dis(rng);
  }
  vector<uint64_t> sum(2 * N + 1);
  for (int i = 0; i < 2 * N; ++i) {
    sum[i + 1] = sum[i] ^ rnd[clr[i]];
  }
  set<uint64_t> vis;
  vector<int> stk = {-1};
  vis.insert(0);
  vector<vector<int>> vec;
  set<pair<int, int>> edges;

  auto AddEdge = [&](int a, int b) {
    if (a > b) {
      swap(a, b);
    }
    if (a == b || (a - b + 2 * N) % (2 * N) == 1 ||
        (b - a + 2 * N) % (2 * N) == 1) {
      return;
    }
    edges.emplace(a, b);
  };

  for (int i = 0; i < 2 * N; ++i) {
    if (vis.count(sum[i + 1])) {
      vector<int> group = {i};
      while (sum[stk.back() + 1] != sum[i + 1]) {
        vis.erase(sum[stk.back() + 1]);
        group.push_back(stk.back());
        stk.pop_back();
      }
      if (i < 2 * N - 1) {
        AddEdge((stk.back() + 2 * N) % (2 * N), (i + 1) % (2 * N));
        AddEdge((group.back() + 2 * N) % (2 * N), (i + 1) % (2 * N));
      }
      vec.push_back(group);
    } else {
      vis.insert(sum[i + 1]);
      stk.push_back(i);
    }
  }
  vector<int> gr;
  for (int u : stk) {
    if (u != -1) {
      gr.push_back(u);
    }
  }
  if (!gr.empty()) {
    vec.push_back(gr);
  }
  cout << 2 * N - vec.size() << "\n";
  for (auto gr : vec) {
    reverse(gr.begin(), gr.end());
    for (int i = 1; i < gr.size(); ++i) {
      if ((gr[i] - gr[0] + 2 * N) % (2 * N) != 1 &&
          (gr[0] - gr[i] + 2 * N) % (2 * N) != 1) {
        int a = gr[0], b = gr[i];
        AddEdge(a, b);
      }
    }
  }
  assert(edges.size() == 2 * N - 3);
  for (auto [a, b] : edges) {
    cout << a + 1 << " " << b + 1 << "\n";
  }
}
