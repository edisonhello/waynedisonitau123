#include <bits/stdc++.h>
using namespace std;

const int kN = 531441;
long long a[kN], b[kN], c[kN];

int main() {
    int k; cin >> k;
    int n = 1;
    for (int i = 0; i < k; ++i) n *= 3;
    auto Mex3 = [&](int a, int b) {
        int c = 0;
        for (int i = 0, j = 1; i < k; ++i, j *= 3) {
            int x = a % 3, y = b % 3;
            int z = 0;
            while (z == x || z == y) ++z;
            c += j * z;
            a /= 3, b /= 3;
        }
        return c;
    };
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[Mex3(i, j)] += a[i] * b[j];
            // printf("mex3(%d, %d) = %d\n", i, j, Mex3(i, j));
            // cnt[Mex3(i, j)].emplace_back(i, j);

        }
    }
    for (int i = 0; i < n; ++i) {
        cout << c[i] << ' ';
        // printf("i = %d: ", i);
        // for (auto u : cnt[i]) printf("(%d, %d) ", u.first, u.second);
        // puts("");
    }
    cout << endl;
}
