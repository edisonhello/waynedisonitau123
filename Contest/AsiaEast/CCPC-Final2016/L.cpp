#include <bits/stdc++.h>
using namespace std;

int _days[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int Days(int y, int m) {
    if (m != 2) return _days[m];
    if (y % 4) return 28;
    if (y % 100) return 29;
    if (y % 400) return 28;
    return 29;
}


int wee[150][15][33];

int main() {
    int y = 20, m = 10, d = 29, w = 4;
    wee[y][m][d] = w;
    while (y >= 7) {
        --d;
        if (d <= 0) {
            --m;
            if (m <= 0) {
                --y;
                m = 12;
            }
            d = Days(y, m);
        }
        --w; if (w < 0) w = 6;
        wee[y][m][d] = w;
    }

    y = 20, m = 10, d = 29, w = 4;
    while (y <= 100) {
        ++d;
        if (d > Days(y, m)) {
            d = 1;
            ++m;
            if (m > 12) {
                m = 1;
                ++y;
            }
        }
        ++w; if (w >= 7) w = 0;
        wee[y][m][d] = w;
    }


    int t; scanf("%d", &t);
    for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int Y, M, D, h, m, s;
        scanf("%d-%d-%d %d:%d:%d", &Y, &M, &D, &h, &m, &s);
        if (4 <= M && M <= 10) {
            cout << "PDT" << '\n';
        } else if (M <= 2 || M >= 12) {
            cout << "PST" << '\n';
        } else if (M == 3) {
            int dd = Days(Y, 3);
            int chd = -1;
            int sunc = 0;
            for (int d = 1; d <= dd; ++d) {
                if (wee[Y - 2000][3][d] == 0) {
                    ++sunc;
                    if (sunc == 2) {
                        chd = d;
                        break;
                    }
                }
            }
            if (D < chd) cout << "PST" << '\n';
            else if (D > chd) cout << "PDT" << '\n';
            else {
                if (h < 2) cout << "PST" << '\n';
                else if (h >= 3) cout << "PDT" << '\n';
                else cout << "Neither" << '\n';
            }
        } else if (M == 11) {
            int dd = Days(Y, 11);
            int chd = -1;
            for (int d = 1; d <= dd; ++d) {
                if (wee[Y - 2000][3][d] == 0) {
                    chd = d;
                    break;
                }
            }

            if (D < chd) cout << "PDT" << '\n';
            else if (D > chd) cout << "PST" << '\n';
            else {
                if (h < 1) cout << "PDT" << '\n';
                else if (h > 1) cout << "PST" << '\n';
                else cout << "Both" << '\n';
            }
        }
    }
}

