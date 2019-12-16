#include <bits/stdc++.h>
using namespace std;
#define INT array<int64_t, 4>

const int base = 1000'000'000

INT operator = (const INT &a, long long b) {
    a[2] = a[3] = 0;
    a[1] = b / base;
    a[0] = b % base;
    return a;
}
INT operator + (const INT &a, const INT &b) {
    INT x = 0;
    x[0] = a[0] + b[0] >= base
}

struct rec {
    int x1, x2, y1, y2;
} r[100005];


void findcen(int n, int &cx, int &cy) {
    INT totx = 0, toty = 0, wid = 0;
    for (int i = 0; i < n; ++i) {
        INT area = (r[i].x2 - r[i].x1) * (r[i].y2 - r[i].y1);
        totx = totx + area * (r[i].x1 + r[i].x2);
        toty = toty + area * (r[i].y1 + r[i].y2);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> r[i].x1 >> r[i].y1 >> r[i].x2 >> r[i].y2;
            r[i].x1 *= 2;
            r[i].x2 *= 2;
            r[i].y1 *= 2;
            r[i].y2 *= 2;
        }
        int cenx, ceny;
        findcen(n, cenx, ceny);

    }
}
