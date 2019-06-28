#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int a[maxn], t[maxn];
int l[maxn], r[maxn];
long long st1[maxn * 4], st2[maxn * 4], tg[maxn * 4];
long long dp[maxn];

/* void build(int l, int r, int o = 0) {
    if (r - l == 1) {
        st1[o] = (l == 0 ? 0
    }
} */

void push(int o) {
    st1[o * 2 + 1] += tg[o];
    st2[o * 2 + 1] += tg[o];
    tg[o * 2 + 1] += tg[o];
    st1[o * 2 + 2] += tg[o];
    st2[o * 2 + 2] += tg[o];
    tg[o * 2 + 2] += tg[o];
    tg[o] = 0;
}

long long query1(int l, int r, int ql, int qr, int o = 0) {
    if (l >= qr || ql >= r) return 1e18;
    if (l >= ql && r <= qr) return st1[o];

    push(o);

    return min(query1(l, (l + r) >> 1, ql, qr, o * 2 + 1),
               query1((l + r) >> 1, r, ql, qr, o * 2 + 2));
}

long long query2(int l, int r, int ql, int qr, int o = 0) {
    // printf("query2 l = %d r = %d ql = %d qr = %d\n", l, r, ql, qr);
    if (l >= qr || ql >= r) return 1e18;
    if (l >= ql && r <= qr) return st2[o];

    push(o);

    return min(query2(l, (l + r) >> 1, ql, qr, o * 2 + 1),
               query2((l + r) >> 1, r, ql, qr, o * 2 + 2));
}

void modify(int l, int r, int ql, int qr, int v, int o = 0) {
//        if (o == 0) printf("modify l = %d r = %d ql = %d qr = %d v = %d\n", l, r, ql, qr, v);
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) {
        st1[o] += v;
        st2[o] += v;
        tg[o] += v;
        return;
    }

    push(o);

    modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
    modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);

    st1[o] = min(st1[o * 2 + 1], st1[o * 2 + 2]);
    st2[o] = min(st2[o * 2 + 1], st2[o * 2 + 2]);
}

void modify2(int l, int r, int p, long long v, int o = 0) {
        // printf("modify2 l = %d r = %d p = %d v = %lld\n", l, r, p, v);

    if (r - l == 1) {
        // printf("l = %d\n", l);
        st2[o] += v;
        return;
    }

    push(o);

    if (p < ((l + r) >> 1))
        modify2(l, (l + r) >> 1, p, v, o * 2 + 1);
    else 
        modify2((l + r) >> 1, r, p, v, o * 2 + 2);

    st2[o] = min(st2[o * 2 + 1], st2[o * 2 + 2]);
}

void debug(int l, int r, int o = 0) {
    if (r - l == 1) {
        printf("st1[%d] = %lld\n", l, st1[o]);
        printf("st2[%d] = %lld\n", l, st2[o]);
        return;
    }

    push(o);

    debug(l, (l + r) >> 1, o * 2 + 1);
    debug((l + r) >> 1, r, o * 2 + 2);
}

int main() {
    int n; 
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &t[i], &a[i]);

        for (int i = 0; i <= 4 * n; ++i) st1[i] = st2[i] = tg[i] = 0;

        dp[0] = 0;

        stack<int> st;

        /* for (int i = 1; i <= n; ++i) {
            int p = 0;
            dp[i] = 1e18;
            for (int j = i - 1; j >= 0; --j) {
                p = max(p, a[j + 1]);
                dp[i] = min(dp[i], max(dp[j], 1ll * t[i]) + 2 * p);
            }
            printf("dp[%d] = %lld\n", i, dp[i]);
        } */

        for (int i = 1; i <= n; ++i) {
            while (!st.empty() && a[i] >= a[st.top()]) {
                modify(0, n + 1, l[st.top()], r[st.top()], 2 * -a[st.top()]);
                st.pop();
            }

            if (!st.empty() && i < r[st.top()]) {
                modify(0, n + 1, i, r[st.top()], 2 * -a[st.top()]);
                r[st.top()] = i;
            }

            l[i] = st.empty() ? 0 : r[st.top()];
            r[i] = n + 1;
            st.push(i);

            modify(0, n + 1, l[i], r[i], 2 * a[i]);
            int j = lower_bound(dp, dp + i, 1ll * t[i]) - dp + 1;
            /* puts("before");
            debug(0, n + 1);
            printf("j = %d\n", j); */
            // printf("query2 = %lld\n", query2(0, n, j, i + 1));
            // printf("query1 = %lld\n", query1(0, n, 1, j));
            dp[i] = min(query2(0, n + 1, j, i + 1), query1(0, n + 1, 1, j) + t[i]);
            modify2(0, n + 1, i + 1, dp[i]);

            // printf("dp[%d] = %lld\n", i, dp[i]);

        }

        printf("%lld\n", dp[n]);
    }
    return 0;
}
