#include <bits/stdc++.h>
using namespace std;

struct node {
    vector<node*> ch;
    vector<int> val;
    void add(int x, node *l, node *r) {
        if (ch.size() == 2u) {
            if (x < val[0]) {
                val.insert(val.begin(), x);
                ch.insert(ch.begin(), l);
                ch[1] = r;
            } else {
                val.push_back(x);
                ch.back() = l;
                ch.push_back(r);
            }
        } else {
            assert(ch.size() == 3u);
            if (x < val[0]) {
                val.insert(val.begin(), x);
                ch.insert(ch.begin(), l);
                ch[1] = r;
            } else if (x < val[1]) {
                val.insert(val.begin() + 1, x);
                ch.insert(ch.begin() + 1, l);
                ch[2] = r;
            } else {
                val.push_back(x);
                ch.back() = l;
                ch.push_back(r);
            }
        }
    }
} *root;

void dfs(node *now) {
    if (!now) return;
    for (int i : now->val) cout << i << " "; cout << '\n';
    for (node *c : now->ch) dfs(c);
}

bool insert(node *now, int x, node *pa) {
    bool first = true;
    while (true) {
        // cerr << "While loop start for now = " << now << " and child = "; for (int i : now->val) cout << i << " "; cout << " , x = " << x << endl;
        if (now->ch.size() == 4u && first) {
            if (pa) {
                node *nl = new node(), *nr = new node();
                nl->val.push_back(now->val[0]);
                nl->ch.push_back(now->ch[0]);
                nl->ch.push_back(now->ch[1]);
                nr->val.push_back(now->val[2]);
                nr->ch.push_back(now->ch[2]);
                nr->ch.push_back(now->ch[3]);
                pa->add(now->val[1], nl, nr);
                return false;
            } else {
                node *nl = new node(), *nr = new node();
                nl->val.push_back(now->val[0]);
                nl->ch.push_back(now->ch[0]);
                nl->ch.push_back(now->ch[1]);
                nr->val.push_back(now->val[2]);
                nr->ch.push_back(now->ch[2]);
                nr->ch.push_back(now->ch[3]);
                node *nroot = new node();
                nroot->val.push_back(now->val[1]);
                nroot->ch.push_back(nl);
                nroot->ch.push_back(nr);
                now = root = nroot;
            }
        } else if (now->ch[0] == 0) {
            now->ch.push_back(0);
            now->val.push_back(x);
            sort(now->val.begin(), now->val.end());
            return true;
        } else if (now->ch.size() == 2u) {
            if (x < now->val[0]) {
                if (insert(now->ch[0], x, now)) return true;
            } else {
                if (insert(now->ch[1], x, now)) return true;
            }
        } else if (now->ch.size() == 3u) {
            if (x < now->val[0]) {
                if (insert(now->ch[0], x, now)) return true;
            } else if (x < now->val[1]) {
                if (insert(now->ch[1], x, now)) return true;
            } else {
                if (insert(now->ch[2], x, now)) return true;
            }
        } else if (now->ch.size() == 4u) {
            if (x < now->val[0]) {
                if (insert(now->ch[0], x, now)) return true;
            } else if (x < now->val[1]) {
                if (insert(now->ch[1], x, now)) return true;
            } else if (x < now->val[2]) {
                if (insert(now->ch[2], x, now)) return true;
            } else {
                if (insert(now->ch[3], x, now)) return true;
            }
        }
        first = false;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ":\n";
        int n; cin >> n; 
        int x; cin >> x;
        root = new node();
        root->val.push_back(x);
        root->ch.resize(2, 0);
        // cerr << "Print after root generated" << endl;
        // dfs(root);
        // cerr << "---------------" << endl;
        for (int i = 1; i < n; ++i) {
            cin >> x;
            // cerr << "Inserting " << x << endl;
            insert(root, x, 0);
            // cerr << "Print after " << x << " is inserted" << endl;
            // dfs(root);
            // cerr << "---------------" << endl;
        }
        dfs(root);
    }
}
