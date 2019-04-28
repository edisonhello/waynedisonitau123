#include <bits/stdc++.h>
using namespace std;

string a, s, d;
int ui, uj;

void read() {
    string aa, ss, dd;
    cin >> aa >> ss >> dd;
    for (int i = 0; i < 3; ++i) {
        if (a[i] != aa[i]) ui = 0, uj = i;
        if (s[i] != ss[i]) ui = 1, uj = i;
        if (d[i] != dd[i]) ui = 2, uj = i;
    }
    tie(a, s, d) = make_tuple(aa, ss, dd);
}

bool board(string z, string x, string c) {
    return z == a && x == s && c == d;
}

void out(string a, string s, string d) {
    cout << a << endl << s << endl << d << endl;
}

bool update(int z, int x) {
    return z == ui && x == uj;
}

void place(int i, int j) {
    if (i == 0) a[j] = 'x';
    if (i == 1) s[j] = 'x';
    if (i == 2) d[j] = 'x';
    out(a, s, d);
    read();
}

void game() {
    place(1, 1);
    if (board("o..", ".x.", "...")) {
        place(0, 2);
        if (board("o.x", ".x.", "o..")) {
            place(1, 2);
            if (!board("o.x", "oxx", "o..")) {
                place(1, 0);
                return;
            }
            place(2, 2);
            return;
        }
        place(2, 0);
        return;
    } else if (board(".o.", ".x.", "...")) {
        place(1, 2);
        if (board(".o.", "oxx", "...")) {
            place(0, 2);
            if (board(".ox", "oxx", "o..")) {
                place(2, 2);
                return;
            }
            place(2, 0);
            return;
        }
        place(1, 0);
        return;
    } else if (board("..o", ".x.", "...")) {
        place(0, 0);
        if (!board("x.o", ".x.", "..o")) place(2, 2);
        else {
            place(1, 0);
            if (!board("x.o", "xxo", "..o")) place(1, 2);
            else place(2, 0);
        }
        return;
    } else if (board("...", ".xo", "...")) {
        place(0, 1);
        if (!update(2, 1)) place(2, 1);
        else {
            place(0, 2);
            if (update(0, 0)) place(2, 0);
            else place(0, 0);
        }
        return;
    } else if (update(2, 2)) {
        place(2, 0);
        if (!update(0, 2)) place(0, 2);
        else {
            place(1, 0);
            if (!update(1, 2)) place(1, 2);
            else place(0, 0);
        }
        return; 
    } else if (update(2, 1)) {
        place(1, 0);
        if (!update(1, 2)) place(1, 2);
        else {
            place(0, 0);
            if (!update(2, 0)) place(2, 0);
            else place(2, 2);
        }
        return;
    } else if (update(2, 0)) {
        place(0, 0);
        if (!update(2, 2)) place(2, 2);
        else {
            place(0, 1);
            if (!update(2, 1)) place(2, 1);
            else place(0, 2);
        }
        return;
    } else if (update(1, 0)) {
        place(0, 1);
        if (!update(2, 1)) place(2, 1);
        else {
            place(0, 0);
            if (!update(0, 2)) place(0, 2);
            else place(2, 2);
        }
        return;
    }
}

int main() {
    read();
    while (true) {
        if (a == s && s == d && d == "xxx") break;
        game();
    }
}
