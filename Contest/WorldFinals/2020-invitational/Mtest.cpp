#include <bits/stdc++.h>
using namespace std;

int get_selected(double p) {
  int r = rand();
  return (double)r / RAND_MAX < p;
}

vector<double> get_s(int x) {
  cerr << "mn = " << x << endl;

  auto getv = [&](double a, double b, double c, double d, double e) {
    vector<double> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);
    v.push_back(e);
    return v;
  };

  vector<double> v;
  if (x >= 30) {
    v.push_back(0);
    v.push_back(0);
    v.push_back(0);
    v.push_back(0);
    v.push_back(0);
  } else {
    // if (x == 1) v = getv(1, 0, 0, 0, 0);
    // if (x == 2) v = getv(0.9, 0.1, 0, 0, 0);
    // if (x == 3) v = getv(0.8, 0.2, 0, 0, 0);
    // if (x == 4) v = getv(0.7, 0.3, 0, 0, 0);
    // if (x == 5) v = getv(0.6, 0.4, 0, 0, 0);
    // if (x == 6) v = getv(0.5, 0.5, 0, 0, 0);
    // if (x == 7) v = getv(0.4, 0.5, 0.1, 0, 0);
    // if (x == 8) v = getv(0.4, 0.4, 0.2, 0, 0);
    // if (x == 9) v = getv(0.3, 0.4, 0.3, 0, 0);
    // if (x == 10) v = getv(0.3, 0.3, 0.4, 0, 0);
    // if (x == 11) v = getv(0.2, 0.3, 0.4, 0.1, 0);
    // if (x == 12) v = getv(0.1, 0.3, 0.4, 0.2, 0);
    // if (x == 13) v = getv(0.1, 0.2, 0.4, 0.3, 0);
    // if (x == 14) v = getv(0.1, 0.2, 0.3, 0.3, 0.1);
    // if (x == 15) v = getv(0.0, 0.2, 0.3, 0.4, 0.1);
    // if (x == 16) v = getv(0.0, 0.1, 0.3, 0.4, 0.2);
    // if (x == 17) v = getv(0.0, 0.0, 0.3, 0.4, 0.3);
    // if (x == 18) v = getv(0.0, 0.0, 0.2, 0.4, 0.4);
    // if (x == 19) v = getv(0.0, 0.0, 0.2, 0.3, 0.5);
    // if (x == 20) v = getv(0.0, 0.0, 0.1, 0.3, 0.6);
    // if (x == 21) v = getv(0.0, 0.0, 0.0, 0.3, 0.7);
    // if (x == 22) v = getv(0.0, 0.0, 0.0, 0.2, 0.8);
    // if (x == 23) v = getv(0.0, 0.0, 0.0, 0.1, 0.7);
    // if (x == 24) v = getv(0.0, 0.0, 0.0, 0.0, 0.6);
    for (int i = 0; i < 5; ++i) {
      if (x < 5) {
        // v.push_back(1);
        // break;
        double p1 = (double)(10 - x) / 10;
        v.push_back(p1);
        if (v.size() < 5u)
          v.push_back(1 - p1);
        break;
      } else {
        v.push_back(0);
        x -= 5;
      }
    }
  }

  while (v.size() < 5u) v.push_back(0);

  for (double i : v) cerr << i << ' ';
  cerr << endl;

  return v;
}

int get_or(vector<double> p) {
  double sum = 0;
  for (auto i : p) {
    assert(i >= 0);
    sum += i;
  }
  assert(sum <= 1);

  double z = (double)rand() / RAND_MAX;

  for (int i = 0; i < 5; ++i) {
    if (z < p[i]) return i;
    z -= p[i];
  }
  return 5;
}

double play(int mn1, int mn2) {
  vector<double> prob1 = get_s(mn1);
  vector<double> prob2 = get_s(mn2);

  // int or1 = get_or(prob1);
  // int or2 = get_or(prob2);

  if (mn2 < mn1) swap(mn1, mn2), swap(prob1, prob2);

  prob2.push_back(1 - (prob2[0] + prob2[1] + prob2[2] + prob2[3] + prob2[4]));

  double sum = 0;
  for (int i = 0; i < 5; ++i) {
    for (int j = i + 1; j < 6; ++j) {
      sum += prob1[i] * prob2[j];
    }
  }
  return sum;
}

int main() {
  srand(time(0) * clock());

  int t = 10000;
  vector<int> all(100);
  iota(all.begin(), all.end(), 1); // [1 - 100]


  double probs = 0;
  for (int i = 0; i < t; ++i) {
    random_shuffle(all.begin(), all.end());
    int mn1 = *min_element(all.begin(), all.begin() + 5);
    int mn2 = *min_element(all.begin() + 5, all.begin() + 10);

    probs += play(mn1, mn2);
  }

  cout << probs / t << endl;
}

