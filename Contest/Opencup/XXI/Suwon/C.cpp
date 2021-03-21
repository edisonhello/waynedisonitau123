#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int Z = 250000;
struct Seg {
    int v, mx, mn;
} seg[Z * 4];
// int v[Z * 4], mx[Z * 4], mn[Z * 4];

void addtag(int o, int v) {
    seg[o].v += v;
    seg[o].mx += v;
    seg[o].mn += v;
}

#define lc ((o << 1) | 0)
#define rc ((o << 1) | 1)

void pull(int o) {
    seg[o].mx = max(seg[lc].mx, seg[rc].mx);
    seg[o].mn = min(seg[lc].mn, seg[rc].mn);
}

void push(int o) {
    if (!seg[o].v) return;
    addtag(lc, seg[o].v);
    addtag(rc, seg[o].v);
    seg[o].v = 0;
}

#define mid ((l + r) >> 1)

vector<pair<int, int>> zero_segs, tmp;
void merge_zero() {
    if (zero_segs.empty()) return;
    tmp.clear();
    tmp.push_back(zero_segs[0]);
    for (auto [l, r] : zero_segs) {
        if (l <= tmp.back().second + 1) {
            tmp.back().second = max(tmp.back().second, r);
        } else {
            tmp.emplace_back(l, r);
        }
    }
    zero_segs.swap(tmp);
}

void find_zero(int o, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return;
    // cerr << "l r ql qr mx mn " << l << ' ' << r << ' ' << ql << ' ' << qr << ' ' << now->mx << ' ' << now->mn << endl;
    if (ql <= l && r <= qr) {
        if (seg[o].mx == 0) {
            zero_segs.emplace_back(l, r);
            return;
        }
    }
    if (seg[o].mn >= 1) return;
    push(o);
    find_zero(lc, l, mid, ql, qr);
    find_zero(rc, mid + 1, r, ql, qr);
    return;
}

void modify(int o, int l, int r, int ml, int mr, int v) {
    if (mr < l || r < ml) return;
    if (ml <= l && r <= mr) {
        addtag(o, v);
        return;
    }
    push(o);
    modify(lc, l, mid, ml, mr, v);
    modify(rc, mid + 1, r, ml, mr, v);
    pull(o);
    return;
}
#undef mid

vector<tuple<int, int, int, int>> ev, sev;
int solve(int length, auto &v) {
    ev.clear();

    for (auto &vv : v) {
        sev.clear();
        for (auto [x, y] : vv) {
            sev.emplace_back(x, -1, y, y + length);
            sev.emplace_back(x + length, 1, y, y + length); // -1 -> add, 1 -> remove
        }

        sort(sev.begin(), sev.end());

        for (auto [x, type, yl, yr] : sev) {
            if (type == -1) {
                zero_segs.clear();
                find_zero(1, 0, Z, yl, yr);
                merge_zero();
                for (auto [l, r] : zero_segs) {
                    ev.emplace_back(x, -1, l, r);
                }
                modify(1, 0, Z, yl, yr, 1);
            } else {
                modify(1, 0, Z, yl, yr, -1);
                zero_segs.clear();
                find_zero(1, 0, Z, yl, yr);
                merge_zero();
                for (auto [l, r] : zero_segs) {
                    ev.emplace_back(x, 1, l, r);
                }
            }
        }
    }

    sort(ev.begin(), ev.end());
    int mx = 0;
    for (auto [x, type, yl, yr] : ev) {
        if (type == -1) {
            modify(1, 0, Z, yl, yr, 1);
            mx = max(mx, seg[1].mx);
        } else {
            modify(1, 0, Z, yl, yr, -1);
        }
    }
    return mx;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;

    vector<vector<pair<int, int>>> ps(k + 1);
    while (n--) {
        int x, y, z; cin >> x >> y >> z;
        ps[z].emplace_back(x, y);
    }

    int L = 0, R = 250000;
    while (L < R) {
        int M = (L + R) / 2;
        if (solve(M, ps) == k) R = M;
        else L = M + 1;
    }

    cout << L << endl;
}

