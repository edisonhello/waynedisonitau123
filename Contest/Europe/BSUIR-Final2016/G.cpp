#include <bits/stdc++.h>
using namespace std;

long long tr(string s) {
    long long r = 0;
    for (char c : s) {
        r = r * 10 + c - '0';
    }
    return r;
}

int main() {
    int n; cin >> n;
    string ans = "2";
    for (int i = 2; i <= n; ++i) {
        if (tr(ans) % (1ll << i)) ans = "1" + ans;
        else ans = "2" + ans;
    }
    cout << ans << endl;
}
