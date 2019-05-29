#include <bits/stdc++.h>
using namespace std;

struct node {
    node *l, *r, *pa;
    int dep, cnt;
    node() : l(0), r(0), pa(0), dep(0), cnt(0) {}
};

string simplify(string s) {
    string t;
    int idx = 0;
    int n = s.size();
    bool first = true;
    while (idx < n) {
        while (idx < n && (isalpha(s[idx]) || isdigit(s[idx]) || (first && s[idx] == '-'))) ++idx, first = false;
        t += 'a';
        while (idx < n && (s[idx] == '+' || s[idx] == '-' || s[idx] == '*' || s[idx] == '(' || s[idx] == ')')) t += s[idx], ++idx;
    }
    return t;
}

int op[300005];

node *dfs(int l, int r, string &s) {
    if (l > r) return 0;
    if (op[l]) return dfs(l + 1, r - 1, s);
    if (l == r) return new node();
    stack<char> ops;
    stack<node*> opr;

    while (l <= r) {
        if (s[l] == '+' || s[l] == '-') {
            if (ops.size()) {
                ops.pop();
                node *r = opr.top(); opr.pop();
                node *l = opr.top(); opr.pop();
                node *root = new node();
                root->l = l;
                root->r = r;
                opr.push(root);
            }
            ops.push(s[l]);
            ++l;
        } else if (s[l] == '(') {
            opr.push(dfs(l, op[l], s));
            l = op[l] + 1;
        } else if (s[l] == 'a') {
            opr.push(new node());
            ++l;
        } else if (s[l] == '*') {
            if (ops.size() && ops.top() != '*') {
                ops.pop();
                node *r = opr.top(); opr.pop();
                node *l = opr.top(); opr.pop();
                node *root = new node();
                root->l = l;
                root->r = r;
                opr.push(root);
            }
            ops.push(s[l]);
            ++l;
        } else if (s[l] == ')') {

        }
    }
    while (ops.size()) {
        ops.pop();
        node *r = opr.top(); opr.pop();
        node *l = opr.top(); opr.pop();
        node *root = new node();
        root->l = l;
        root->r = r;
        opr.push(root);
    }
    return opr.top();
}

void print(node *now) {
    if (!now) return;
    if (now->l) cout << "(", print(now->l), cout << ")";
    cout << ".";
    if (now->r) cout << "(", print(now->r), cout << ")";
}

priority_queue<pair<int, node*>, vector<pair<int, node*>>, less<pair<int, node*>>> pq;

void dfs(node *now) {
    if (now->l) {
        now->l->pa = now;
        now->l->dep = now->dep + 1;
        dfs(now->l);
    }
    if (now->r) {
        now->r->pa = now;
        now->r->dep = now->dep + 1;
        dfs(now->r);
    }
    if (!now->l) {
        if (now->pa) ++now->pa->cnt;
    }
    if (now->cnt == 2) {
        pq.emplace(now->dep, now);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int k; cin >> k;
    string s; cin >> s;
    s = simplify(s);
    int n = s.size();
    stack<int> left;
    s = " " + s;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '(') left.push(i);
        else if (s[i] == ')') {
            op[left.top()] = i;
            op[i] = left.top();
            left.pop();
        }
    }
    // cout << "s = " << s << endl;
    node *root = dfs(1, n, s);
    dfs(root);
    int step = 0;
    while (pq.size()) {
        ++step;
        vector<node*> calc;
        while (pq.size() && (int)calc.size() < k) {
            calc.push_back(pq.top().second);
            pq.pop();
        }
        for (node *now : calc) {
            now->l = now->r = 0;
            if (now->pa) {
                ++now->pa->cnt;
                if (now->pa->cnt == 2) pq.emplace(now->pa->dep, now->pa);
            }
        }
    }
    cout << step << endl;
}
