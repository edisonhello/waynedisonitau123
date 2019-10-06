#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e6 + 5;
int id[maxn];
 
struct Graph {
    vector<vector<int>> ed;
 
    Graph() = default;
    Graph(size_t n) { ed.resize(n); }
 
    int F, L;
 
    size_t size() const { return ed.size(); }
 
    void AddEdge(int u, int v) {
        while (ed.size() <= u) ed.emplace_back();
        while (ed.size() <= v) ed.emplace_back();
        ed[u].push_back(v);
        ed[v].push_back(u);
    }
 
    vector<pair<int, int>> Edge() const {
        vector<pair<int, int>> res;
        for (size_t i = 0; i < ed.size(); ++i) {
            for (size_t j = 0; j < ed[i].size(); ++j) {
                if (i < ed[i][j])
                    res.emplace_back(i, ed[i][j]);
            }
        }
        return res;
    }
 
    void Print() const {
        vector<pair<int, int>> edge = Edge();
        cout << "F = " << F << " L = " << L << endl;
        for (auto e : edge) cout << e.first + 1 << ' ' << e.second + 1 << endl;
    }
 
    void Renumber() {
        vector<int> id(ed.size());
        id[F] = 0;
        id[L] = ed.size() - 1;
        for (int i = 0, j = 1; i < (int)ed.size(); ++i) {
            if (i != F && i != L)
                id[i] = j++;
        }
 
        vector<pair<int, int>> edge = Edge();
        for (int i = 0; i < (int)ed.size(); ++i) ed.clear();
 
        for (auto e : edge) AddEdge(id[e.first], id[e.second]);
    }
};
 
Graph T(const vector<Graph> &v) {
    if (v.empty()) {
        cout << "T: Empty list" << endl;
        assert(false);
    }
    Graph res = v[0];
    res.F = v[0].F;
    int F = res.F;
    res.L = v[0].L;
    int sz = v[0].size();
    for (int i = 1; i < (int)v.size(); ++i) {
        vector<int> jid(v[i].size());
        for (int j = 0; j < (int)v[i].size(); ++j) {
            if (j == v[i].F) jid[j] = F;
            else jid[j] = sz++;
        }
        vector<pair<int, int>> e = v[i].Edge();
        for (auto x : e) res.AddEdge(jid[x.first], jid[x.second]);
    }
    return res;
}
 
Graph C(const vector<Graph> &v) {
    // cout << "CCC" << endl;
    // for (Graph g : v) g.Print();
    // cout << "done" << endl;
    if (v.empty()) {
        cout << "C: Empty list" << endl;
        assert(false);
    }
    Graph res = v[0];
    res.F = v[0].F;
    int last = v[0].L;
    int sz = v[0].size();
    for (int i = 1; i < (int)v.size(); ++i) {
        vector<int> jid(v[i].size());
        for (int j = 0; j < (int)v[i].size(); ++j) {
            if (j == v[i].F) jid[j] = last;
            else jid[j] = sz++;
        }
        vector<pair<int, int>> e = v[i].Edge();
        for (auto x : e) res.AddEdge(jid[x.first], jid[x.second]);
        last = jid[v[i].L];
    }
    res.L = last;
    return res;
}
 
Graph Loop(const vector<Graph> &v) {
    if (v.empty()) {
        cout << "C: Empty list" << endl;
        assert(false);
    }
    Graph res = v[0];
    int last = v[0].L;
    int fi = v[0].F;
    int sz = v[0].size();
    for (int i = 1; i < (int)v.size(); ++i) {
        vector<int> jid(v[i].size());
        for (int j = 0; j < (int)v[i].size(); ++j) {
            if (j == v[i].F) jid[j] = last;
            else if (i == (int)v.size() - 1 && j == v[i].L) jid[j] = fi;
            else jid[j] = sz++;
        }
        vector<pair<int, int>> e = v[i].Edge();
        for (auto x : e) res.AddEdge(jid[x.first], jid[x.second]);
        last = jid[v[i].L];
    }
    return res;
}
 
Graph CreateC() {
    Graph res(2);
    res.AddEdge(0, 1);
    res.F = 0;
    res.L = 1;
    return res;
}
 
int ParseNumber(const string &s) {
    // cout << "ParseNumber" << endl;
    // cout << "s = " << s << endl;
    int res = 0;
    for (int i = 0; i < (int)s.size(); ++i) 
        res = res * 10 + (s[i] - '0');
    // cout << "res = " << res << endl;
    return res;
}
 
vector<Graph> ParseList(const string &s);
Graph ParseGraph(const string &s);
 
string ToString(int x) {
    string res = "";
    while (x > 0) {
        res += (char)(x % 10 + '0');
        x /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}
 
string Replace(const string &s, char v, int x) {
    string sx = ToString(x);
    string res = "";
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == v) res += sx;
        else res += s[i];
    }
    return res;
}
 
void Hold() {
    return;
    int p; cin >> p;
}
 
vector<Graph> ParseList(const string &s) {
    // if (s == "") { return {CreateC();} }
 
    // cout << "ParseList: " << s << endl;
 
    assert(s.size() > 0);
    if (isdigit(s[0])) {
        int i = 0;
        while (i < (int)s.size() && isdigit(s[i])) ++i;
        int k = ParseNumber(s.substr(0, i));
        // cout << "k = " << k << endl;
        if (i < (int)s.size()) {
            assert(s[i] == ',');
            Graph g = ParseGraph(s.substr(i + 1));
            vector<Graph> res;
            while (k--) res.push_back(g);
            return res;
        } else {
            vector<Graph> res;
            while (k--) res.push_back(CreateC());
            return res;
        }
    }
 
    if (s[0] == 'r') {
        assert(s.size() >= 6 && s.substr(0, 6) == "range(");
        char var = s[6];
        assert(s[7] == ',');
        int i = 8;
        while (i < (int)s.size() && s[i] != ',') ++i;
        assert(i < (int)s.size() && s[i] == ',');
 
        int a = ParseNumber(s.substr(8, i - 8));
        int j = i;
        while (j < (int)s.size() && s[j] != ')') ++j;
        int b = ParseNumber(s.substr(i + 1, j - (i + 1)));
 
        if (a > b) swap(a, b);
        // cout << "a = " << a << " b = " << b << endl;
        // Hold();
 
        ++j;
        vector<Graph> res;
        if (j < (int)s.size()) {
            assert(s[j] == ',');
            string r = s.substr(j + 1);
            for (int i = a; i <= b; ++i) {
                string rr = Replace(r, var, i);
                res.push_back(ParseGraph(rr)); 
            }
        } else {
            for (int i = a; i <= b; ++i) res.push_back(CreateC());
        }
        return res;
    }
 
    int p = 0;
 
    vector<Graph> res;
    int last = 0;
 
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            p++;
        } 
        if (s[i] == ')') {
            p--;
        }
 
        if (s[i] == ',' && p == 0) {
            string t = s.substr(last, i - last);
            res.push_back(ParseGraph(t));
            last = i + 1;
        }
    }
    string t = s.substr(last);
    res.push_back(ParseGraph(t));
    return res;
}
 
Graph ParseGraph(const string &s) {
    // cout << "ParseGraph: " << s << endl;
    // cout << "s.size() = " << s.size() << endl;
    if (s.size() == 0) return CreateC();
    if (s == "c") return CreateC(); 
    if (s[0] == 'c') {
        assert(s.back() == ')');
        assert(s[1] == '(');
        string t = s.substr(2, s.size() - 3);
        vector<Graph> v = ParseList(t);
        return C(v);
    }
    if (s[0] == 't') {
        assert(s.back() == ')');
        assert(s[1] == '(');
        string t = s.substr(2, s.size() - 3);
        vector<Graph> v = ParseList(t);
        return T(v);
    }
    if (s[0] == 'l') {
        assert(s.size() >= 4 && s.substr(0, 4) == "loop");
        assert(s.back() == ')');
        string t = s.substr(5, s.size() - 6);
        vector<Graph> v = ParseList(t);
        return Loop(v);
    }
    assert(false);
}
 
set<int> G[50005];
set<pair<int, pair<int, int>>> cG[50005];
int low[50005], dfn[50005], nt;
stack<int> stk;
int bel[50005], cc, startat[50005];
vector<int> mem[50005];
vector<int> route[50005];
bitset<50005> walked;
// stack<pair<int, int>> stk;
// set<pair<int, int>> loop_edge
 
void dfs(int now, int pa) {
    low[now] = dfn[now] = ++nt;
    stk.push(now);
    for (int i : G[now]) {
        if (i == pa) continue;
        if (dfn[i]) {
            low[now] = min(low[now], dfn[i]);
        } else {
            dfs(i, now);
            low[now] = min(low[now], low[i]);
        }
    }
    if (low[now] == dfn[now]) {
        ++cc;
        do {
            bel[stk.top()] = cc;
            mem[cc].push_back(stk.top());
            stk.pop();
        } while (mem[cc].back() != now);
        startat[cc] = now;
    }
}
// void dfs(int now) {
//     low[now] = dfn[now] = ++nt;
//     for (int i : G[now]) {
//         if (dfn[i]) {
//             low[now] = min(low[now], dfn[i]);
//         } else {
//             stk.emplace(minmax(now, i));
//             dfs(i);
//             low[now] = min(low[now], low[i]);
//             vector<pair<int, int>> add;
//             if (low[i] == dfn[now]) {
//                 do {
//                     add.push_back(stk.top());
//                     stk.pop(); 
//                 } while (add.back() != minmax(now, i));
//             }
//             if (add.size() > 1u) {
//                 for (auto &p : add) loop_edge.insert(p);
//             }
//         }
//     }
// }
 
// int djs[50005], deg[50005];
 
// int F(int x) { return djs[x] == x ? x : djs[x] = F(djs[x]); }
// void U(int x, int y) { djs[F(x)] = F(y); }
 
vector<vector<int>> ans;
 
// void dfs(int now) {
//     for (int i : G[now]) {
//         G[now].erase(i);
//         G[i].erase(now);
//         ans.back().push_back(i);
//         dfs(i);
//         break;
//     }
// }
 
bitset<50005> vis;
set<pair<int, int>> sss;
void FindLoop(int ccn, int now) {
    for (int i : G[now]) if (bel[i] == ccn && !sss.count(minmax(i, now))) {
        sss.insert(minmax(i, now));
        FindLoop(ccn, i);
    }
    route[ccn].push_back(now);
}
 
void dfs2(int now) {
    // cerr << "dfs2 " << cnow << endl;
    ans.back().push_back(now);
    if (!walked[bel[now]]) {
        int start = 0;
        while (route[bel[now]][start] != now) ++start;
        for (int i = start; i < (int)route[bel[now]].size(); ++i) ans.back().push_back(route[bel[now]][i]);
        for (int i = 0; i < start; ++i) ans.back().push_back(route[bel[now]][i]);
        walked[bel[now]] = 1;
    }
    ans.back().push_back(now);
    if (G[now].empty()) return;
    assert(G[now].size() > 0);
    int i = *G[now].begin();
    G[now].erase(i);
    G[i].erase(now);
    dfs2(i);
    /* for (auto &i : G[now]) {
        G[now].erase(i);
        G[i].erase(now);
        dfs2(i);
        break;
    } */
}
 
int main() {
    freopen("cactus.in", "r", stdin);
    freopen("cactus.out", "w", stdout);
    string s; cin >> s;
    Graph g = ParseGraph(s);
 
    g.Renumber();
    // g.Print();
    vector<pair<int, int>> edge = g.Edge();
    int n = g.size();
    for (auto &e : edge) ++e.first, ++e.second;
    for (auto &e : edge) G[e.first].insert(e.second), G[e.second].insert(e.first);
 
    dfs(1, 0);
    /* for (int i = 1; i <= cc; ++i) {
        cout << "mem " << i << " : ";
        for (int j : mem[i]) cout << j << ' ';
        cout << endl;
    } */
    for (int i = 1; i <= cc; ++i) sss.clear(), route[i].push_back(startat[i]), FindLoop(i, startat[i]), route[i].resize(unique(route[i].begin(), route[i].end()) - route[i].begin());
    /* for (int i = 1; i <= cc; ++i) {
        cout << "route " << i << " : ";
        for (int j : route[i]) cout << j << ' ';
        cout << endl;
    } */
    for (int i = 1; i <= cc; ++i) for (int j = 1; j < (int)route[i].size(); ++j) {
        G[route[i][j - 1]].erase(route[i][j]);
        G[route[i][j]].erase(route[i][j - 1]);
    }
 
    for (int i = 1; i <= n; ++i) for (int j : G[i]) if (bel[i] != bel[j]) cG[bel[i]].insert(make_pair(bel[j], make_pair(i, j)));
    
    queue<int> is_leaf;
    while (true) {
        if (is_leaf.empty()) {
            for (int i = 1; i <= n; ++i) if (G[i].size() == 1u) is_leaf.push(i);
        }
        if (is_leaf.empty()) break;
        int now = is_leaf.front(); is_leaf.pop();
        if (G[now].size() != 1u) continue;
        ans.push_back(vector<int>());
        dfs2(now);
    }
    if (cc == 1) ans.push_back(vector<int>()), dfs2(1);
    // while (true) {
    //     bool walk = false;
    //     for (int i = 1; i <= n; ++i) {
    //         if (G[i].size()) ans.push_back(vector<int>(1, i)), dfs(i), walk = true;
    //     }
    //     if (!walk) break;
    // }
 
    cout << n << " " << ans.size() << endl;
    for (vector<int> &v : ans) {
        v.resize(unique(v.begin(), v.end()) - v.begin());
        cout << v.size();
        for (int i : v) cout << " " << i;
        cout << endl;
    }
 
    // for (int i = 1; i <= n; ++i) djs[i] = i;
    // for (auto &e : edge) if (!loop_edge.count(minmax(e.first, e.second))) U(e.first, e.second);
 
    // set<int> trees;
    // for (int i = 1; i <= n; ++i) trees.insert(F(i));
    // for (auto &e : edge) if (!loop_edge.count(minmax(e.first, e.second))) ++deg[e.first], ++deg[e.second];
 
    // int ans = trees.size();
    // for (int i = 1; i <= n; ++i) {
    //     ans += (deg[i] - 1) / 2;
    // }
    
}
