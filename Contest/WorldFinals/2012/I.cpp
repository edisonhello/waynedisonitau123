#include <bits/stdc++.h>
using namespace std;

set<pair<int, int>> mr[1000006], mc[1000006];
vector<pair<int, int>> mirs;

// [right, down, left, up]

#define mid ((l + r) >> 1)
struct node {
    node *l, *r;
    int v;
} *root, pool[1000006 * 4];
int itr;

node *gnode() {
    pool[itr].l = pool[itr].r = 0;
    pool[itr].v = 0;
    return &pool[itr++];
}

void insert(node *&now, int l, int r, int x, int v) {
    if (!now) now = gnode();
    if (l == r) {
        now->v += v;
        return;
    }
    if (x <= mid) insert(now->l, l, mid, x, v);
    else insert(now->r, mid + 1, r, x, v);
    now->v = (now->l ? now->l->v : 0) + (now->r ? now->r->v : 0);
}

int query_count(node *now, int l, int r, int ql, int qr) {
    if (!now) return 0;
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return now->v;
    return query_count(now->l, l, mid, ql, qr) + query_count(now->r, mid + 1, r, ql, qr);
}

int query_first(node *now, int l, int r, int ql, int qr) {
    if (!now) return 1000000000;
    if (!now->v) return 1000000000;
    if (qr < l || r < ql) return 1000000000;
    if (ql <= l && r <= qr) {
        if (l == r) return l;
        if (now->l && now->l->v) return query_first(now->l, l, mid, ql, qr);
        else return query_first(now->r, mid + 1, r, ql, qr);
    }
    return min(query_first(now->l, l, mid, ql, qr), query_first(now->r, mid + 1, r, ql, qr));
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts = 0;
    int r, c, m, n; while (cin >> r >> c >> m >> n) {
        cout << "Case " << (++ts) << ": ";
        for (int i = 0; i < m; ++i) {
            int x, y; cin >> x >> y;
            mirs.emplace_back(x, y);
            mr[x].insert(make_pair(y, 1));
            mc[y].insert(make_pair(x, 1));
        } // /mirror
        for (int i = 0; i < n; ++i) {
            int x, y; cin >> x >> y;
            mirs.emplace_back(x, y);
            mr[x].insert(make_pair(y, 2));
            mc[y].insert(make_pair(x, 2));
        } // \mirror

        bool to_the_bottom = 0;
        auto meow = [&] (int nr, int nc, int ndir) {
            vector<pair<pair<int, int>, pair<int, int>>> lre, ude;
            while (true) {
                if (ndir == 0) {
                    auto it = mr[nr].lower_bound(make_pair(nc + 1, -1));
                    if (it == mr[nr].end()) {
                        lre.emplace_back(make_pair(nr, nc), make_pair(nr, c + 1));
                        break;
                    }
                    int nnc = it->first;
                    if (it->second == 1) ndir = 3;
                    else ndir = 1;
                    lre.emplace_back(make_pair(nr, nc), make_pair(nr, nnc));
                    nc = nnc;
                } else if (ndir == 1) {
                    auto it = mc[nc].lower_bound(make_pair(nr + 1, -1));
                    if (it == mc[nc].end()) {
                        ude.emplace_back(make_pair(nr, nc), make_pair(r + 1, c));
                        break;
                    }
                    int nnr = it->first;
                    if (it->second == 1) ndir = 2;
                    else ndir = 0;
                    ude.emplace_back(make_pair(nr, nc), make_pair(nnr, nc));
                    nr = nnr;
                } else if (ndir == 2) {
                    auto it = mr[nr].lower_bound(make_pair(nc, -1));
                    if (it == mr[nr].begin()) {
                        lre.emplace_back(make_pair(nr, 0), make_pair(nr, nc));
                        break;
                    }
                    int nnc = prev(it)->first;
                    if (prev(it)->second == 1) ndir = 1;
                    else ndir = 3;
                    lre.emplace_back(make_pair(nr, nnc), make_pair(nr, nc));
                    nc = nnc;
                } else {
                    auto it = mc[nc].lower_bound(make_pair(nr, -1));
                    if (it == mc[nc].begin()) {
                        ude.emplace_back(make_pair(0, nc), make_pair(nr, nc));
                        break;
                    }
                    int nnr = prev(it)->first;
                    if (prev(it)->second == 1) ndir = 0;
                    else ndir = 2;
                    ude.emplace_back(make_pair(nnr, nc), make_pair(nr, nc));
                    nr = nnr;
                }
                // cout << "nr nc ndir " << nr << ' ' << nc << ' ' << ndir << endl;
            }
            if (nr == r && ndir == 0) to_the_bottom = 1;
            // cerr << "lre:" << endl;
            // for (auto &p : lre) cerr << p.first.first << " " << p.first.second << " to " << p.second.first << " " << p.second.second << endl;
            // cerr << "ude:" << endl;
            // for (auto &p : ude) cerr << p.first.first << " " << p.first.second << " to " << p.second.first << " " << p.second.second << endl;
            return make_pair(lre, ude);
        };

        auto r1 = meow(1, 0, 0);
        auto r2 = meow(r, c + 1, 2);

        if (to_the_bottom) {
            cout << 0 << endl;
        } else {
            auto get_intersect = [&] (vector<pair<pair<int, int>, pair<int, int>>> lre,
                                      vector<pair<pair<int, int>, pair<int, int>>> ude) {
                vector<tuple<int, int, int, int>> events; // query: [time, 0, l, r], modify: [time, -1, type, where]
                for (auto &pp : lre) {
                    if (pp.first.second + 1 == pp.second.second);
                    else {
                        events.emplace_back(pp.first.second + 1, -1, 1, pp.first.first),
                        events.emplace_back(pp.second.second, -1, -1, pp.first.first);
                    }
                }
                for (auto &pp : ude) {
                    if (pp.first.first + 1 <= pp.second.first - 1) {
                        events.emplace_back(pp.first.second, 0, pp.first.first + 1, pp.second.first - 1);
                    }
                }

                itr = 0;
                root = nullptr;
                sort(events.begin(), events.end());

                long long count = 0;
                pair<int, int> minpos = make_pair(1000000000, 1000000000);
                for (auto &t : events) {
                    int tm, tp, x, y; tie(tm, tp, x, y) = t;
                    if (tp == 0) {
                        pair<int, int> res;
                        res.first = query_count(root, 0, r + 1, x, y);
                        if (res.first) {
                            res.second = query_first(root, 0, r + 1, x, y);
                            count += res.first;
                            minpos = min(minpos, make_pair(res.second, tm));
                        }
                    } else {
                        if (x == 1) {
                            insert(root, 0, r + 1, y, 1);                    
                        } else {
                            insert(root, 0, r + 1, y, -1);
                        }
                    }
                }
                return make_pair(count, minpos);
            };

            pair<long long, pair<int, int>> in1 = get_intersect(r1.first, r2.second);
            pair<long long, pair<int, int>> in2 = get_intersect(r2.first, r1.second);
            long long tot = in1.first + in2.first;
            if (tot == 0) {
                cout << "impossible" << endl;
            } else {
                cout << tot << ' ';
                pair<int, int> pos = min(in1.second, in2.second);
                cout << pos.first << ' ' << pos.second << endl;
            }
        }

        for (auto &p : mirs) {
            mr[p.first].clear();
            mc[p.second].clear();
        }
        mirs.clear();
    }
}

