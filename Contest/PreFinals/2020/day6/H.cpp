#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int64_t x, y, diff;

    TreeNode() : x(0), y(0), diff(0) {}
};

int main() {
    int n, m;
    cin >> n;
    vector<int> x1(n), y1(n);
    vector<int> x2(m), y2(m);
    vector<int> dx, dy;
    for (int i = 0; i < n; ++i) {
        cin >> x1[i] >> y1[i];
        dx.push_back(x1[i]);
        dy.push_back(y1[i]);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> x2[i] >> y2[i];
        dx.push_back(x2[i]);
        dy.push_back(y2[i]);
    }

    sort(dx.begin(), dx.end());
    sort(dy.begin(), dy.end());
    
    vector<vector<int>> points(dx.size());
    for (int i = 0; i < n; ++i) {
        x1[i] = lower_bound(dx.begin(), dx.end(), x1[i]) - dx.begin();
        y1[i] = lower_bound(dy.begin(), dy.end(), y1[i]) - dy.begin();
        points[x1[i]].push_back(y1[i]);
    }
    for (int i = 0; i < m; ++i) {
        x2[i] = lower_bound(dx.begin(), dx.end(), x2[i]) - dx.begin();
        y2[i] = lower_bound(dy.begin(), dy.end(), y2[i]) - dy.begin();
        points[x2[i]].push_back(~y2[i]);
    }
    int c1, c2;
    cin >> c1 >> c2;
    int64_t res = 0;

    const int kC = dy.size();
    vector<TreeNode> tree((kC + 1) * 4);
    vector<int64_t> tag((kC + 1) * 4);

    auto Combine = [&](const TreeNode &a, const TreeNode &b) {
        TreeNode res;
        res.x = max(a.x, b.x);
        res.y = min(a.y, b.y);
        res.diff = max(a.diff, b.diff);
        res.diff = max(res.diff, b.x - a.y);
        return res;
    };

    auto Modify = [&](int ql, int qr, int v) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (l >= qr || ql >= r) return;
            if (l >= ql && r <= qr) {
                tree[o].x += v;
                tree[o].y += v;
                tag[o] += v;
                return;
            }
            for (int k = 1; k <= 2; ++k) {
                tree[o * 2 + k].x += tag[o];
                tree[o * 2 + k].y += tag[o];
                tag[o * 2 + k] += tag[o];
            }
            tag[o] = 0;
            int m = (l + r) >> 1;
            self(self, l, m, o * 2 + 1);
            self(self, m, r, o * 2 + 2);
            tree[o] = Combine(tree[o * 2 + 1], tree[o * 2 + 2]);
        };

        _(_, 0, kC + 1);
    };

    for (int i = 0; i < dx.size(); ++i) {
        fill(tree.begin(), tree.end(), TreeNode());
        fill(tag.begin(), tag.end(), 0);
        for (int j = i; j < dx.size(); ++j) {
            for (int u : points[j]) {
                if (u >= 0) {
                    Modify(u + 1, kC + 1, c1);
                } else {
                    Modify(~u + 1, kC + 1, -c2);
                }
            }
            res = max(res, tree[0].diff);
        }
    }
    cout << res << "\n";
    return 0;
}

