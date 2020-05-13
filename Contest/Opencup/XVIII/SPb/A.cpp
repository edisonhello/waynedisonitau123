#include <bits/stdc++.h>
using namespace std;

int c[1000035];

int main() {
    string a, b; cin >> a >> b;
    for (int i = a.size() - 1, j = 0; i >= 0; --i, ++j) {
        if (a[i] - '0') ++c[j];
    }
    for (int i = b.size() - 1, j = 0; i >= 0; --i, ++j) {
        if (b[i] - '0') ++c[j];
    }

    for (int i = 0; i < 1000020; ++i) {
        while (c[i] >= 2 && c[i + 1] >= 2 && c[i + 2] >= 1) {
            c[i] -= 2, c[i + 1] -= 2, c[i + 2] -= 1;
        }

        while (c[i] >= 2) {
            c[i] -= 2;
            c[i + 2]++;
            c[i + 3]++;
        }
    }

    bool p = 0;
    for (int i = 1000030; i >= 0; --i) {
        if (c[i]) p = 1;
        if (p) cout << c[i];
    }
    if (!p) cout << 0;
    cout << endl;
}

