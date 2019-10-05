#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, int> c;
    string s;
    int n = 0;
    while (cin >> s) {
        c[s]++;
        ++n;
    }
    for (auto it : c) {
        if (it.second + it.second >= n) {
            cout << it.first << endl;
            return 0;
        }
    }
}
