#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> g[maxn];
int color[maxn], deg[maxn];
bool del[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        g[i].push_back(x - 1);
        deg[x - 1]++;
    }
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        g[i + n].push_back(x - 1);
        deg[x - 1]++;
    }
    for (int i = 0; i < n; ++i) color[i] = 0;
    for (int i = 0; i < n; ++i) color[i + n] = 1;
    queue<int> q;
    for (int i = n; i < n + n; ++i) {
        if (deg[i] == 0) {
            color[i] = 0;
            q.push(i);
        }
    }
    while (q.size()) {
        int x = q.front(); q.pop();
        vector<int> cand;
        for (const int &u : g[x]) {
            color[u] = 1;
            if (!del[u]) {
                del[u] = true;
                cand.push_back(u);
            }
        }
        for (int i = 0; i < (int)cand.size(); ++i) {
            int x = cand[i];
            for (const int &u : g[x]) {
                --deg[u];
                if (color[u] == 1 && deg[u] == 0) {
                    color[u] = 0;
                    q.push(u);
                }
            }
        }
    }
    for (int i = 0; i < n + n; ++i) if (color[i] == 0) printf("%d ", i + 1);
    puts("");
    return 0;
}
