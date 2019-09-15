#include <bits/stdc++.h>
using namespace std;

#define getchar gtx
inline int gtx() {
    static const int N = 4096;
    static char b[N];
    static char *p = b, *e = b;
    if (p == e) {
        e = b + fread(b, 1, N, stdin);
        p = b;
    }
    return *p++;
}

inline void rit(int &x) {
    char c = 0;
    while (c = gtx(), (c < '0') || c > '9');
    x = c & 15;
    while (c = gtx(), c >= '0' && c <= '9') x = x * 10 + (c & 15);
}

const int mod = 3428977;
const int pp = 184903;

int a[1005][1005];
int at[1000006][2];
int bit[1005][1005];
int lr[1005][2], ud[1005][2];

void bitadd(int x, int y) {
    for (; x < 1005; x += x & -x) {
        for (int yy = y; yy < 1005; yy += yy & -yy) {
            ++bit[x][yy];
        }
    }
}

int query(int x, int y) {
    int v = 0;
    for (; x; x -= x & -x) {
        for (int yy = y; yy; yy -= yy & -yy) {
            v += bit[x][yy];
        }
    }
    return v;
}

int query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
}

int main() {
    int t; rit(t); for (int ts = 1; ts <= t; ++ts) {
        memset(bit, 0, sizeof(bit));
        for (int i = 0; i < 1005; ++i) lr[i][0] = ud[i][0] = 10000, lr[i][1] = ud[i][1] = 0;

        int n, m; rit(n); rit(m);
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
            rit(a[i][j]);
            at[a[i][j]][0] = i;
            at[a[i][j]][1] = j;
        }
        int sum = 0;
        int np = pp;
        int now = 0;

        auto add = [&] (int x) {
            ++x;
            now = (now + x) % mod;
            // cerr << "rectangle add " << x << ", now = " << now << endl;
            sum = (sum + now * 1ll * np) % mod;
            np = 1ll * np * pp % mod;
        };

        auto update = [&] (int x, int y) {
            lr[x][0] = min(lr[x][0], y);
            lr[x][1] = max(lr[x][1], y);
            ud[y][0] = min(ud[y][0], x);
            ud[y][1] = max(ud[y][1], x);
            bitadd(x, y);
        };


        for (int i = 1; i <= n * m; ++i) {
            int l = 0, r = 0, u = 0, d = 0;
            int x = at[i][0], y = at[i][1];
            // cerr << "add " << x << " " << y << endl;
            if (x > 1 && a[x - 1][y] < i) ++u;
            if (x < n && a[x + 1][y] < i) ++d;
            if (y > 1 && a[x][y - 1] < i) ++l;
            if (y < m && a[x][y + 1] < i) ++r;
            int L = lr[x][0];
            int R = lr[x][1];
            int U = ud[y][0];
            int D = ud[y][1];
            if (l + r + u + d == 1) {
                if (l) {
                    add(query(x, L, x, y));
                } 
                if (r) {
                    add(query(x, y, x, R));
                }
                if (u) {
                    add(query(U, y, x, y));
                }
                if (d) {
                    add(query(x, y, D, y));
                }
            }
            if (l && u) {
                add(query(U, L, x, y));
            }
            if (u && r) {
                add(query(U, y, x, R));
            }
            if (r && d) {
                add(query(x, y, D, R));
            }
            if (d && l) {
                add(query(x, L, D, y));
            }
            if (l + r + u + d == 0) {
                add(0);
            }
            update(x, y);
        }

        printf("Case %d: %d\n", ts, sum);
    }
}
