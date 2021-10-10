#include <bits/stdc++.h>
using namespace std;


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int n; cin >> n;
  int v = 0;
  while (n--) {
    int x; cin >> x;
    v ^= x - 2;
  }

  string fi; cin >> fi;

  if (v) {
    cout << fi << endl;
  } else {
    if (fi == "Whiteking") cout << "Blackking" << endl;
      else cout << "Whiteking" << endl;
  }
}
