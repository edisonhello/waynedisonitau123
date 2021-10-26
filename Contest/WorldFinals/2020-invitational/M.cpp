#include <bits/stdc++.h>
using namespace std;

vector<int> input() {
  vector<int> v;
#ifdef LOCAL
  for (int i = 0; i < 5; ++i) {
    v.push_back(rand() % 100 + 1);
  }
#else
  for (int i = 0; i < 5; ++i) {
    int t; cin >> t;
    v.push_back(t);
  }
#endif
  return v;
}

void output(double a, double b, double c, double d, double e) {
#ifdef LOCAL
  //meow
#else
  cout << fixed << setprecision(12) << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << endl;
#endif
}


int main() {
  int t; 
#ifdef LOCAL
  t = 1000;
  srand(time(0) * clock());
#else
  cin >> t; 
#endif

  while (t--) {
    auto v = input();

    int mn = *min_element(v.begin(), v.end());

    if (mn >= 92) {
      output(0, 0, 0, 0, 0);
      continue;
    }

    vector<double> p;
    if (mn >= 40) {
      p.push_back(0);
      p.push_back(0);
      p.push_back(0);
      p.push_back(0);
      p.push_back(0);
    } else {
      for (int i = 0; i < 5; ++i) {
        if (mn < 8) {
          // v.push_back(1);
          // break;
          double p1 = (double)(10 - mn) / 10;
          p.push_back(p1);
          if (p.size() < 5u)
            p.push_back(1 - p1);
          break;
        } else {
          p.push_back(0);
          mn -= 8;
        }
      }
    }

    while (p.size() < 5u) p.push_back(0);

    output(p[0], p[1], p[2], p[3], p[4]);
  }


}
