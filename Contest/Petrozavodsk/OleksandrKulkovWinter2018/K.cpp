#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
int a[4005];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    cout << (a[1] - a[2] + mod) % mod << endl;
}
