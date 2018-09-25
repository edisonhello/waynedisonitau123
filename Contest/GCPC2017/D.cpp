#include <bits/stdc++.h>
using namespace std;

const int maxn = 200 + 5;
vector<int> g[maxn], r[maxn];
bool v[maxn];

map<string, int> rev;

int rev_t(string s) {
    if (rev.find(s) != rev.end()) return rev[s];
    int t = rev.size();
    rev[s] = t;
    return t;
}

void gdfs(int x) {
    v[x] = true;
    for (int u : g[x]) {
        if (!v[u]) gdfs(u);
    }
}
void rdfs(int x) {
    v[x] = true;
    for (int u : r[x]) {
        if (!v[u]) rdfs(u);
    }
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string a, b, c, d, e; 
        cin >> a >> b >> c >> d >> e;
        int x = rev_t(a);
        int y = rev_t(e);
        g[x].push_back(y);
        r[y].push_back(x);
    }
    while (m--) {
        string a, b, c, d, e; 
        cin >> a >> b >> c >> d >> e;
        int x = rev_t(a);
        int y = rev_t(e);
        memset(v, false, sizeof(v));
        gdfs(x);
        if (v[y]) {
            cout << "Fact" << endl;
            continue;
        }
        memset(v, false, sizeof(v));
        rdfs(x);
        if (v[y]) {
            cout << "Alternative Fact" << endl;
            continue;
        }
        cout << "Pants on Fire" << endl;
    }
}
