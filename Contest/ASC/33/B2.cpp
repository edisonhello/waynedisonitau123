#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("beavers.in", "r", stdin);
  freopen("beavers.out", "w", stdout);
  vector<string> s(10);
  for (int i = 0; i < 10; ++i) {
    cin >> s[i];
  }
  unordered_map<int, uint64_t> state;

  auto State = [&](int p) -> int {
    int b = p / 64, f = p % 64;
    if (state.find(b) == state.end()) return 0;
    return (state[b] >> f & 1);
  };

  auto SetState = [&](int p, int v) {
    int b = p / 64;
    int f = p % 64;
    if (state.find(b) == state.end() && v == 0) return;
    state[b] &= ~(1ULL << f);
    if (v) {
      state[b] ^= (1ULL << f);
    } else {
      if (state[b] == 0) {
        state.erase(b);
      }
    }
  };

  int p = 0, mood = 0;
  constexpr int kIter = 60'000'000;
  for (int it = 0; it < kIter; ++it) {
    int g = State(p) + mood * 2;
    cerr << "p = " << p << " g = " << g << endl;
    if (s[g][2] == 'H') {
      cout << "happy beaver"
           << "\n";
      return 0;
    }
    SetState(p, s[g][0] - '0');
    mood = s[g][2] - 'A';
    p += s[g][1] == 'L' ? -1 : 1;
  }
  cout << "unhappy beaver" << "\n";
}

