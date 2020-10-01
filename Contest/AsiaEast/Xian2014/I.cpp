#include <bits/stdc++.h>
using namespace std;

struct node {
    node *ch[2];
    bool end;
    node() {
        ch[0] = ch[1] = 0;
        end = 0;
    }
};

void build(node *now, uint32_t ip, int l, int b) {
    if (!l) {
        now->end = 1;
        return;
    }
    node *&go = now->ch[!!(ip & (1u << b))];
    if (!go) go = new node();

    build(go, ip, l - 1, b - 1);
}

vector<pair<uint32_t, int>> ans;

void dfs(node *now, uint32_t pre, int b, int c) {
    if (b == -1) {
        return;
    }
    if (now->end) {
        return;
    }
    if (now->ch[0] == 0 && now->ch[1] == 0) {
        ans.emplace_back(pre, c);
        return;
    }
    for (uint32_t i = 0; i < 2; ++i) {
        uint32_t nw = pre | (i << b);
        if (now->ch[i]) {
            dfs(now->ch[i], nw, b - 1, c + 1);
        } else {
            ans.emplace_back(nw, c + 1);
        }
    }
}

int main() {
    int t, T = 0; scanf("%d", &t); while (t--) {
        ++T;

        node *root = new node();
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            uint32_t a, b, c, d, l; 
            scanf("%u.%u.%u.%u/%d", &a, &b, &c, &d, &l);
            uint32_t ip = (a << 24) | (b << 16) | (c << 8) | d;
            build(root, ip, l, 31);
        }

        ans.clear();
        dfs(root, 0, 31, 0);

        printf("Case #%d: \n", T);
        printf("%d\n", (int)ans.size());
        for (int i = 0; i < (int)ans.size(); ++i) {
            uint32_t ip = ans[i].first;
            printf("%u.%u.%u.%u/%d\n", 
                    (ip >> 24) & 255,
                    (ip >> 16) & 255,
                    (ip >> 8) & 255,
                    ip & 255,
                    ans[i].second);
        }

    }
}

