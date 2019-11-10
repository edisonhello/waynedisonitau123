#include <bits/stdc++.h>
using namespace std;

int appear[256];

void update(string &a, const string &b) {
    if (a.size() != b.size()) {
        if (b.size() < a.size()) a = b;
    }
    else if (b < a) a = b;
}


int main() {
    string s; getline(cin, s);
    for (char c : s) ++appear[c];

    auto generate = [&] (const vector<pair<int, int>> &v) {
        string rt;
        for (auto &p : v) {
            if (p.first == p.second) {
                rt += char(p.first);
            } else if (p.first == p.second - 1) {
                rt += char(p.first);
                rt += char(p.first + 1);
            } else {
                rt += char(p.first);
                rt += "-";
                rt += char(p.second);
            }
        }
        return rt;
    };

    auto merge = [&] (vector<pair<int, int>> vp) {
        sort(vp.begin(), vp.end());
        vector<pair<int, int>> res;
        for (auto &p : vp) {
            if (res.empty() || res.back().second < p.first - 1) {
                res.push_back(p);
            } else {
                res.back().second = max(res.back().second, p.second);
            }
        }

        return res;
    };

    string positive = [&] () {
        vector<pair<int, int>> segs;
        if (appear[32]) segs.emplace_back(32, 32);
        for (int i = 48, j; i < 58; i = j) {
            if (!appear[i]) {
                j = i + 1; 
                continue;
            }
            for (j = i; j < 58; ++j) {
                if (!appear[j]) break;
            }
            segs.emplace_back(i, j - 1);
        }
        for (int i = 65, j; i < 91; i = j) {
            if (!appear[i]) {
                j = i + 1; 
                continue;
            }
            for (j = i; j < 91; ++j) {
                if (!appear[j]) break;
            }
            segs.emplace_back(i, j - 1);
        }
        for (int i = 97, j; i < 123; i = j) {
            if (!appear[i]) {
                j = i + 1; 
                continue;
            }
            for (j = i; j < 123; ++j) {
                if (!appear[j]) break;
            }
            segs.emplace_back(i, j - 1);
        }
        string ans = generate(merge(segs));
        segs.emplace_back(33, 47);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.emplace_back(58, 64);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.emplace_back(91, 96);
        update(ans, generate(merge(segs)));
        segs.pop_back();

        segs.emplace_back(33, 47);
        segs.emplace_back(58, 64);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.pop_back();
        segs.emplace_back(33, 47);
        segs.emplace_back(91, 96);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.pop_back();
        segs.emplace_back(58, 64);
        segs.emplace_back(91, 96);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.pop_back();

        segs.emplace_back(33, 47);
        segs.emplace_back(58, 64);
        segs.emplace_back(91, 96);
        update(ans, generate(merge(segs)));

        return ans;
    }();

    string negative = [&] () {
        vector<pair<int, int>> segs;
        if (!appear[32]) segs.emplace_back(32, 32);
        for (int i = 48, j; i < 58; i = j) {
            if (appear[i]) {
                j = i + 1; 
                continue;
            }
            for (j = i; j < 58; ++j) {
                if (appear[j]) break;
            }
            segs.emplace_back(i, j - 1);
        }
        for (int i = 65, j; i < 91; i = j) {
            if (appear[i]) {
                j = i + 1; 
                continue;
            }
            for (j = i; j < 91; ++j) {
                if (appear[j]) break;
            }
            segs.emplace_back(i, j - 1);
        }
        for (int i = 97, j; i < 123; i = j) {
            if (appear[i]) {
                j = i + 1; 
                continue;
            }
            for (j = i; j < 123; ++j) {
                if (appear[j]) break;
            }
            segs.emplace_back(i, j - 1);
        }
        string ans = generate(merge(segs));
        segs.emplace_back(33, 47);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.emplace_back(58, 64);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.emplace_back(91, 96);
        update(ans, generate(merge(segs)));
        segs.pop_back();

        segs.emplace_back(33, 47);
        segs.emplace_back(58, 64);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.pop_back();
        segs.emplace_back(33, 47);
        segs.emplace_back(91, 96);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.pop_back();
        segs.emplace_back(58, 64);
        segs.emplace_back(91, 96);
        update(ans, generate(merge(segs)));
        segs.pop_back();
        segs.pop_back();

        segs.emplace_back(33, 47);
        segs.emplace_back(58, 64);
        segs.emplace_back(91, 96);
        update(ans, generate(merge(segs)));

        return "^" + ans;
    }();

    update(positive, negative);

    if (positive == "^") positive = "^!";
    cout << "%[" << positive << "]" << endl;
}
