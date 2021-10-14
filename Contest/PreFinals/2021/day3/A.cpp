#include <bits/stdc++.h>
using namespace std;

int main() {
  int A = 0, B = 0;
  for (int i = 0; i < 5; ++i) {
    int x;
    cin >> x;
    A += x;
  }
  for (int i = 0; i < 5; ++i) {
    int x;
    cin >> x;
    B += x;
  }
  cout << (A >= B ? "Blue" : "Red") << "\n";
}
