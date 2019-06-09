#include <bits/stdc++.h>
using namespace std;

char dig(int x) {
    if (x <= 9) return '0' + x;
    return x - 10 + 'A';
}

int main() {
    int b, n; cin >> b >> n;
    string s(n, 0), t(n, 0);
    s[0] = 1; t[0] = 1;
    int si = 0, ti = n - 1;
    while (si < ti) {
        if (s[si] == b - 1) { ++si; }
        else if (t[ti] == b - 1) { --ti; }
        else { ++s[si], ++t[ti]; }
    }
    // for (int i = 0; i < n; ++i) cout << dig(s[i]); cout << endl;
    // for (int i = 0; i < n; ++i) cout << dig(t[i]); cout << endl;
    for (int i = 0; i < n; ++i) {
        s[i] -= t[i];
    }
    for (int i = n - 1; i > 0; --i) {
        if (s[i] < 0) {
            s[i] += b;
            s[i - 1] -= 1;
        }
    }
    int i = 0;
    while (i < n && s[i] == 0) ++i;
    if (i == n) --i;
    for (; i < n; ++i) {
        cout << dig(s[i]);
    }
    cout << endl;
}
