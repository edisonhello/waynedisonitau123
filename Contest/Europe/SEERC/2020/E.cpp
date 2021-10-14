#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    A[i] %= 3;
  }
  int x = 0, y = 0;
  vector<vector<int>> cnt(3, vector<int>(3));
  cnt[0][0] = 1;

  int64_t ans = 0;

  for (int i = 0; i < N; ++i) {
    (x += A[i]) %= 3;
    (y += A[i] * A[i]) %= 3;
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; ++k) {
        int a = (x + 3 - j) % 3;
        int b = (y + 3 - k) % 3;
        if ((a * a + 3 - b) % 3 == 0) ans += cnt[j][k];
      }
    }
    cnt[x][y]++;
  }
  cout << ans << "\n";
}
