#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define mid ((l + r) >> 1)

void NO() {
    cout << "(" << endl;
    exit(0);
}

int a[400005];
char ans[400005];

struct node {
    node *l, *r;
    int pval, sval, premn, sufmx;
    node() : l(0), r(0), pval(0), sval(0), premn(0), sufmx(0) {}
    void pull() { 
        pval = l->pval + r->pval;
        sval = l->sval + r->sval;
        premn = min(l->premn, l->pval + r->premn);
        sufmx = max(r->sufmx, r->sval + l->sufmx);
    }
} *root;

void Build(node *now, int l, int r) {
    if (l == r) {
        now->pval = 1;
        now->sval = -1;
        now->premn = 1;
        now->sufmx = -1;
        return;
    }
    Build(now->l = new node(), l, mid);
    Build(now->r = new node(), mid + 1, r);
    now->pull();
}

void Modify(node *now, int l, int r, int x, int v) {
    if (l == r) {
        now->pval = v;
        now->sval = v;
        now->premn = v;
        now->sufmx = v;
        return;
    }
    if (x <= mid) Modify(now->l, l, mid, x, v);
    else Modify(now->r, mid + 1, r, x, v);
    now->pull();
    // cerr << "modify " << l << " " << r << " after pull premn " << now->premn << " sufmx " << now->sufmx << endl;
}

int pos[400005];

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    n *= 2;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] ^= i;
    }

    Build(root = new node(), 1, n);

    auto Ok = [&] () -> bool {
        // cerr << "premn = " << root->premn << " sufmx = " << root->sufmx << endl;
        return root->premn >= 0 && root->sufmx <= 0;
    };

    for (int i = 1; i <= n; ++i) {
        if (ans[i]) continue;
        // cerr << "i = " << i << " try (" << endl;

        ans[i] = '(';
        Modify(root, 1, n, i, 1);
        int j = pos[a[i]] ^ i;
        Modify(root, 1, n, j, 1);
        ans[j] = '(';

        if (!Ok()) {
            // cerr << "i = " << i << " try )" << endl;

            ans[i] = ')';
            Modify(root, 1, n, i, -1);
            ans[j] = ')';
            Modify(root, 1, n, j, -1);
            if (!Ok()) NO();
        }
    }

    cout << string(ans + 1) << endl;
}

