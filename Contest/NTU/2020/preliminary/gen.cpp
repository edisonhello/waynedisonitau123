#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(clock() + time(0));
  int n = 5, m = 5;
  cout << n << " " << m << endl;
  for (int i = 1; i < n; ++i) {
    int p = rand() % i;
    cout << p + 1 << " " << i + 1 << " " << rand() % 5 << "\n";
  }
  set<int> marked;
  for (int i = 0; i < m; ++i) {
    int t = rand() % 3;
    while (true) {
      if (t == 0 && marked.size() == n || t == 1 && marked.empty() || t == 2 && marked.empty()) {
        t = rand() % 3;
      } else {
        break;
      }
    }
    cout << t + 1 << " ";
    if (t == 0) {
      int x = rand() % n;
      while (marked.count(x)) {
        x = rand() % n;
      }
      marked.insert(x);
      cout << x + 1 << endl;
    }
    if (t == 1) {
      int x = rand() % n;
      while (!marked.count(x)) {
        x = rand() % n;
      }
      marked.erase(x);
      cout << x + 1 << endl;
    }
    if (t == 2) {
      int k = rand() % marked.size();
      cout << rand() % n + 1 << " " << k + 1 << endl;
    }
  }
}
