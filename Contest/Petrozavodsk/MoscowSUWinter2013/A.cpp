#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000006;

struct node {
    node *l, *r;
    int tag, mx;
    node() : l(0), r(0), tag(-1), mx(-1) {}
    void add(int x) {
        tag = mx = x;
    }
    void pull() {
        mx = max(l->mx, r->mx);
    }
    void push() {
        if (tag != -1) {
            l->add(tag);
            r->add(tag);
            tag = -1;
        }
    }
} *root;

int a[maxn], mex[maxn], cnt[maxn];
vector<int> pos[maxn];

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
    if (l == r) {
        now->add(mex[l]);
        return;
    }
    build(now->l = new node(), l, mid);
    build(now->r = new node(), mid + 1, r);
    now->pull();
}

void modify(node *now, int l, int r, int ml, int mr, int val) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) return now->add(val), void();
    now->push();
    modify(now->l, l, mid, ml, mr, val);
    modify(now->r, mid + 1, r, ml, mr, val);
    now->pull();
}

int search(node *now, int l, int r, int sl, int sr, int val) {
    if (l == r) return l;
    now->push();
    if (now->l->mx <= val) return search(now->r, mid + 1, r, sl, sr, val);
    else return search(now->l, l, mid, sl, sr, val);
}

int query(node *now, int l, int r, int x) {
    if (l == r) return now->mx;
    now->push();
    if (x <= mid) return query(now->l, l, mid, x);
    else return query(now->r, mid + 1, r, x);
}

int ans[maxn];


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
        ++cnt[a[i]];
        mex[i] = mex[i - 1];
        while (cnt[mex[i]]) ++mex[i];
        // cerr << mex[i] << ' ';
    }
    // cerr << endl;
    for (int i = 0; i <= 1000000; ++i) pos[i].push_back(n + 1);
    build(root = new node(), 1, n);
    vector<tuple<int, int, int>> qs;
    int q; cin >> q; for (int i = 1; i <= q; ++i) {
        int l, r; cin >> l >> r;
        qs.emplace_back(l, r, i);
    }
    sort(qs.begin(), qs.end());
    int curl = 0;
    for (auto ttt : qs) {
        int l, r, i; tie(l, r, i) = ttt;
        while (curl != l - 1) {
            ++curl;
            int v = a[curl];
            int nx = *upper_bound(pos[v].begin(), pos[v].end(), curl);
            int ll = curl, rr = nx - 1;
            ll = search(root, 1, n, ll, rr, v);
            if (query(root, 1, n, ll) <= v) continue;
            modify(root, 1, n, ll, rr, v);
            // cerr << "delete " << a[curl] << endl;
            // for (int i = 1; i <= n; ++i) cerr << query(root, 1, n, i) << ' '; cerr << endl;
        }
        ans[i] = query(root, 1, n, r);
    }
    for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}
