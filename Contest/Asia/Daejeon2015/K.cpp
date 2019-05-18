#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000 + 5;
const long long inf = 1e15;
vector<int> t1[maxn], t2[maxn];
int lab1[maxn], lab2[maxn], r1, r2;
char s1[100000], s2[100000];
bool v[maxn][maxn];
int sz1[maxn], sz2[maxn];
long long dp[maxn][maxn], dp2[maxn][maxn];
long long w[maxn][maxn];

int build(char *s, vector<int> t[maxn], int lab[maxn]) {
    s[strlen(s) - 1] = 0; ++s;
    stack<int> pid;
    int now = 0;
    while (*s) {
        if (*s == '(') {
            ;
        } else if (*s == ')') {
            pid.pop();
        } else {
            lab[now] = *s - 'A';
            if (pid.size()) t[pid.top()].push_back(now);
            pid.push(now); 
            ++now;
        }
        ++s;
    }
    return now;

    /* for (int i = 0; i < maxn; ++i) t[i].clear();
    int n = strlen(s);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        if (s[i] != '(' && s[i] != ')') continue;
        if (s[i] == '(') st.push(i);
        else match[st.top()] = i, match[i] = st.top(), st.pop();
    }
    r1 = dfs(s, 0, n - 1, t); */
}

long long dfs(int x, int y) {
    if (v[x][y]) return dp[x][y];
    vector<vector<long long>> w(t1[x].size() + 1, vector<long long>(t2[y].size() + 1, 0));
    for (int i = 0; i < t1[x].size(); ++i) {
        for (int j = 0; j < t2[y].size(); ++j) {
        //    printf("i = %d j = %d\n", t1[x][i], t2[y][j]);
            w[i + 1][j + 1] = dfs(t1[x][i], t2[y][j]);
          //  printf("x = %d y = %d w[%d][%d] = %lld\n", x, y, i + 1, j + 1, w[i + 1][j + 1]);
        }
    }
    for (int i = 0; i <= t1[x].size(); ++i) {
        for (int j = 0; j <= t2[y].size(); ++j) {
            dp2[i][j] = inf;
        }
    }
   /* printf("dfs x = %d y = %d\n", x, y);
    for (int i = 1; i <= t1[x].size(); ++i) {
        for (int j = 1; j <= t2[y].size(); ++j) printf("w[%d][%d] = %lld\n", i, j, w[i][j]);
    } */

    dp2[0][0] = 0;
    for (int i = 0; i <= t1[x].size(); ++i) {
        for (int j = 0; j <= t2[y].size(); ++j) {
            if (i + 1 <= t1[x].size() && j + 1 <= t2[y].size()) {
                dp2[i + 1][j + 1] = min(dp2[i + 1][j + 1], dp2[i][j] + w[i + 1][j + 1]);
            }
            if (i + 1 <= t1[x].size()) {
                dp2[i + 1][j] = min(dp2[i + 1][j], dp2[i][j] + sz1[t1[x][i]]);
            }
            if (j + 1 <= t2[y].size()) {
                dp2[i][j + 1] = min(dp2[i][j + 1], dp2[i][j] + sz2[t2[y][j]]);
            }
            // printf("dp2[%d][%d] = %lld\n", i, j, dp2[i][j]);
        }
    }
    v[x][y] = true;
    dp[x][y] = dp2[t1[x].size()][t2[y].size()];
    if (lab1[x] != lab2[y]) ++dp[x][y];
//     printf("dp[%d][%d] = %lld\n", x, y, dp[x][y]);
    return dp[x][y];
}

void dfs1(int x, vector<int> t[maxn], int sz[maxn]) {
    sz[x] = 1;
    for (int u : t[x]) {
        dfs1(u, t, sz);
        sz[x] += sz[u];
    }
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < maxn; ++i) t1[i].clear(), t2[i].clear();
        memset(s1, 0, sizeof(s1));
        memset(s2, 0, sizeof(s2));
        scanf("%s", s1);
        scanf("%s", s2);
        int n1 = build(s1, t1, lab1);
        int n2 = build(s2, t2, lab2);
 /*       for(int i=0;i<n1;++i){
            cout<<"i: ";
            for(int j:t1[i])cout<<j<<" ";
            cout<<endl;
        }
        for(int i=0;i<n2;++i){
            cout<<"i: ";
            for(int j:t2[i])cout<<j<<" ";
            cout<<endl;
        } */
        dfs1(0, t1, sz1);
        dfs1(0, t2, sz2);
//        for (int i = 0; i < n1; ++i) printf("sz1[%d] = %d ", i, sz1[i]);
//        for (int i = 0; i < n2; ++i) printf("sz2[%d] = %d ", i, sz2[i]);
        memset(v, false, sizeof(v));
        printf("%lld\n", dfs(0, 0));
    }
}
