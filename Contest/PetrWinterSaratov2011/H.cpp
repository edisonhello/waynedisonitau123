#include <bits/stdc++.h>
using namespace std;

struct node {
    long long mn, tag;
    int mni;
} seg[2000005 * 4];
node operator + (const node &a, const node &b) {
    if (a.mn < b.mn) {
        return node{a.mn, 0, a.mni};
    } else {
        return node{b.mn, 0, b.mni};
    }
}

#define lc ((o << 1) | 0)
#define rc ((o << 1) | 1)
#define mid ((l + r) >> 1)
void pull(int o) {
    seg[o] = seg[lc] + seg[rc];
}
void push(int o) {
    seg[lc].mn += seg[o].tag;
    seg[lc].tag += seg[o].tag;
    seg[rc].mn += seg[o].tag;
    seg[rc].tag += seg[o].tag;
    seg[o].tag = 0;
}
void build(int o, int l, int r) {
    if (l == r) {
        seg[o].mni = l;
        return;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pull(o);
}
void modify(int o, int l, int r, int ml, int mr, long long t) {
    if (mr < l || r < ml) return;
    if (ml <= l && r <= mr) {
        seg[o].mn += t;
        seg[o].tag += t;
        return;
    }
    push(o);
    modify(lc, l, mid, ml, mr, t);
    modify(rc, mid + 1, r, ml, mr, t);
    pull(o);
}
node query(int o, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return node{LLONG_MAX, 0, 0};
    if (ql <= l && r <= qr) return seg[o];
    push(o);
    return query(lc, l, mid, ql, qr) + query(rc, mid + 1, r, ql, qr);
}

struct Segment {
    int l, r, t;
} segment[100005];

int main() {
#ifdef ONLINE_JUDGE
    freopen("lamps.in", "r", stdin);
    freopen("lamps.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> num;
    for (int i = 0; i < n; ++i) cin >> segment[i].l >> segment[i].r >> segment[i].t;
    for (int i = 0; i < n; ++i) num.push_back(segment[i].l), num.push_back(segment[i].r);
    sort(num.begin(), num.end());
    int MX = num.size();
    for (int i = 0; i < n; ++i) {
        segment[i].l = upper_bound(num.begin(), num.end(), segment[i].l) - num.begin();
        segment[i].r = upper_bound(num.begin(), num.end(), segment[i].r) - num.begin() - 1;
    }
    // sort(segment, segment + n, [] (const Segment &a, const Segment &b) { return a.r < b.r; });
    build(1, 1, MX);
    for (int i = 0; i < n; ++i) {
        modify(1, 1, MX, segment[i].l, segment[i].r, segment[i].t);
    }
    set<pair<int, int>> left_side, right_side;
    map<int, vector<int>> events;
    for (int i = 0; i < n; ++i) {
        left_side.insert(make_pair(segment[i].r, i));  // maintain the smallest right side
        right_side.insert(make_pair(segment[i].l, i)); // maintain the largest left side
        events[segment[i].l].push_back(i + 1);
        events[segment[i].r + 1].push_back(-i - 1);
    }
    long long in_cost = 0, min_cost = LLONG_MAX;
    pair<int, int> cut_point(-1, -1);
    // for (int i = 0; i < n; ++i) {
    bool left_aru = false;
    for (auto &p : events) {
        for (int i : p.second) {
            if (i > 0) {
                int x = i - 1; // segment x start
                in_cost += segment[x].t;
                modify(1, 1, MX, segment[x].l, segment[x].r, -segment[x].t);
                left_side.erase(make_pair(segment[x].r, x));
                right_side.erase(make_pair(segment[x].l, x));
            } else {
                int x = -i - 1; // segment x end
                in_cost -= segment[x].t;
                left_aru = true;
            }
        }
        // modify(1, 1, MX, segment[i].l, segment[i].r - 1, -segment[i].t);
        // left_side.erase(segment[i].r, i);
        // right_side.erase(segment[i].l, i);
        // if (i == n - 1) break;
        if (left_side.empty()) break;
        if (!left_aru) continue;
        int L = left_side.begin()->first + 1;
        int R = right_side.rbegin()->first - 1;
        if (L > R) continue;
        node res = query(1, 1, MX, L, R);
        if (in_cost + res.mn < min_cost) {
            min_cost = in_cost + res.mn;
            cut_point = make_pair(p.first, res.mni);
        }
    }
    if (cut_point.first == -1) {
        cout << -1 << endl;
        exit(0);
    }
    vector<int> cuts;
    for (int i = 0; i < n; ++i) {
        if (segment[i].l <= cut_point.first && cut_point.first <= segment[i].r) {
            cuts.push_back(i + 1);
        } else if (segment[i].l <= cut_point.second && cut_point.second <= segment[i].r) {
            cuts.push_back(i + 1);
        }
    }
    cout << min_cost << endl;
    cout << cuts.size() << endl;
    for (int i : cuts) {
        cout << i << " \n"[i == cuts.back()];
    }
}
