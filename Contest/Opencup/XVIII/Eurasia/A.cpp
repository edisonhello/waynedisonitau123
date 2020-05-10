#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        while (s.size() % 4 != 0) s = "0" + s;
        int n = s.size();

        auto Hex = [&](int v) {
            if (v < 10) return v + '0';
            return (v - 10) + 'A';
        };

        for (int i = 0; i < n; i += 4) {
            int v = 0;
            for (int j = 0; j < 4 && i + j < n; ++j) v = v * 2 + (s[i + j] - '0');
            cout << (char)Hex(v);
        }
        cout << "\n";
    }
}

