#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int a[maxn], lb[maxn], rb[maxn];
int st[maxn * 4], ans[maxn], res[maxn], x[maxn], y[maxn];
vector<pair<int, int>> qr[maxn];

void modify(int l, int r, int p, int v, int o = 0) {
    if (r - l == 1)
        return st[o] = v, void();
    if (p < (l + r) >> 1)
        modify(l, (l + r) >> 1, p, v, o * 2 + 1);
    else
        modify((l + r) >> 1, r, p, v, o * 2 + 2);
    st[o] = max(st[o * 2 + 1], st[o * 2 + 2]);
}

int query(int l, int r, int ql, int qr, int o = 0) {
    if (l >= qr || ql >= r) return 0;
    if (l >= ql && r <= qr) return st[o];
    return max(query(l, (l + r) >> 1, ql, qr, o * 2 + 1),
               query((l + r) >> 1, r, ql, qr, o * 2 + 2));
}

vector<int> record;
vector<pair<int, int>> hist;

int fw[maxn], cnt[maxn], cc[maxn];

void add(int p, int v) {
    // printf("add p = %d v = %d\n", p, v);
    for (int i = p; i < maxn; i += i & -i)
        fw[i] += v;
}

int query(int p) {
    int res = 0;
    for (int i = p; i > 0; i -= i & -i)
        res += fw[i];
    return res;
}

void insert(int v, bool g) {
    // printf("insert v = %d\n", v);
    ++cc[v];
    if (cnt[a[v]] == 0) add(a[v], 1);
    ++cnt[a[v]];
    if (g) hist.emplace_back(v, 1);
}

void erase(int v, bool g) {
    // printf("erase v = %d\n", v);
    --cc[v];
    --cnt[a[v]];
    if (cnt[a[v]] == 0) add(a[v], -1);
    if (g) hist.emplace_back(v, -1);
}

void save() {
    record.push_back((int)hist.size());
}

void undo() {
    int z = record.back(); record.pop_back();
    while ((int)hist.size() > z) {
        int p = hist.back().first, v = hist.back().second;
        if (v == -1) insert(p, false);
        else erase(p, false);
        hist.pop_back();
    }
}

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < n; ++i) {
        lb[i] = i - 1;
        while (lb[i] >= 0 && a[i] > a[lb[i]]) lb[i] = lb[lb[i]];
    }
    for (int i = n - 1; i >= 0; --i) {
        rb[i] = i + 1;
        while (rb[i] < n && a[i] > a[rb[i]]) rb[i] = rb[rb[i]];
    }

    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [&](int i, int j) { return a[i] < a[j]; });

    for (int i = 0; i < n; ++i) {
        int j = v[i];
        ans[j] = query(0, n, lb[j] + 1, rb[j]) + 1;
        modify(0, n, j, ans[j]);
        --ans[j];
    }

    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        --x[i], --y[i];
        if (y[i] == -1) {
            res[i] = ans[x[i]];
            continue;
        }
        if (a[x[i]] > a[y[i]]) swap(x[i], y[i]);
        qr[x[i]].emplace_back(y[i], i);
    }

    stack<int> stk;
    for (int i = 0; i < n; ++i) {
        save();
        while (!stk.empty() && a[stk.top()] <= a[i]) {
            erase(stk.top(), true);
            stk.pop();
        }
        insert(i, true);
        stk.push(i);
    }
    while (!stk.empty()) stk.pop();

    for (int i = n - 1; i >= 0; --i) {
        // printf("i = %d\n", i);
        while (!stk.empty() && a[stk.top()] <= a[i]) {
            // printf("pop %d\n", stk.top());
            erase(stk.top(), false);
            stk.pop();
        }
        insert(i, false);
        for (auto p : qr[i]) {
            int v = a[p.first];
            // printf("p.first = %d\n", p.first);
            if (cc[p.first] > 0) {
                // printf("v = %d\n", v);
                // printf("q = %d\n", query(v - 1));
                res[p.second] = query(v - 1);
            }
        }
        stk.push(i);
        // printf("start undo\n");
        undo();
        // printf("end undo\n");
    }
    for (int i = 0; i < q; ++i) printf("%d\n", res[i]);
    return 0;
}
