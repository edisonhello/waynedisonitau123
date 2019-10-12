#include <bits/stdc++.h>
using namespace std;

// struct node {
//     node *next;
//     int val;
//     node(): next(0), val(0) {}
//     node(int v): next(0), val(v) {}
//     node(node *ref): next(ref->next), val(ref->val) {}
// };
// 
// node *head[200005], *tail[200005];

int curhead[200005];
int pa[20][200005], dep[200005];
int is_push[200005], val[200005];

int get_nxt_child(int pppa, int me) {
    // cout << "get_nxt_child of " << me << " from " << pppa << endl;
    for (int z = 19; z >= 0; --z) {
        if (dep[pa[z][me]] <= dep[pppa]) continue;
        // cout << "me climb to " << pa[z][me] << endl;
        me = pa[z][me];
    }
    return me;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);

    // head[0] = tail[0] = new node(0);
    int q; cin >> q; 
    for (int i = 1; i <= q; ++i) {
        // cout << "i = " << i << endl;
        int c; cin >> c;
        if (c == 1) {
            int pv, v; cin >> pv >> v;
            dep[i] = dep[pv] + 1;
            curhead[i] = curhead[pv];
            is_push[i] = 1;
            val[i] = v;

            pa[0][i] = pv;
            for (int z = 1; z < 20; ++z) pa[z][i] = pa[z - 1][pa[z - 1][i]];
            //         head[i] = new node(head[pv]);
            //         tail[i] = new node(tail[pv]);
            //         tail[i]->next = new node(v);
            //         tail[i] = tail[i]->next;
        } else {
            int pv; cin >> pv;
            curhead[i] = curhead[pv];
            dep[i] = dep[pv] + 1;
            pa[0][i] = pv;
            for (int z = 1; z < 20; ++z) pa[z][i] = pa[z - 1][pa[z - 1][i]];

            curhead[i] = get_nxt_child(curhead[i], i);
            while (!is_push[curhead[i]]) {
                curhead[i] = get_nxt_child(curhead[i], i);
            }
            cout << val[curhead[i]] << '\n';
            //         head[i] = new node(head[pv]->next);
            //         tail[i] = new node(tail[pv]);
            //         cout << head[i]->val << '\n';
        }
    }
}
