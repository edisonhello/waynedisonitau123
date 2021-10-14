#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  const int kD[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int cnt[365];
  memset(cnt, 0, sizeof(cnt));
  int w = 1, d = 0, c = 0;
  for (int i = 0; i < 12; ++i) {
    for (int j = 0; j < kD[i]; ++j) {
      c++; 
      if (w != 5 && w != 6) {
        cnt[d] = c;
        c = 0;
      }
      w++;
      w %= 7;
      d++;
    }
  }

  double ans = 0;
  for (int i = 0; i < 365; ++i) {
    double p = static_cast<double>(cnt[i]) / 365;
    double q = pow(1 - p, N) + N * pow(1 - p, N - 1) * p;
    ans += 1 - q;
  }
  cout << fixed << setprecision(20) << ans << "\n";
}
