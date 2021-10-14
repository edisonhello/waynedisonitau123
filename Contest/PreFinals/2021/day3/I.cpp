#include <bits/stdc++.h>
using namespace std;


int main() {
  vector<string> v(6);
  for (int i = 0; i < 6; ++i) cin >> v[i];

  int dif = 0;
  for (int i = 0; i < 3; ++i) {
    if (v[i] != v[i + 3]) ++dif;
  }

  if (dif == 0) {
    if (v[0] == v[2] && v[0] != v[1]) {
      cout << 7 << endl;
    } else {
      cout << 8 << endl; 
    }
  } else if (dif == 1) {
    cout << 6 << endl;
  } else if (dif == 2) {
    cout << 5 << endl;
  } else {
    cout << 4 << endl;
  }
}
