#include <bits/stdc++.h>
using namespace std;

struct node {
    node *l, *r;
    pair<int, int> val;
    node(): l(0), r(0), val({-1, -1}) {}
};

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
    if (l == r) return;
    build(now->l = new node(), l, mid);
    build(now->r = new node(), mid + 1, r);
}
void add(node *now, int l, int r, int x, pair<int, int> v) {
    now->val = v;
    if (l == r) {
        return;
    }
    if (x <= mid) add(now->l, l, mid, x, v);
    else add(now->r, mid + 1, r, x, v);
}
pair<int, int> query(node *now, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return make_pair(-1, -1);
    if (now->val.first == -1) return make_pair(-1, -1);
    if (ql <= l && r <= qr) return now->val;
    // auto q = query(now->l, l, mid, ql, qr);
    // if (q == make_pair(-1, -1)) q = query(now->r, mid + 1, r, ql, qr);
    auto q = query(now->r, mid + 1, r, ql, qr);
    if (q == make_pair(-1, -1)) q = query(now->l, l, mid, ql, qr);
    return q;
}

void check(int want, vector<pair<int, int>> p) {
    return;
    for (auto &[l, r] : p) {
        l -= 2, r -= 2;
    }
    int n = p.size();
    int nn = 4 * n - 1;
    int ans = -1;
    for (int z = 0; z < (1 << nn); ++z) {
        vector<int> pre(nn);
        for (int i = 0; i < nn; ++i) if (z & (1 << i)) ++pre[i];
        for (int i = 1; i < nn; ++i) pre[i] += pre[i - 1];
        // cerr << "z pre " << z << ' ';
        // for (int i : pre) cerr << i; cerr << endl;

        bool bad = 0;
        for (auto [l, r] : p) {
            if (pre[r] - (l ? pre[l - 1] : 0) != 1) {
                bad = 1;
                break;
            }
        }
        if (!bad) {
            ans = 1;
            break;
        }
    }

    if (ans != want) {
        cerr << "answer not same as bf: bf output " << ans << ' ' << want << endl;
        assert(0);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<pair<int, int>> p(n);
    for (auto &[l, r] : p) {
        cin >> l >> r;
        l += 2; r += 2;
    }

    int nn = 4 * n + 4;

    vector<int> tol(nn + 10, 0);
    vector<int> tor(nn + 10, 0);
    
    
    { 
        sort(p.begin(), p.end(), [&] (const pair<int, int> &a, const pair<int, int> &b) { return a.second < b.second; });
        int it = 0;
        int mxl = 0;
        for (int i = 0; i <= nn; ++i) {
            while (it < n && p[it].second < i) {
                mxl = max(mxl, p[it].first);
                ++it;
            }
            tol[i] = mxl;
        }
    } {
        sort(p.begin(), p.end(), [&] (const pair<int, int> &a, const pair<int, int> &b) { return a.first < b.first; });
        deque<int> dq;

        int it = 0;
        for (int i = 0; i <= nn; ++i) {
            while (dq.size() && p[dq.front()].second < i) dq.pop_front();
            while (it < n && p[it].first <= i) {
                while (dq.size() && p[dq.back()].first > p[it].first) dq.pop_back();
                dq.push_back(it);
                ++it;
            }
            if (dq.empty()) tor[i] = -1;
            else tor[i] = p[dq.front()].first - 1;
        }
    }

    // cerr << "l r: " << endl;
    // for (auto [l, r] : p) cerr << l << ' ' << r << endl;
    
    // for (int i = 0; i <= nn; ++i) cerr << i << " : " << tol[i] << ' ' << tor[i] << endl;

    node *root;
    build(root = new node(), 0, nn);
    add(root, 0, nn, 0, make_pair(0, 0));

    int last = -1;
    for (int i = 1; i <= nn; ++i) {
        int l = tol[i], r = tor[i];
        if (l > r) continue;
        auto q = query(root, 0, nn, l, r);
        // cerr << "at i = " << i << " q = " << q.first << ' ' << q.second << endl;
        if (q != make_pair(-1, -1)) add(root, 0, nn, i, make_pair(i, q.first)), last = i;
    }

    int q = last;
    if (q == -1) {
        cout << -1 << endl;
        check(-1, p);
        exit(0);
    }

    vector<int> qs;
    while (q) {
        qs.push_back(q);
        q = query(root, 0, nn, q, q).second;
    }

    // cerr << "qs: ";
    // for (int i : qs) cerr << i << ' ';
    // cerr << endl;

    vector<int> pre(nn + 10, 0);
    for (int i : qs) ++pre[i];
    for (int i = 1; i < (int)pre.size(); ++i) pre[i] += pre[i - 1];

    for (auto [l, r] : p) {
        if (pre[r] == pre[l - 1]) {
            cout << -1 << endl;
            check(-1, p);
            exit(0);
        }
        if (pre[r] > pre[l - 1] + 1) {
            // cerr << "for l r " << l << ' ' << r << endl;
            // cerr << "too many point in a seg" << endl;
            assert(false);
        }
    }

    pre = vector<int>(nn + 10, 0);
    for (auto [l, r] : p) ++pre[l], --pre[r + 1];
    for (int i = 1; i < (int)pre.size(); ++i) pre[i] += pre[i - 1];
    for (int i : qs) if (pre[i] == 0) {
        // cerr << "point not on seg" << endl;
        // assert(false);
        while (true) {}
    }

    vector<int> ans;
    for (int i : qs) {
        i -= 2;
        if (0 <= i && i <= 4 * n - 2) ans.push_back(i);
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int i : ans) cout << i << ' ';
    cout << endl;
    check(1, p);
}

