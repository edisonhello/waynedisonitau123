#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct node {
    node *l, *r;
    int sz, key, tag, val, mx;
    node() : l(0), r(0), sz(1), key(-1), tag(0), val(0), mx(0) {}

    void addtag(int t) {
        tag += t;
        val += t;
        mx += t;
    }
    void push() {
        if (tag) {
            if (l) l->addtag(tag);
            if (r) r->addtag(tag);
            tag = 0;
        }
    }
    void pull() {
        mx = max(max(l ? l->mx : 0, r ? r->mx : 0), val);
    }
    int lz() { return l ? l->sz : 0; }
    int rz() { return r ? r->sz : 0; }
    void pullsz() {
        sz = lz() + rz() + 1;
    }
};

void Meow(node *&now) {
    if (!now) return;
    now->push();
    if (now->l) now->l->push();
    if (now->r) now->r->push();
    now->pullsz();
    now->pull();
    if (now->lz() * 2 > now->rz() * 3) {
        node *tmp = now->l;
        now->l = tmp->r;
        tmp->r = now;
        now = tmp;
        now->r->pullsz();
        now->r->pull();
        now->pullsz();
        now->pull();
    } else if (now->rz() * 2 > now->lz() * 3) {
        node *tmp = now->r;
        now->r = tmp->l;
        tmp->l = now;
        now = tmp;
        now->l->pullsz();
        now->l->pull();
        now->pullsz();
        now->pull();
    }
}

void ModifyLargerEqual(node *now, int key, int val) {
    if (!now) return;
    now->push();
    if (now->key >= key) {
        now->val += val;
        if (now->r) now->r->addtag(val);
        ModifyLargerEqual(now->l, key, val);
        now->pull();
    } else {
        ModifyLargerEqual(now->r, key, val);
        now->pull();
    }
}

int LessMax(node *now, int key) {
    if (!now) return 0;
    now->push();
    if (now->key < key) {
        return max(max(now->l ? now->l->mx : 0, now->val), LessMax(now->r, key));
    } else {
        return LessMax(now->l, key);
    }
}

void InsertOrMax(node *&now, int key, int val) {
    if (!now) {
        now = new node();
        now->key = key;
        now->val = now->mx = val;
        return;
    }
    now->push();
    if (now->key == key) {
        now->val = max(now->val, val);
        now->pull();
        return;
    } else if (now->key > key) {
        InsertOrMax(now->l, key, val);
        now->pull();
        Meow(now);
    } else {
        InsertOrMax(now->r, key, val);
        now->pull();
        Meow(now);
    }
}

void PrintTree(node *now) {
    if (!now) return;
    // now->push();
    if (now->l) cerr << "[", PrintTree(now->l), cerr << "]";
    cerr << "(key = " << now->key << " val = " << now->val << " mx = " << now->mx << " tag = " << now->tag << ")";
    if (now->r) cerr << "[", PrintTree(now->r), cerr << "]";
}

vector<int> g[200005];
int val[200005];

node *Dfs(int now) {
    // cerr << "Dfs = " << now << endl;
    node *ret = 0;

    // auto Add = [&] (int key, int val, int diff) {
    //     int mx = LessMax(ret, key);
    //     ModifyLargerEqual(ret, key, diff);
    //     InsertOrMax(ret, key, val + mx);
    // };

    for (int i : g[now]) {
        // cerr << "  Dfs " << now << " go child " << i << endl;
        node *tmp = Dfs(i);
        // cerr << "  Dfs " << now << " go child " << i << " back" << endl;

        if (!ret) ret = tmp;
        else {
            if (ret->sz < tmp->sz) swap(ret, tmp);
            vector<pair<int, int>> cand;
            auto Dfs2 = [&] (auto self, node *now) -> void {
                if (!now) return;
                now->push();
                self(self, now->l);
                // Add(now->key, now->val, now->val - prev);
                // prev = now->val;
                cand.emplace_back(now->key, now->val);
                // cerr << "  cand " << now->key << ' ' << now->val << endl;
                self(self, now->r);
            };
            Dfs2(Dfs2, tmp);

            vector<pair<int, int>> inserts;
            for (auto &p : cand) {
                int mx = LessMax(ret, p.first);
                inserts.emplace_back(p.first, p.second + mx);
                // cerr << "  inserts " << p.first << ", " << p.second << " + " << mx << endl;
            }

            int prev = 0;
            for (auto &p : cand) {
                if (prev > p.second) continue;
                // cerr << "  modify larger equal " << p.first << ' ' << p.second - prev << endl;
                ModifyLargerEqual(ret, p.first, p.second - prev);
                prev = p.second;
            }

            // cerr << "  Dfs " << now << " go child " << i << " back, After modify " << endl << "     ";
            // PrintTree(ret);
            // cerr << endl;

            for (auto &p : inserts) InsertOrMax(ret, p.first, p.second);
        }

        // cerr << "  Dfs " << now << " go child " << i << " back, print tree " << endl << "     ";
        // PrintTree(ret);
        // cerr << endl;
    }

    if (!ret) {
        ret = new node();
        ret->key = val[now];
        ret->val = ret->mx = 1;
    } else {
        int mx = LessMax(ret, val[now]);
        InsertOrMax(ret, val[now], 1 + mx);
    }

    // cerr << "  Dfs " << now << " finally print tree " << endl << "  ";
    // PrintTree(ret);
    // cerr << endl;

    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int v, p; cin >> v >> p;
        if (p) g[p].push_back(i);
        val[i] = v;
    }

    node *root = Dfs(1);
    cout << root->mx << endl;
}

