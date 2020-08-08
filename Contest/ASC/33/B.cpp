#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  constexpr int kIter = 100'000'000;

  freopen("beavers.in", "r", stdin);
  freopen("beavers.out", "w", stdout);
  vector<string> s(10);

  for (int i = 0; i < 10; ++i) {
    cin >> s[i];
  }
  bitset<kIter * 2 + 1> state;
  state.reset();

  auto State = [&](int p) -> bool {
    return state.test(p + kIter);
  };

  auto SetState = [&](int p, bool v) {
    state[p + kIter] = v;
  };

  int p = 0, mood = 0;
  for (int it = 0; it < kIter; ++it) {
    int g = (int)State(p) + 2 * mood;
    if (s[g][2] == 'H') {
      cout << "happy beaver"
           << "\n";
      return 0;
    }
    SetState(p, (bool)(s[g][0] - '0'));
    mood = s[g][2] - 'A';
    p += s[g][1] == 'L' ? -1 : 1;
  }
  cout << "unhappy beaver" << "\n";
}
