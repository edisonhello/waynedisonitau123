#include <bits/stdc++.h>
using namespace std;

struct node {
    node *pa;
    vector<int> val;
    vector<node*> ch;
    node() : pa(0) {}
    void insert(int x) {
        val.push_back(x);
        sort(val.begin(), val.end());
        ch.push_back(0);
    }
    void add(int x, node *l, node *r) {
        cerr << "A node with first val = " << val[0] << " receive add. This is a " << ch.size() << " node. x = " << x << endl;
        if (ch.size() == 2u) {
            if (x < val[0]) {
                cerr << ch[0] << " is being replaced" << endl;
                val.insert(val.begin(), x);
                ch.insert(ch.begin(), l);
                ch[1] = r;
            } else {
                cerr << ch[1] << " is being replaced" << endl;
                val.push_back(x);
                ch.back() = l;
                ch.push_back(r);
            }
        } else {
            cerr << "ch.size() = " << ch.size() << endl;
            assert(ch.size() == 3u);
            if (x < val[0]) {
                cerr << ch[0] << " is being replaced" << endl;
                val.insert(val.begin(), x);
                ch.insert(ch.begin(), l);
                ch[1] = r;
            } else if (x < val[1]) {
                cerr << ch[1] << " is being replaced" << endl;
                val.insert(val.begin() + 1, x);
                ch.insert(ch.begin() + 1, l);
                ch[2] = r;
            } else {
                cerr << ch[2] << " is being replaced" << endl;
                val.push_back(x);
                ch.back() = l;
                ch.push_back(r);
            }
        }
        cout << "New children is "; for (node *c : ch) cout << c << " "; cout << endl;
    }
};

node *root;

void insert(node *&now, int x) {
    cerr << "Insert " << x << ". now is a node with first val = " << now->val[0] << ". Address = " << now << ". ch size = " << now->ch.size() << " , val size = " << now->val.size() << endl;
    if (now->ch.size() == 4u) {
        if (!now->pa) {
            node *nl = new node();
            nl->val.push_back(now->val[0]);
            nl->ch.push_back(now->ch[0]);
            nl->ch.push_back(now->ch[1]);
            node *nr = new node();
            nr->val.push_back(now->val[2]);
            nr->ch.push_back(now->ch[2]);
            nr->ch.push_back(now->ch[3]);
            node *nroot = new node();
            nl->pa = nroot;
            nr->pa = nroot;
            nroot->val.push_back(now->val[1]);
            nroot->ch.push_back(nl);
            nroot->ch.push_back(nr);
            cerr << "now = " << now << " is deleted" << endl;
            delete now;
            now = nroot;
            root = nroot;
            cerr << "new root = " << now << " = " << nroot << endl;
            insert(now, x);
            return;
        } else {
            cerr << "Split 4 node, have parent" << endl;
            node *nl = new node();
            nl->val.push_back(now->val[0]);
            nl->ch.push_back(now->ch[0]);
            nl->ch.push_back(now->ch[1]);
            nl->pa = now->pa;
            node *nr = new node();
            nr->val.push_back(now->val[2]);
            nr->ch.push_back(now->ch[2]);
            nr->ch.push_back(now->ch[3]);
            nr->pa = now->pa;
            cerr << "nl = " << nl << " , nr = " << nr << endl;
            cerr << "Their pa = " << nl->pa << " = " << nr->pa << " = " << now->pa << endl;
            node *original = now;
            now->pa->add(now->val[1], nl, nr);
            delete original;
            insert(nr->pa, x);
            return;
        }
    } else if (now->ch[0] == 0) {
        cerr << "I'm leaf, insert" << endl;
        now->insert(x);
        return;
    } else if (now->ch.size() == 3u) {
        if (x < now->val[0]) insert(now->ch[0], x);
        else if (x < now->val[1]) insert(now->ch[1], x);
        else insert(now->ch[2], x);
    } else {
        if (x < now->val[0]) insert(now->ch[0], x);
        else insert(now->ch[1], x);
    }
}

void dfs(node *now) {
    if (!now) return;
    cerr << "dfs at now address " << now << " with first val = " << now->val[0] << endl;
    for (int i : now->val) cout << i << " "; cout << '\n';
    for (node *c : now->ch) dfs(c);
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
        cerr << "Print after root generated" << endl;
        dfs(root);
        cerr << "---------------" << endl;
        for (int i = 1; i < n; ++i) {
            cin >> x;
            cerr << "Inserting " << x << endl;
            insert(root, x);
            cerr << "Root = " << root << endl;
            cerr << "Print after " << x << " is inserted" << endl;
            dfs(root);
            cerr << "---------------" << endl;
        }
        dfs(root);
    }
}
