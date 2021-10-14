#include <iostream>
#include <string>
using namespace std;

int main() {
  string s;
  cin >> s;
  int64_t inv = 0;
  for (int i = 0, j = 0; i < s.size(); ++i) {
    if (s[i] == '0') inv += j;
    else j += 1;
  }
  cout << (inv % 3 == 0 ? "Bob" : "Alice")  << "\n";
}
