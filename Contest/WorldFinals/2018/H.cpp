#include <bits/stdc++.h>
using namespace std;

int main() {
  cout << fixed << setprecision(20);
  int N, W, H;
  cin >> N >> W >> H;
  assert(W > 1 || H > 1);
  vector<tuple<int, int, int>> points;
  for (int i = 0; i < N; ++i) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    points.emplace_back(x1, y1, i);
    points.emplace_back(x2, y2, i);
  }

  auto Category = [&](int x, int y) {
    if (y == 0) return 0;
    if (x == W) return 1;
    if (y == H) return 2;
    if (x == 0) return 3;
    assert(false);
  };

  sort(points.begin(), points.end(), [&](const tuple<int, int, int>& lhs, const tuple<int, int, int>& rhs) {
    int a = Category(get<0>(lhs), get<1>(lhs));
    int b = Category(get<0>(rhs), get<1>(rhs));
    if (a != b) {
      return a < b;
    }
    if (a == 0) {
      return get<0>(lhs) < get<0>(rhs);
    }
    if (a == 1) {
      return get<1>(lhs) < get<1>(rhs);
    }
    if (a == 2) {
      return get<0>(lhs) > get<0>(rhs);
    }
    if (a == 3) {
      return get<1>(lhs) > get<1>(rhs);
    }
  });

  int diff = 0;
  vector<int> cnt(N);

  auto Add = [&](int x) {
    if (cnt[x]++ == 0) diff++;
  };

  auto Remove = [&](int x) {
    if (--cnt[x] == 0) diff--;
  };

  for (int i = 0; i < N; ++i) {
    Add(get<2>(points[i]));  
  }

  auto Print = [&](int x, int y) {
    if (y == 0) {
      assert(x != 0);
      cout << static_cast<double>(x) - 0.5 << " " << y;
    } else if (x == W) {
      assert(y != 0);
      cout << x << " " << static_cast<double>(y) - 0.5;
    } else if (y == H) {
      assert(x != W);
      cout << static_cast<double>(x) + 0.5 << " " << y;
    } else {
      assert(x == 0);
      assert(y != H);
      cout << x << " " << static_cast<double>(y) + 0.5;
    }
  };

  for (int i = 0, j = N; i < 2 * N; ++i) {
    if (diff == N) {
      cout << 1 << "\n";
      Print(get<0>(points[i]), get<1>(points[i]));
      cout << " ";
      Print(get<0>(points[j]), get<1>(points[j]));
      cout << "\n";
      return 0;
    }
    Remove(get<2>(points[i]));
    Add(get<2>(points[j]));
    j = (j + 1) % (2 * N);
  }

  cout << 2 << "\n";
  if (W == 1) {
    cout << 0 << " " << 0.5 << " " << W << " " << static_cast<double>(H) - 0.5 << "\n";
    cout << 0 << " " << static_cast<double>(H) - 0.5 << " " << W << " " << 0.5 << "\n";
  } else {
    cout << 0.5 << " " << 0 << " " << static_cast<double>(W) - 0.5 << " " << H << "\n";
    cout << 0.5 << " " << H << " " << static_cast<double>(W) - 0.5 << " " << 0 << "\n";
  }
}

