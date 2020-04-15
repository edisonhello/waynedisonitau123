#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *l, *r;
    int len, tag, v;
    void addtag() {
        v = len - v;
        tag ^= 1;
    }
    void push() {
        if (tag) {
            tag = 0;
            l->addtag();
            r->addtag();
        }
    }
    void pull() {
        v = l->v + r->v;
    }
};

#define mid ((l + r) >> 1)
void Build(Node *now, int l, int r) {
    now->len = r - l + 1;
    now->tag = 0;
    now->v = 0;
    now->l = now->r = 0;
    if (l == r) {
        return;
    }
    Build(now->l = new Node(), l, mid);
    Build(now->r = new Node(), mid + 1, r);
}

void Modify(Node *now, int l, int r, int ml, int mr) {
    if (mr < l || r < ml) return;
    if (ml <= l && r <= mr) {
        now->addtag();
        return;
    }
    now->push();
    Modify(now->l, l, mid, ml, mr);
    Modify(now->r, mid + 1, r, ml, mr);
    now->pull();
}

void Delete(Node *now) {
    if (!now) return;
    if (now->l) Delete(now->l);
    if (now->r) Delete(now->r);
    delete now;
}

long long init_sum = 0;
int meow(vector<vector<pair<int, int>>> &ev, int X) {
    init_sum = 0;
    Node *root = new Node();
    Build(root, 0, X - 1);
    int odd = 0;
    for (auto &v : ev) {
        for (auto &p : v) Modify(root, 0, X - 1, p.first, p.second);
        odd += root->v & 1;
        init_sum += root->v;
    }
    Delete(root);
    return odd;
}

int Reduce(int a) {
    if (a == 0) return 0;
    if (a & 1) return 1;
    return 2;
}

bool Same(pair<int, int> a, pair<int, int> b) {
    return Reduce(a.first) == Reduce(b.first) && Reduce(a.second) == Reduce(b.second);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, q; cin >> n >> m >> q;

    vector<vector<pair<int, int>>> eventn(n + 1);
    vector<vector<pair<int, int>>> eventm(m + 1);
    while (q--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        --x1, --y1, --x2, --y2;
        eventn[x1].emplace_back(y1, y2);
        eventn[x2 + 1].emplace_back(y1, y2);
        eventm[y1].emplace_back(x1, x2);
        eventm[y2 + 1].emplace_back(x1, x2);
    }

    int b = meow(eventm, n);
    int a = meow(eventn, m);

    // cerr << "a = " << a << " b = " << b << endl;

    long long cost = init_sum;
    vector<pair<int, int>> vv = {{a, b}};

    while (a || b) {
        int aa = a * ((m - b) % 2) + (n - a) * (b % 2);
        int bb = b * ((n - a) % 2) + (m - b) * (a % 2);

        pair<int, int> p(aa, bb);
        bool dead = 0;
        for (auto &pp : vv) if (Same(pp, p)) dead = 1;
        if (dead) {
            cout << -1 << endl;
            exit(0);
        }
        vv.push_back(p);

        cost += 1ll * a * (m - b) + 1ll * b * (n - a);

        a = aa, b = bb;
        cerr << "a = " << a << " b = " << b << " cost = " << cost << endl;
    }

    cout << cost << endl;
}

