#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int sum = 0;
    while (n--) {
        int t; cin >> t;
        sum += t;
    }
    cout << (sum + 1) / 2 << endl;
}
