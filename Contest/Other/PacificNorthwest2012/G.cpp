#include <bits/stdc++.h>
using namespace std;

long long C[80][80];

int main() {
    C[0][0] = 1;
    for (int i = 1; i < 80; ++i) {
        for (int j = 0; j <= i; ++j) {
            C[i][j] = C[i - 1][j];
            if (j) C[i][j] += C[i - 1][j - 1];
        }
    }

    long long n; while (cin >> n) {
        int start = 0;
        long long cnt = 0;
        ++n;
        for (int i = 60; i >= 0; --i) {
            if (!((1ll << i) & n)) continue;
            for (int j = start; j <= 60; j += 3) {
                cnt += C[i][j];
            }

            start = (start + 2) % 3;
        }

        cout << "Day " << n - 1 << ": " << "Level = " << cnt - 1 << '\n';
    }
}

