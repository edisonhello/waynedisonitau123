#include <bits/stdc++.h>
using namespace std;

int pa[100005];
int co[100005];
vector<int> g[100005];
int nn;

void ae(int u, int v) {
    if (!u) return;
    pa[v] = u;
    g[u].push_back(v);
}

void dfs(int now) {
    if (g[now].empty()) {
        co[now] = 1;
    }
    for (int i : g[now]) {
        dfs(i);
        co[now] += co[i];
    }
}

int main() {
    int n; cin >> n;
    int root = 0;
    if (n == 1) {
        cout << "2" << endl;
        cout << "1" << endl;
        cout << "1 2" << endl;
        exit(0);
    }
    while (n) {
        if (n == 1) {
            int a = ++nn;
            ae(root, a);
            break;
        } else if (n == 2) {
            int a = ++nn;
            int b = ++nn;
            int c = ++nn;
            ae(root, a);
            ae(a, b);
            ae(a, c);
            break;
        } else if (n % 2 == 0) {
            int a = ++nn;
            int b = ++nn;
            int c = ++nn;
            int d = ++nn;
            int e = ++nn;
            ae(root, a);
            ae(a, b);
            ae(b, c);
            ae(c, d);
            ae(c, e);
            root = b;
            n = (n - 2) / 2;
        } else {
            int a = ++nn;
            int b = ++nn;
            int c = ++nn;
            int d = ++nn;
            ae(root, a);
            ae(a, b);
            ae(b, c);
            ae(b, d);
            root = a;
            n = (n - 1) / 2;
        }
    }

    dfs(1);

    cout << nn << endl;
    for (int i = 2; i <= nn; ++i) cout << pa[i] << " \n"[i == nn];
    for (int i = 1; i <= nn; ++i) cout << co[i] << " \n"[i == nn];
}
