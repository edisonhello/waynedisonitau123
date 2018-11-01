#include<bits/stdc++.h>
using namespace std;

struct item{
    char i,st,ed;
};

vector<int> g[20], r[20], ga[20];
int a[20], b[20], c[20], scc[20], sz;
long long dp[1 << 20];
int reach[20];
bool vs[20];
vector<int> tp;

void add_edge(int x, int y) {
    // printf("add_edge x = %d y = %d\n", x, y);
    g[x].push_back(y);
    r[y].push_back(x);
}

void dfs(int x) {
    vs[x] = true;
    for (int u : g[x]) {
        if (vs[u]) continue;
        dfs(u);
    }
    tp.push_back(x);
}

void rdfs(int x) {
    scc[x] = sz;
    for (int u : r[x]) {
        if (~scc[u]) continue;
        rdfs(u);
    }
}

void check(int x, int s) {
    reach[s] ^= (1 << x);
    vs[x] = true;
    for (int u : ga[x]) {
        if (!vs[u]) check(u, s);
    }
}

int main(){
#ifdef ONLINE_JUDGE
    freopen("fygon20.in", "r", stdin);
    freopen("fygon20.out", "w", stdout);
#endif
    int n; cin>>n;
    string s; getline(cin,s);
    vector<item> v;
    --n;
    while(n--){
        getline(cin,s);
        stringstream ss(s);
        ss>>s>>s;
        item ii;
        ii.i=s[0];
        ss>>s>>s;
        ii.st=s[s.size()-2];
        ss>>s;
        ii.ed=s[0];
        v.push_back(ii);
    }
    vector<char> ds;
    for (int i = 0; i < (int)v.size(); ++i) {
        if (v[i].i != '1' && v[i].i != 'n') ds.push_back(v[i].i);
        if (v[i].st != '1' && v[i].st != 'n') ds.push_back(v[i].st);
        if (v[i].ed != '1' && v[i].ed != 'n') ds.push_back(v[i].ed);
    }
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < (int)v.size(); ++i) {
        a[i] = v[i].i == '1' || v[i].i == 'n' ? -1 : lower_bound(ds.begin(), ds.end(), v[i].i) - ds.begin();
        b[i] = v[i].st == '1' || v[i].st == 'n' ? -1 : lower_bound(ds.begin(), ds.end(), v[i].st) - ds.begin();
        c[i] = v[i].ed == '1' || v[i].ed == 'n' ? -1 : lower_bound(ds.begin(), ds.end(), v[i].ed) - ds.begin();
    }
    for (int i = 0; i < (int)v.size(); ++i) {
        if (~a[i] && ~b[i]) add_edge(b[i], a[i]);
        if (~a[i] && ~c[i]) add_edge(a[i], c[i]);
    }
    for (int i = 0; i < (int)ds.size(); ++i) {
        int x = i;
        if (vs[x]) continue;
        dfs(x);
    }
    memset(scc, -1, sizeof(scc));
    for (int i = (int)tp.size() - 1; i >= 0; --i) {
        int x = tp[i];
        if (scc[x] == -1) rdfs(x), ++sz;
    } 
    for (int i = 0; i < (int)ds.size(); ++i) {
        int x = i;
        for (int u : g[x]) {
            if (scc[x] == scc[u]) continue;
            ga[scc[x]].push_back(scc[u]);
        }
    }
    for (int i = 0; i < sz; ++i) {
        sort(ga[i].begin(), ga[i].end());
        ga[i].resize(unique(ga[i].begin(), ga[i].end()) - ga[i].begin());
    }
    for (int i = 0; i < sz; ++i) {
        memset(vs, false, sizeof(vs));
        check(i, i);
        // printf("reach[%d] = %d\n", i, reach[i]);
    }
    dp[0] = 1;
    for (int i = 0; i < (1 << sz) - 1; ++i) {
        for (int j = 0; j < sz; ++j) {
            if (i >> j & 1) continue;
            int mask = reach[j];
            if ((mask & i) == 0) dp[i ^ (1 << j)] += dp[i];
        }
        // printf("dp[%d] = %lld\n", i, dp[i]);
    }
    // printf("dp[%d] = %lld\n", (1 << sz) - 1, dp[(1 << sz) - 1]);
    long long dd = 1;
    for (int i = 1; i <= sz; ++i) dd *= i;
    // printf("dd = %lld\n", dd);
    long long g = __gcd(dd, dp[(1 << sz) - 1]);
    dd /= g, dp[(1 << sz) - 1] /= g;
    printf("%d %lld/%lld\n", sz, dp[(1 << sz) - 1], dd);
}
