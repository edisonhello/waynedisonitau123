#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, E, PP;
    while (cin >> N >> E >> PP) {
        if (N == 0 && E == 0 && PP == 0) break;
        vector<int> e(N + 1), p(N + 1), fa(N + 1);
        for (int i = 0; i < N; ++i) {
            cin >> e[i + 1] >> p[i + 1] >> fa[i + 1];
        }
        int64_t P = 0, Q = 1;
        for (int i = 1; i <= N; ++i) {
            int X = i;
            int64_t Top = 0, Bot = 0;
            while (X > 0) {
                if (__int128(Top + 2 * p[X]) * Q > __int128(Bot + 2 * e[X]) * P) {
                    P = Top + 2 * p[X];
                    Q = Bot + 2 * e[X];
                }
                Bot += e[X];
                Top += 2 * p[X];
                X = fa[X];
            }
        }
        long double h = static_cast<long double>(P) / Q;
        long double Need = static_cast<long double>(PP) / E / h;
        Need = log(Need) / h;
        cout << max<int64_t>(0, int64_t(ceil(Need))) << "\n";
    }
}
