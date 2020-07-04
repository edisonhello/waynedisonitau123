#include <bits/stdc++.h>
using namespace std;

long long GetPosition(long long x) {
    long long b = 1;
    long long l = 1;
    long long r = 0;
    while (b <= x) {
        r += l * (1ll << (l - 1));
        b = (b << 1) | 1;
        ++l;
    }
    b >>= 1;
    r += (x - b) * l;
    return r;
}

long long Bin2Int(string s) {
    long long x = 0;
    for (char c : s) {
        if (c == '0') x <<= 1;
        else x = (x << 1) | 1;
    }
    return x;
}
string Int2Bin(long long x) {
    if (x == 0) return "0";
    string s;
    while (x) {
        if (x & 1) s = "1" + s;
        else s = "0" + s;
        x >>= 1;
    }
    return s;
}

string AddOne(string s) {
    ++s.back();
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] >= '2') {
            s[i] -= 2;
            s[i - 1] += 1;
        } else break;
    }
    return s;
}

long long Case1(string s) {
    if (s[0] == '0') s = "1" + s;
    return GetPosition(Bin2Int(s));
}

long long Case2(string s) {
    // cerr << "case 2 " << endl;
    long long rt = LLONG_MAX;
    for (int i = 0; i < (int)s.size(); ++i) {
        for (int j = i; j < (int)s.size(); ++j) {
            if (j != (int)s.size() - 1 && s[j + 1] == '0') continue;
            if (s[i] != '1') continue;
            long long x = Bin2Int(s.substr(i, j - i + 1));
            // cerr << "i j x " << i << ' ' << j << ' ' << x << endl;
            auto GoPrev = [&, x, i, j] () mutable -> bool {
                while (i) {
                    --x;
                    if (x == 0) return false;
                    string sx = Int2Bin(x);
                    j = i - 1;
                    i = j - (int)sx.size() + 1;
                    if (i < 0) {
                        sx = sx.substr(-i, (int)sx.size() + i);
                        i = 0;
                    }
                    if (sx != s.substr(i, j - i + 1)) return false;
                }
                // cerr << "go prev ok " << endl;
                return true;
            };
            auto GoNext = [&, x, i, j] () mutable -> bool {
                while (j < (int)s.size() - 1) {
                    ++x;
                    string sx = Int2Bin(x);
                    i = j + 1;
                    j = i + (int)sx.size() - 1;
                    if (j >= (int)s.size()) {
                        sx = sx.substr(0, (int)s.size() - i);
                        j = (int)s.size() - 1;
                    }
                    if (sx != s.substr(i, j - i + 1)) return false;
                }
                // cerr << "go next ok " << endl;
                return true;
            };
            if (GoPrev() && GoNext()) rt = min(rt, GetPosition(x) + (int)s.size() - j - 1);
        }
    }
    // cerr << "case 2 get " << rt << endl;
    return rt;
}

long long Case3(string s) {
    // cerr << "Case 3 " << endl;
    long long rt = LLONG_MAX;
    for (int i = 0; i < (int)s.size() - 1; ++i) {
        if (s[i + 1] == '0') continue;

        auto All1 = [&] () {
            for (int j = 0; j <= i; ++j) if (s[j] != '1') return false;
            return true;
        };

        string pre = s.substr(0, i + 1);
        string suf = s.substr(i + 1, s.size() - (i + 1));
        // cerr << "pre suf " << pre << ' ' << suf << endl;
        if (All1()) {
            int sufc0 = 0;
            for (int i = suf.size() - 1; i >= 0; --i) {
                if (suf[i] == '0') ++sufc0;
                else break;
            }

            if (sufc0 >= (int)pre.size()) {
                // 
            } else {
                int diff = (int)pre.size() - sufc0;
                for (int i = 0; i < diff; ++i) suf += "0";
                rt = min(rt, GetPosition(Bin2Int(suf)) - diff);
            }
        } else {
            // cerr << "not all 1 " << endl;
            pre = AddOne(pre);
            for (int overlap = (int)min(pre.size(), suf.size()) - 1; overlap >= 0; --overlap) {
                // cerr << "overlap = " << overlap << endl;
                bool ok = true;
                for (int i = suf.size() - overlap, j = 0; i < (int)suf.size(); ++i, ++j) {
                    if (suf[i] != pre[j]) ok = false;
                }

                // cerr << "ok = " << ok << endl;

                if (ok) {
                    string sx = suf + pre.substr(overlap, pre.size() - overlap);
                    // cerr << "sx = " << sx << endl;
                    rt = min(rt, GetPosition(Bin2Int(sx) - 1) + (int)suf.size());
                }
            }
        }
    }
    // cerr << "case 3 get " << rt << endl;
    return rt;
}

int main() {
    string s;
    cin >> s;
    
    cout << min(min(Case1(s), Case2(s)), Case3(s)) << endl;
}

