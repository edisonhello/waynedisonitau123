#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(clock() + time(0));
  int N = 5, Q = 1;
  cout << N << " " << Q << endl;
  vector<int> arr(2 * N, -1);
  for (int i = 0; i < N; ++i) {
    int p = rand() % (2 * N);
    while (arr[p] != -1) p = rand() % (2 * N);
    arr[p] = i;
    while (arr[p] != -1) p = rand() % (2 * N);
    arr[p] = i;
  }
  for (int i = 0; i < 2 * N; ++i) cout << arr[i] + 1 << " ";
  cout << endl;
  for (int i = 0; i < Q; ++i) {
    int u = rand() % N, v = rand() % N;
    while (u == v) {
      u = rand() % N;
      v = rand() % N;
    }
    cout << u + 1 << " " << v + 1 << endl;
  }
}
