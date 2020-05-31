#include <bits/stdc++.h>
using namespace std;
int cnt[1234];
int main() {
    string s; cin >> s;
    for (char c : s) ++cnt[c];
    cout << (cnt['B'] == cnt['W']) << endl;
}


