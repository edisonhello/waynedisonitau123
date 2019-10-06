#include <bits/stdc++.h>
using namespace std;

long long CC[15][15];
double C(int n, int m) {
    return CC[n][m];
}

double serve(double p, double q) {
    double ch = 0;
    ch += C(4 - 1 + 0, 0) * pow(p, 4) * pow(1 - p, 0);
    ch += C(4 - 1 + 1, 1) * pow(p, 4) * pow(1 - p, 1);
    ch += C(4 - 1 + 2, 2) * pow(p, 4) * pow(1 - p, 2);
    ch += C(6, 3) * pow(p, 3) * pow(1 - p, 3) * (p * p / (p * p + (1 - p) * (1 - p)));
    return ch;
}

double not_serve(double p, double q) {
    double ch = 0;
    ch += C(4 - 1 + 0, 0) * pow(q, 4) * pow(1 - q, 0);
    ch += C(4 - 1 + 1, 1) * pow(q, 4) * pow(1 - q, 1);
    ch += C(4 - 1 + 2, 2) * pow(q, 4) * pow(1 - q, 2);
    ch += C(6, 3) * pow(q, 3) * pow(1 - q, 3) * (q * q / (q * q + (1 - q) * (1 - q)));
    return ch;
}

pair<double, double> operator + (const pair<double, double> &a, const pair<double, double> &b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

pair<double, double> dfs2(double p, double q, double x, double y, int win, int lose, double ch, int serve) {
    if (win == 6 && lose <= 4) return make_pair(ch, 0);
    if (lose == 6 && win <= 4) return make_pair(0, ch);
    if (win == 7 && lose == 5) return make_pair(ch, 0);
    if (lose == 7 && win == 5) return make_pair(0, ch);
    if (win == 5 && lose == 5) {
        if (serve) return make_pair(ch * x, ch * y);
        else return make_pair(ch * y, ch * x);
    }
    if (serve) {
        return dfs2(p, q, x, y, win + 1, lose, ch * p, serve ^ 1)
            + dfs2(p, q, x, y, win, lose + 1, ch * (1 - p), serve ^ 1);
    } else {
        return dfs2(p, q, x, y, win + 1, lose, ch * q, serve ^ 1)
            + dfs2(p, q, x, y, win, lose + 1, ch * (1 - q), serve ^ 1);
    }
}

double dfs(double p, double q, int round, int xwin, int ywin, double ch) {
    if (xwin == 3) return ch;
    if (ywin == 3) return 0;
    // double x = (p * p + 2 * p * (1 - p) * q * q) / (1 - 2 * p * (1 - p) * 2 * q * (1 - q)); // chance that serve win
    // double y = q * q + 2 * q * (1 - q) * x; // chance that not serve win
    double x = p * q / (1 - p * (1 - q) - (1 - p) * q); // chance that serve win
    // cerr << "x = " << x << endl;
    // pair<double, double> win_chance = dfs2(p, q, x, y, 0, 0, 1, round & 1);
    pair<double, double> win_chance = dfs2(p, q, x, 1 - x, 0, 0, 1, round & 1);
    // cerr << "(,)" << win_chance.first << " , " << win_chance.second << endl;
    if (round & 1) { // me serve
        return dfs(p, q, round + 1, xwin + 1, ywin, ch * win_chance.first)
            + dfs(p, q, round + 1, xwin, ywin + 1, ch * win_chance.second);
    } else { // you serve
        return dfs(p, q, round + 1, xwin + 1, ywin, ch * win_chance.first)
            + dfs(p, q, round + 1, xwin, ywin + 1, ch * win_chance.second);
    }
}

int main() {
    CC[0][0] = 1;
    for (int i = 1; i < 15; ++i) {
        for (int j = 0; j <= i; ++j) {
            CC[i][j] = CC[i - 1][j];
            if (j) CC[i][j] += CC[i - 1][j - 1];
        }
    }
    double p, q; cin >> p >> q;
    double x = serve(p, q), y = not_serve(p, q);
    // cerr << "serve win chance = " << x << " , not serve = " << y << endl;
    double ans = dfs(x, y, 1, 0, 0, 1);
    cout << fixed << setprecision(10) << ans << endl;
}
