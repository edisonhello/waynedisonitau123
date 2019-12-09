#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

pair<int, int> st[19][200005];
pair<int, int> a[19][200005];
pair<int, int> ans[200005];
pair<int, int> tmp[200005];

// #define lc ((id * 2) + 1)
// #define rc ((id * 2) + 2)
// #define mid ((l + r) >> 1)
// void pull(int z, int id) {
//     seg[z][id].first = min(seg[z][lc].first, seg[z][rc].first);
//     seg[z][id].second = max(seg[z][lc].second, seg[z][rc].second);
// }

// void buildseg(int lev, int id, int l, int r) {
//     if (l == r) seg[lev][id] = a[l];
//     else {
//         buildseg(lev, lc, l, mid);
//         buildseg(lev, rc, mid + 1, r);
//         pull(lev, id);
//     }
// }

pair<int, int> pull(pair<int, int> p1, pair<int, int> p2) {
    return make_pair(min(p1.first, p2.first), max(p1.second, p2.second));
}

// pair<int, int> query(int lev, int id, int l, int r, int ql, int qr) {
//     if (qr < l || r < ql) return make_pair(1000000000, 0);
//     if (ql <= l && r <= qr) return seg[lev][id];
//     pair<int, int> q1 = query(lev, lc, l, mid, ql, qr), q2 = query(lev, rc, mid + 1, r, ql, qr);
//     return pull(q1, q2);
// }

int sufmax[200005];

pair<int, int> query(int l, int r) {
    if (l == r) return st[0][l];
    int z = 31 - __builtin_clz(r - l + 1);
    return pull(st[z][l], st[z][r - (1 << z) + 1]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[0][i].first, a[0][i] = make_pair(max(1, i - a[0][i].first), min(n, i + a[0][i].first));
    // for (int i = 1; i <= n; ++i) st[0][0][i] = a[0][i];
    // for (int z = 1; (1 << z) <= n; ++z) 
    //     for (int i = 1; i + (1 << z) - 1 <= n; ++i) 
    //         st[0][z][i] = pull(st[0][z - 1][i], st[0][z - 1][i + (1 << (z - 1))]);
    // buildseg(0, 0, 1, n);
    for (int z = 1; z <= 18; ++z) {
        for (int i = 1; i <= n; ++i) st[0][i] = a[z - 1][i];
        for (int y = 1; (1 << y) <= n; ++y) 
            for (int i = 1; i + (1 << y) - 1 <= n; ++i) 
                st[y][i] = pull(st[y - 1][i], st[y - 1][i + (1 << (y - 1))]);

        for (int i = 1; i <= n; ++i) {
            a[z][i] = query(a[z - 1][i].first, a[z - 1][i].second);
            // a[i] = query(z - 1, 0, 1, n, a[i].first, a[i].second);
            // cerr << "a[" << i << "] in z = " << z << ": (" << a[z][i].first << ", " << a[z][i].second << ")" << endl;
        }
        // buildseg(z, 0, 1, n);
        // for (int i = 1; i <= n; ++i) st[z][0][i] = a[i];
        // for (int y = 1; (1 << y) <= n; ++y) 
        //     for (int i = 1; i + (1 << y) - 1 <= n; ++i) 
        //         st[z][y][i] = pull(st[z][y - 1][i], st[z][y - 1][i + (1 << (y - 1))]);
    }

    for (int i = 1; i <= n; ++i) ans[i] = make_pair(i, i);

    int aa = 0;
    for (int z = 18; z >= 0; --z) {
        for (int i = 1; i <= n; ++i) st[0][i] = a[z][i];
        for (int y = 1; (1 << y) <= n; ++y) 
            for (int i = 1; i + (1 << y) - 1 <= n; ++i) 
                st[y][i] = pull(st[y - 1][i], st[y - 1][i + (1 << (y - 1))]);

        bool ok = false;
        for (int i = 1; i <= n; ++i) 
            tmp[i] = query(ans[i].first, ans[i].second);

        sufmax[n] = tmp[n].first;
        for (int i = n - 1; i >= 1; --i) sufmax[i] = max(sufmax[i + 1], tmp[i].first);

        for (int i = 1; i <= n; ++i) {
            int r = tmp[i].second;
            if (r == n) continue;
            int l = sufmax[r + 1];
            if (l > i) { ok = true; break; }
        }

        if (ok) {
            // cerr << "z = " << z << " ok" << endl;
            aa += 1 << z;
            for (int i = 1; i <= n; ++i) ans[i] = tmp[i];
        }
    }

    cout << aa + 1 << endl;

    // auto check = [&] (int t) {
    //     // cerr << "check " << t << endl;
    //     for (int i = 1; i <= n; ++i) {
    //         int tt = t;
    //         pair<int, int> now = make_pair(i, i);
    //         for (int z = 17; z >= 0; --z) if (tt >= (1 << z)) {
    //             now = query(z, now.first, now.second);
    //             tt -= 1 << z;
    //         }
    //         a[i] = now;
    //         // cerr << "go from " << i << " = " << now.first << " " << now.second << endl;
    //     }

    //     sufmax[n] = a[n].first;
    //     for (int i = n - 1; i >= 1; --i) sufmax[i] = max(sufmax[i + 1], a[i].first);

    //     for (int i = 1; i <= n; ++i) {
    //         int r = a[i].second;
    //         if (r == n) continue;
    //         int l = sufmax[r + 1];
    //         if (l > i) return true;
    //     }
    //     return false;
    // };

    // int L = 0, R = n - 1;
    // while (L < R) {
    //     int M = (L + R + 1) >> 1;
    //     if (check(M)) L = M;
    //     else R = M - 1;
    // }
    // cout << L + 1 << endl;
    // exit(0);

    // int mx = 0;
    // for (int i = 1; i <= n; ++i) {
    //     int aa = 0;
    //     pair<int, int> now = make_pair(i, i);
    //     for (int z = 18; z >= 0; --z) {
    //         pair<int, int> tmp = query(z, 0, 1, n, now.first, now.second);
    //         if (tmp != make_pair(1, n)) {
    //             cerr << "i = " << i << ", tmp = " << tmp.first << " " << tmp.second << endl;
    //             now = tmp;
    //             aa += (1 << z);
    //         }
    //     }
    //     mx = max(mx, aa + 1);
    // }
    // cout << mx << endl;
}
