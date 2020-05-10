#include <bits/stdc++.h>
using namespace std;

int HexToDec(string s) {
    int x = 0;
    for (char c : s) {
        x *= 16;
        if (c >= 'A' && c <= 'F') x += c - 'A' + 10;
        else x += c & 15;
    }
    return x;
}

string Encode(int x) {
    if (x == 0) return "0";
    string r;
    while (x) {
        int z = x & 15;
        x >>= 4;

        if (z >= 10) r += char(z - 10 + 'A');
        else r += char(z + '0');
    }

    reverse(r.begin(), r.end());

    return r;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s; 
    vector<int> v;
    while (cin >> s) {
        v.push_back(HexToDec(s));
        // cout << bitset<8>(v.back()) << '\n';
    }

    for (int i = 0; i < (int)v.size(); ) {
        int j = i;
        int len = 0;
        vector<int> tmp;

        auto Try = [&] (int fo) {
            // cerr << "Try " << fo << endl;
            int x = v[j] & ((1 << (6 - fo)) - 1);
            for (int i = 1; i <= fo; ++i) {
                ++j;
                if (j >= (int)v.size()) return false;
                if ((v[j] >> 6) != 2) return false;
                x <<= 6;
                x |= v[j] & ((1 << 6) - 1);
            }
            len += 1 + fo;
            tmp.push_back(x);
            // cerr << "good" << endl;
            ++j;
            return true;
        };

        while (j < (int)v.size()) {
            // cerr << "j = " << j << " = " << bitset<8>(v[j]) << endl;
            if ((v[j] >> 7) == 0) {
                tmp.push_back(v[j]);
                ++j;
                ++len;
            } else if ((v[j] >> 5) == 6) {
                if (!Try(1)) break;
            } else if ((v[j] >> 4) == 14) {
                if (!Try(2)) break;
            } else if ((v[j] >> 3) == 30) {
                if (!Try(3)) break;
            } else if ((v[j] >> 2) == 62) {
                if (!Try(4)) break;
            } else if ((v[j] >> 1) == 126) {
                if (!Try(5)) break;
            } else {
                ++j;
                break;
            }
            // cerr << "continue" << endl;
        }

        // cerr << "j len " << j << ' ' << len << endl;

        if (tmp.size() >= 3u) {
            for (int i : tmp) cout << Encode(i) << ' ';
            cout << endl;
        }
        i = j;

    }
}

