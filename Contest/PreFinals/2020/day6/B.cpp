#include <bits/stdc++.h>
using namespace std;

constexpr int kMod = 1'000'000'000 + 7;

struct Node {
    static mt19937 rng;
    Node *lc, *rc;
    int sum, val, tag, sz;
    uint32_t pri;

    Node() : lc(nullptr), rc(nullptr) {}
    Node(int v) : val(v), sum(v), tag(1), sz(1), lc(nullptr), rc(nullptr), pri(rng()) {}

    void Push() { 
        if (lc) lc->Mult(tag);
        if (rc) rc->Mult(tag);
        tag = 1;
    }

    void Mult(int p) {
        sum = 1LL * sum * p % kMod;
        val = 1LL * val * p % kMod;
        tag = 1LL * tag * p % kMod;
    }

    void Pull() {
        sz = 1;
        sum = val; 
        if (lc) {
            sz += lc->sz;
            (sum += lc->sum) >= kMod ? sum -= kMod : 0;
        }
        if (rc) {
            sz += rc->sz;
            (sum += rc->sum) >= kMod ? sum -= kMod : 0;
        }
    }
};

Node *Merge(Node *a, Node *b) {
    if (!a || !b) return a ? a : b;
    a->Push();
    b->Push();
    if (a->pri > b->pri) {
        a->rc = Merge(a->rc, b);
        a->Pull();
        return a;
    } else {
        b->lc = Merge(a, b->lc);
        b->Pull();
        return b;
    }
}

void SplitBySize(Node *t, int k, Node *&a, Node *&b) {
    if (!t) {
        a = b = nullptr;
        return;
    }
    t->Push();
    int v = (t->lc ? t->lc->sz : 0) + 1;
    if (v <= k) {
        a = t;
        SplitBySize(t->rc, k - v, a->rc, b);
        a->Pull();
    } else {
        b = t;
        SplitBySize(t->lc, k, a, b->lc);
        b->Pull();
    }
}

int PrefixSum(Node *&t, int k) {
    if (k < 0) return 0;
    assert(t && t->sz > k);
    int bsz = t->sz;
    Node *a, *b;
    SplitBySize(t, k + 1, a, b);
    assert(a);
    int res = a->sum;
    t = Merge(a, b);
    assert(bsz == t->sz);
    return res;
}

void RangeMult(Node *&t, int l, int r, int k) {
    int bsz = t->sz;
    Node *a, *b, *c, *d;
    SplitBySize(t, l, a, b);
    SplitBySize(b, r - l + 1, c, d);
    c->Mult(k);
    t = Merge(a, Merge(c, d));
    assert(bsz == t->sz);
}


void ReSize(Node *&t, int k) {
    if (t->sz > k) {
        Node *a, *b;
        SplitBySize(t, k, a, b);
        t = a;
    }
}

vector<int> Flatten(Node *t) {
    vector<int> res;
    auto Dfs = [&](auto self, Node *x) -> void {
        x->Push();
        if (x->lc) self(self, x->lc);
        res.push_back(x->val);
        if (x->rc) self(self, x->rc);
    };

    Dfs(Dfs, t);
    return res;
}

int Get(Node *&t, int k) {
    int bsz = t->sz;
    Node *a, *b;
    SplitBySize(t, k, a, b);
    Node *c, *d;
    SplitBySize(b, 1, c, d);
    int res = c->val;
    t = Merge(a, Merge(c, d));
    return res;
}

void Set(Node *&t, int k, int v) {
    int bsz = t->sz;
    Node *a, *b;
    SplitBySize(t, k, a, b);
    Node *c, *d;
    SplitBySize(b, 1, c, d);
    c->val = v;
    c->sum = v;
    t = Merge(a, Merge(c, d));
    assert(bsz == t->sz);
}

mt19937 Node::rng(7122);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // vector<deque<int>> dp(n);

    // auto PrefixSum = [&](int x, int p) {
    //     int sum = 0;
    //     for (int i = 0; i <= p; ++i) {
    //         sum += dp[x][i];
    //         sum >= kMod ? sum -= kMod : 0;
    //     }
    //     return sum;
    // };

    // auto RangeMult = [&](int x, int l, int r, int p) {
    //     cout << "RangeMult l = " << l << " r = " << r << " p = " << p << endl;
    //     for (int i = l; i <= r; ++i) {
    //         dp[x][i] = 1LL * dp[x][i] * p % kMod;
    //     }
    // };

    vector<Node *> dp(n, nullptr);

    function<void(int, int)> Dfs = [&](int x, int p) {
        int prd = 1;
        dp[x] = new Node(1);
        for (int u : g[x]) {
            if (u == p) continue;
            Dfs(u, x);
            dp[u]->Push();
            // cout << "u = " << u << " dp[u].size() = " << dp[u]->sz << endl;
            // cout << "x = " << x << " u = " << u << " dp[x].size() = " << dp[x]->sz << endl;
            int sum = dp[u]->sum;
            prd = 1LL * prd * sum % kMod;
            if (dp[u]->sz > dp[x]->sz) swap(dp[u], dp[x]);
            // cout << "after x = " << x << " u = " << u << " dp[x].size() = " << dp[x]->sz << endl;
            vector<pair<int, int>> event;
            auto dpu = Flatten(dp[u]);
            vector<int> pref(dpu.size());
            for (int i = 0; i < dpu.size(); ++i) {
                pref[i] = dpu[i];
                if (i > 0) (pref[i] += pref[i - 1]) >= kMod ? pref[i] -= kMod : 0;
            }
            // cout << "before x = " << x << " u = " << u << " dp[x].size() = " << dp[x]->sz << endl;
            vector<int> st(dpu.size());
            for (int i = 0; i < dpu.size(); ++i) {
                int got = min(i, k - i - 1);
                int xi = Get(dp[x], i);
                // cout << "xi " << dp[x]->sz << endl;
                int sum = (1LL * dpu[i] * PrefixSum(dp[x], got) % kMod + 1LL * xi * (got < 0 ? 0 : pref[got]) % kMod) % kMod;
                // cout << "pref " << dp[x]->sz << endl;
                if (i + i < k) {
                    sum += kMod - 1LL * dpu[i] * xi % kMod;
                    sum %= kMod;
                }
                st[i] = sum;
                if (dpu.size() + i < k) {
                    int lb = dpu.size();
                    int rb = min(k - i - 1, dp[x]->sz - 1);
                    if (lb > rb) continue;
                    event.emplace_back(lb, dpu[i]);
                    event.emplace_back(rb + 1, kMod - dpu[i]);
                }
                // for (int j = 0; j <= i && i + j < k) {
                //     sum += 1LL * dp[u][i] * dp[x][j] vector% kMod;
                //     sum %= kMod;
                //     sum += 1LL * dp[u][j] * dp[x][i] % kMod;
                //     sum %= kMod;
                // }
            }
            for (int i = 0; i < dpu.size(); ++i) Set(dp[x], i, st[i]);
            // if (x == 0) cout << "ddone dp[x].size() = " << dp[x]->sz << endl;
            sort(event.begin(), event.end());
            int cover = 0, prv = -1;
            for (int i = 0, j = 0; i < event.size(); i = j) {
                if (prv != -1) {
                    RangeMult(dp[x], prv, event[i].first - 1, cover);
                }
                prv = event[i].first;
                while (j < event.size() && event[j].first == event[i].first) {
                    cover += event[j].second;
                    if (cover >= kMod) cover -= kMod;
                    j++;
                }
            }
            // if (x == 0) cout << "done dp[x].size() = " << dp[x]->sz << endl;
            // for (int i = 0; i < dp[u].size(); ++i) {
            //     for (int j = 0; j < dp[x].size(); ++j) {
            //         if (i + j < k) {
            //             nxt[max(i, j)] += 1LL * dp[u][i] * dp[x][j] % kMod;
            //             if (nxt[max(i, j)] >= kMod) nxt[max(i, j)] -= kMod;
            //             // add.emplace_back(max(i, j), 1LL * dp[u][i] * dp[x][j] % kMod);
            //         }
            //     }
            // }
            // dp[x] = nxt;
            // for (auto &v : add) {
            //     dp[x][v.first] += v.second;
            //     if (dp[x][v.first] >= kMod) dp[x][v.first] -= kMod;
            // }
            // cout << "x = " << x << " after u = " << u << endl;
            // for (int i = 0; i < dp[x]->sz; ++i) {
            //     cout << "dp[" << x << "][" << i << "] = " << Get(dp[x], i) << endl;
            // }
            // cout << "end" << endl;
        }
        dp[x] = Merge(new Node(prd), dp[x]);
        ReSize(dp[x], k + 1);
        assert(dp[x]->sz <= k + 1);
        // for (int i = 0; i < dp[x]->sz; ++i) {
        //     cout << "dp[" << x << "][" << i << "] = " << Get(dp[x], i) << endl;
        // }
    };

    Dfs(0, -1);
    dp[0]->Push();
    cout << dp[0]->sum << "\n";
    return 0;
}

