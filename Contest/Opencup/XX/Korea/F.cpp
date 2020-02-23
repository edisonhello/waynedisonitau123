#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

inline int gtx() {
    const int N = 4096;
    static char b[N], *p = b, *e = b;
    if (p == e) {
        e = b + fread(b, 1, N, stdin);
        p = b;
    }
    return *p++;
}

template <typename T> inline void rit(T &x) {
    char c = 0;
    while (c = gtx(), c < '0' || c > '9');
    x = c & 15;
    while (c = gtx(), c >= '0' && c <= '9') x = x * 10 + (c & 15);
}

const int mod = 1000000007;

struct Seg {
    int a, b;
    int atag, btag;
    Seg() : a(1), b(0), atag(1), btag(0) {}
} seg[300005 * 4];

void add_tag(int o, int v) {
    seg[o].b += v;
    if (seg[o].b >= mod) seg[o].b -= mod;
    seg[o].btag += v;
    if (seg[o].btag >= mod) seg[o].btag -= mod;
}

void mul_tag(int o, int v) {
    seg[o].a = 1ll * seg[o].a * v % mod;
    seg[o].b = 1ll * seg[o].b * v % mod;
    seg[o].atag = 1ll * seg[o].atag * v % mod;
    seg[o].btag = 1ll * seg[o].btag * v % mod;
}

void push(int o) {
    if (seg[o].atag != 1) {
        mul_tag(o * 2 + 1, seg[o].atag);
        mul_tag(o * 2 + 2, seg[o].atag);
        seg[o].atag = 1;
    }
    if (seg[o].btag != 0) {
        add_tag(o * 2 + 1, seg[o].btag);
        add_tag(o * 2 + 2, seg[o].btag);
        seg[o].btag = 0;
    }
}

#define mid ((l + r) >> 1)
void seg_add(int o, int l, int r, int ml, int mr, int v) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) {
        add_tag(o, v);
        return;
    }
    push(o);
    if (ml <= mid) seg_add(o * 2 + 1, l, mid, ml, mr, v);
    if (mr > mid) seg_add(o * 2 + 2, mid + 1, r, ml, mr, v);
}

void seg_mul(int o, int l, int r, int ml, int mr) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) {
        mul_tag(o, 2);
        return;
    }
    push(o);
    if (ml <= mid) seg_mul(o * 2 + 1, l, mid, ml, mr);
    if (mr > mid) seg_mul(o * 2 + 2, mid + 1, r, ml, mr);
}

pair<int, int> query(int o, int l, int r, int x) {
    if (l == r) return make_pair(seg[o].a, seg[o].b);
    push(o);
    if (x <= mid) return query(o * 2 + 1, l, mid, x);
    else return query(o * 2 + 2, mid + 1, r, x);
}

bool is_query[300005];
int ans[300005];

struct Seg2 {
    int mn, mx, valid, tag;
    Seg2() : mn(0), mx(0), valid(0), tag(0) {}
} seg2[300005 * 4];

void push2(int o) {
    if (seg2[o].tag) {
        seg2[o * 2 + 1].mn += seg2[o].tag;
        seg2[o * 2 + 1].mx += seg2[o].tag;
        seg2[o * 2 + 1].tag += seg2[o].tag;
        seg2[o * 2 + 2].mn += seg2[o].tag;
        seg2[o * 2 + 2].mx += seg2[o].tag;
        seg2[o * 2 + 2].tag += seg2[o].tag;
        seg2[o].tag = 0;
    }
}

void pull(int o) {
    seg2[o].valid = seg2[o * 2 + 1].valid || seg2[o * 2 + 2].valid;
    seg2[o].mn = min(seg2[o * 2 + 1].valid ? seg2[o * 2 + 1].mn : 2000000000, 
                     seg2[o * 2 + 2].valid ? seg2[o * 2 + 2].mn : 2000000000);
    seg2[o].mx = max(seg2[o * 2 + 1].valid ? seg2[o * 2 + 1].mx : 0, 
                     seg2[o * 2 + 2].valid ? seg2[o * 2 + 2].mx : 0);
}

void seg_div(int o, int l, int r, int G) {
    // cerr << "seg_div " << o << ' ' << l << ' ' << r << ' ' << G << " val is cur " << seg2[o].mn << " valid " << seg2[o].valid << endl;
    if (!seg2[o].valid) return;
    if (seg2[o].mx <= 0) return;
    if (l == r) {
        if (seg2[o].mn & 1) {
            seg2[o].valid = 0;
            ans[l] = G;
            return;
        } else {
            seg2[o].mn >>= 1;
            seg2[o].mx >>= 1;
            return;
        }
    }
    if (seg2[o].tag) push2(o);
    if (seg2[o * 2 + 1].valid) seg_div(o * 2 + 1, l, mid, G);
    if (seg2[o * 2 + 2].valid) seg_div(o * 2 + 2, mid + 1, r, G);
    pull(o);
}

void seg2_dfs(int o, int l, int r, int G) {
    if (seg2[o].mn >= 0) return;
    if (!seg2[o].valid) return;
    if (l == r) {
        ans[l] = G;
        seg2[o].valid = 0;
        return;
    }
    if (seg2[o].tag) push2(o);
    if (seg2[o * 2 + 1].valid && seg2[o * 2 + 1].mn < 0) seg2_dfs(o * 2 + 1, l, mid, G);
    if (seg2[o * 2 + 2].valid && seg2[o * 2 + 2].mn < 0) seg2_dfs(o * 2 + 2, mid + 1, r, G);
    pull(o);
}

void seg_sub(int o, int l, int r, int ql, int qr, int k, int G) {
    if (!seg2[o].valid) return;
    if (r < ql || qr < l) return;
    if (ql <= l && r <= qr) {
        seg2[o].mn -= k;
        seg2[o].mx -= k;
        seg2[o].tag -= k;
        if (seg2[o].mn < 0) {
            seg2_dfs(o, l, r, G);
        }
        return;
    }
    if (seg2[o].tag) push2(o);
    if (seg2[o * 2 + 1].valid && ql <= mid) seg_sub(o * 2 + 1, l, mid, ql, qr, k, G);
    if (seg2[o * 2 + 2].valid && qr > mid) seg_sub(o * 2 + 2, mid + 1, r, ql, qr, k, G);
    pull(o);
}

void seg_addq(int o, int l, int r, int x, int v) {
    if (l == r) {
        seg2[o].valid = 1;
        seg2[o].mn = v;
        seg2[o].mx = v;
        seg2[o].tag = 0;
        return;
    }
    if (seg2[o].tag) push2(o);
    if (x <= mid) seg_addq(o * 2 + 1, l, mid, x, v);
    else seg_addq(o * 2 + 2, mid + 1, r, x, v);
    pull(o);
}

tuple<int, int, int> qs[300005];

int main() {
    int q; rit(q);
    for (int i = 0; i < q; ++i) {
        int c; rit(c);
        if (c == 1) {
            int k; rit(k);
            qs[i] = make_tuple(c, k, 0);
        } else if (c == 2) {
            int g, x; rit(g), rit(x);
            qs[i] = make_tuple(c, g, x);
        } else if (c == 3) {
            int x; rit(x);
            qs[i] = make_tuple(c, x, 0);
        }
    }

    // build(0, 0, q);

    int G = 0;
    for (int i = 0; i < q; ++i) {
        if (get<0>(qs[i]) == 1) {
            auto [c, k, _] = qs[i];

            if (k) {
                seg_add(0, 0, q, 0, G, k);
            } else {
                seg_mul(0, 0, q, 0, G + 1);
                seg_add(0, 0, q, G + 1, G + 1, 1);
            }
            ++G;
        } else if (get<0>(qs[i]) == 2) {
            auto [c, g, x] = qs[i];
            --x;

            auto [a, b] = query(0, 0, q, g);
            // cerr << "get a b " << a << ' ' << b << ", x = " << x<< endl;
            is_query[i] = 1;
            ans[i] = (a * 1ll * x + b) % mod;
        } else if (get<0>(qs[i]) == 3) {
            ;
        }
    }

    // cerr << "G = " << G << endl;
    memset(seg, 0, sizeof(seg));

    for (int i = q - 1; i >= 0; --i) {
        if (get<0>(qs[i]) == 1) {
            auto [c, k, _] = qs[i];

            if (k) {
                seg_sub(0, 0, q, i + 1, q - 1, k, G);
            } else {
                seg_div(0, 0, q, G);
            }
            --G;
        } else if (get<0>(qs[i]) == 2) {
            ;
        } else if (get<0>(qs[i]) == 3) {
            auto [c, x, _] = qs[i];

            seg_addq(0, 0, q, i, x);
            is_query[i] = 1;
        }
    }

    // TODO: last find

    // for (int i = 0; i < q; ++i) cerr << i << " is_query " << is_query[i] << " ans " << ans[i] << endl;
    for (int i = 0; i < q; ++i) if (is_query[i]) printf("%d\n", ans[i]);

}

