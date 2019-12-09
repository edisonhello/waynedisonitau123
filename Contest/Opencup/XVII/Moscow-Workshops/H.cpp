#include <bits/stdc++.h>
using namespace std;

// const int kC = 1000'000'000;
// int dv[kC];

// void Sieve() {
//     vector<int> pr;
//     for (int i = 2; i < kC; ++i) {
//         if (!dv[i]) dv[i] = i, pr.push_back(i);
//         for (int j = 0; i * pr[j] < kC; ++j) {
//             dv[i * pr[j]] = pr[j];
//             if (i % pr[j] == 0) break;
//         }
//     }
// }
// 
// int Count(int x) {
//     int f = 1;
//     while (x > 1) {
//         int d = dv[x], c = 0;
//         while (x % d == 0) {
//             x /= d;
//             c += 1;
//         }
//         if (d % 4 == 1) f *= (c + 1);
//         else if (c % 2 == 1) return 0;
//     }
//     return f;
// }

int x, y;
vector<pair<int, int>> anss, __ans;
int __qcnt;

int ask(int x, int y, int64_t r) {
#ifdef LOCAL
#define sq(x) (1ll * (x) * (x))
    // cerr << "Ask " << x << " " << y << " " << r << endl;
    ++__qcnt;
    if (__qcnt > 15000) {
        cerr << "query exceeded" << endl;
        exit(1);
    }
    int t = 0;
    for (auto &p : __ans) {
        int64_t z = sq(p.first - x) + sq(p.second - y);
        t += (z <= r);
    }
#else
    cout << "? " << x << " " << y << " " << r << endl;
    fflush(stdout);

    int t; cin >> t;
#endif
    return t;
}

bool checkanswer(int x, int y) {
    if (x < -1000000 || x > 1000000 || y < -1000000 || y > 1000000) return false;
    int r = ask(x, y, 0);
    if (r) anss.emplace_back(x, y);
    return r;
}

void dfs(int countin, int64_t L, int64_t R, int ptr) {
    if (countin == 0) return;
    // cerr << "dfs " << countin << ' ' << L << ' ' << R << endl;
    if (L == R) {
        for (int i = 0; 1ll * i * i <= L; ++i) {
            int j = round(sqrt(L - 1ll * i * i));
            if (1ll * j * j + 1ll * i * i == L) {
                countin -= checkanswer(x + i, y + j);
                if (i) countin -= checkanswer(x + i, y - j);
                if (j) {
                    countin -= checkanswer(x - i, y + j);
                    if (i) countin -= checkanswer(x - i, y - j);
                }
                if (countin == 0) break;
            }
        }
        return;
    }

    int64_t M = (L + R) >> 1;
    int l = ask(x, y, M) - ptr;
    int r = countin - l;
    // assert(l <= countin);
    dfs(l, L, M, ptr);
    dfs(r, M + 1, R, ptr + l);
}

void init(int n) {
    while (n--) {
        int x = rand() % 2000001 - 1000000, y = rand() % 2000001 - 1000000;
        // cerr << "ans = " << x << ' ' << y << endl;
        __ans.emplace_back(x, y);
    }
}

int main() {
    srand(time(0) * clock());
    int n; cin >> n;
#ifdef LOCAL
    init(n);
#endif
    x = rand() % 2000001 - 1000000, y = rand() % 2000001 - 1000000;
    dfs(n, 0, 1000000000'000000000, 0);
    cout << "!";
    for (auto &p : anss) cout << ' ' << p.first << ' ' << p.second;
    cout << endl;
    assert(anss.size() == n);
    fflush(stdout);
    exit(0);
    // Sieve();
    // int ans = 0, count = 0;
    // for (int i = 1; i < kC; ++i) {
    //     if (Count(i) > 100) ++count;
    //     ans = max(ans, Count(i));
    //     if ((i & (1048575)) == 0) cout << ans << ' ' << count << endl;
    // }
    // printf("%d\n", ans);
}
