#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; scanf("%d%d", &n, &k);
    vector<int> v = {k};
    for (int i = 1; i < n; ++i) {
        vector<int> w;
        int need = (i + 2) / 2 - 1;
        vector<int> x, y;
        for (int j = 0; j < (int)v.size(); ++j) {
            if (v[j] == -1)
                x.push_back(j);
        }
        for (int j = 0; j < (int)v.size(); ++j) {
            if (v[j] == 0)
                y.push_back(j);
        }
        w.resize(i + 1);

        int take = 0;
        for (int j = 0; j < (int)x.size() && need > 0; ++j) {
            w[x[j] + 1] = 0;
            need--;
        }
        for (int j = 0; j < (int)y.size() && need > 0; ++j) {
            w[y[j] + 1] = 1;
            need--;
            take++;
        }

        if (take > k) {
            w = vector<int>(i + 1, 0);
            for (int j = 1; j < (int)w.size(); ++j)
                w[j] = v[j - 1];
            w[0] = -1;
        } else {
            w[0] = k - take;
        }
        v = w;
    }

    for (int i = 0; i < n; ++i)
        printf("%d ", v[i]);
    puts("");
}
