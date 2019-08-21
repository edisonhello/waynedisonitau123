#include <bits/stdc++.h>
using namespace std;
#define double long double

double get_len() {
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    return hypot(x1 - x2, y1 - y2);
}

double cross(double a, double b, double c, double d) {
    return a * d - b * c;
}

double get_area() {
    double x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    return abs(cross(x2 - x1, y2 - y1, x3 - x1, y3 - y1));
}

int djs[105];
long long ara[105];

int F(int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); }

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        double a = get_len();
        double b = get_len();
        int r; cin >> r;
        double sum = 0;
        while (r--) sum += get_area();
        sum *= 40000 / a / b;
        ara[i] = (long long)(round(sum));
        // cerr << i << " area " << sum << endl;
    }
    for (int i = 1; i <= n; ++i) djs[i] = i;
    for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) {
        if (ara[i] == ara[j])
            djs[F(i)] = F(j);
    }
    for (int i = 1; i <= n; ++i) cout << F(i) << " "; cout << endl;
}
