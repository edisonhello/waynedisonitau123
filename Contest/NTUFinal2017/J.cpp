#include <bits/stdc++.h>
using namespace std;

struct dinic {
    static const int inf = 1e9;
    static const int maxn = 300;
    struct edge {
        int to, cap, w, rev;
        edge(int a, int b, int c, int d):
            to(a), cap(b), w(c), rev(d) {}
    };
    vector<edge> g[maxn];
    int d[maxn], p[maxn], ed[maxn];
    bool inq[maxn];
    void add_edge(int a, int b, int c, int d) {
        // cout<<a<<" to "<<b<<" flow "<<c<<" cost "<<d<<endl;
        g[a].emplace_back(b, c, +d, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, -d, (int)g[a].size() - 1);
    }
    bool spfa(int s, int t, int &f, int &c) {
        for (int i = 0; i < maxn; ++i) {
            d[i] = inf;
            p[i] = ed[i] = -1;
            inq[i] = false;
        }
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int x = q.front(); q.pop();
            inq[x] = false;
            for (int i = 0; i < (int)g[x].size(); ++i) {
                edge &e = g[x][i];
                if (e.cap > 0 && d[e.to] > d[x] + e.w) {
                    d[e.to] = d[x] + e.w;
                    p[e.to] = x;
                    ed[e.to] = i;
                    if (!inq[e.to]) {
                        inq[e.to] = true;
                        q.push(e.to);
                    }
                }
            }
        }
        if (d[t] == inf) return false;
        int dlt = inf;
        for (int x = t; x != s; x = p[x]) dlt = min(dlt, g[p[x]][ed[x]].cap);
        for (int x = t; x != s; x = p[x]) {
            edge &e = g[p[x]][ed[x]];
            e.cap -= dlt;
            g[e.to][e.rev].cap += dlt;
        }
        f += dlt;
        c += d[t] * dlt;
        return true;
    }
    pair<int, int> operator()(int s, int t) {
        int f = 0, c = 0;
        while (spfa(s, t, f, c));
        return make_pair(f, c);
    }
} fl;

int cnt[222];
int cc[222][222];

int main() {
    string s1,t1,s2,t2; cin>>s1>>t1>>s2>>t2;
    for(char c:s1)++cnt[c];
    for(int i='a';i<='z';++i){
        fl.add_edge(0,i,cnt[i],0);
    }
    memset(cnt,0,sizeof(cnt));
    for(char c:t1)++cnt[c];
    for(int i='a';i<='z';++i){
        fl.add_edge(i,1,cnt[i],0);
    }
    for(int i=0;i<int(s2.size());++i){
        ++cc[t2[i]][s2[i]];
        // cout<<t2[i]<<" to "<<s2[i]<<" add"<<endl;
    }
    for(int i='a';i<='z';++i)for(int j='a';j<='z';++j){
        if(!cc[i][j])continue;
        fl.add_edge(i,j,cc[i][j],1);
        // cout<<char(i)<<" to "<<char(j)<<" flow: "<<cc[i][j]<<endl;
    }
    auto r=fl(0,1);
    // cout<<r.first<<" "<<r.second<<endl;
    if(r.first!=int(s1.size()))cout<<-1<<endl;
    else cout<<r.second<<endl;
}
