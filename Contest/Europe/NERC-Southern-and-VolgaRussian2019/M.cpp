#include <bits/stdc++.h>
using namespace std;

using Vint = vector<int>;
using Result = vector<pair<Vint, Vint>>;

void print_status(int n, bitset<5005> *dr) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << dr[i][j];
        }
        cout << endl;
    }
}
void check_answer(int n, bitset<5005> *dr) {
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        if (i == j || i == j + 1) assert(dr[i][j] == 0);
        else assert(dr[i][j] == 1);
    }
}
void draw_answer(const Result &ans, bitset<5005> *dr) {
    for (auto &p : ans) {
        for (int x : p.first) for (int y : p.second) 
            dr[x][y] = 1;
    }
}

void print_answer(int n, const Result &ans) {
    bitset<5005> dr[5005];
    draw_answer(ans, dr);
    print_status(n, dr);
}
void check_answer(int n, const Result &ans) {
    cerr << ans.size() << endl;
    assert((int)ans.size() <= 50);
    bitset<5005> dr[5005];
    draw_answer(ans, dr);
    print_status(n, dr);
    check_answer(n, dr);
}

Result solve_base(int n) {
    if (n <= 2) return Result();
    if (n == 3) {
        Result ans;
        ans.emplace_back(Vint{1}, Vint{2});
        ans.emplace_back(Vint{2}, Vint{3});
        ans.emplace_back(Vint{3}, Vint{1});
        return ans;
    }
    if (n == 4) {
        Result ans;
        ans.emplace_back(Vint{1}, Vint{2, 3});
        ans.emplace_back(Vint{2}, Vint{3, 4});
        ans.emplace_back(Vint{3}, Vint{1, 4});
        ans.emplace_back(Vint{4}, Vint{1, 2});
        return ans;
    }
    if (n == 5) {
        Result ans;
        ans.emplace_back(Vint{1}, Vint{2, 3, 4});
        ans.emplace_back(Vint{2}, Vint{3, 4, 5});
        ans.emplace_back(Vint{3}, Vint{1, 4, 5});
        ans.emplace_back(Vint{4}, Vint{1, 2, 5});
        ans.emplace_back(Vint{5}, Vint{1, 2, 3});
        return ans;
    }
    if (n % 2 == 1) {
        Result ans = solve_base(n / 2);
        for (auto &p : ans) {
            int z = p.first.size();
            for (int i = 0; i < z; ++i) p.first.push_back(p.first[i] + n / 2);
            z = p.second.size();
            for (int i = 0; i < z; ++i) p.second.push_back(p.second[i] + n / 2);
        }
        vector<int> tx, ty;
        tx.clear(), ty.clear();
        for (int i = 2; i <= n - 1; ++i) tx.push_back(i);
        ty.push_back(n);
        ans.emplace_back(tx, ty); // 1
        // print_answer(n, ans); cout << endl;
        tx.clear(), ty.clear();
        for (int i = 1; i <= n / 2 + 1; ++i) tx.push_back(i);
        for (int i = n / 2 + 2; i <= n - 1; ++i) ty.push_back(i);
        ans.emplace_back(tx, ty); // 2 
        // print_answer(n, ans); cout << endl;
        tx.clear(), ty.clear();
        tx.push_back(1); tx.push_back(2); tx.push_back(n - 1);
        ty.push_back(n / 2); ty.push_back(n / 2 + 1);
        ans.emplace_back(tx, ty); // 3
        // print_answer(n ,ans); cout << endl;
        tx.clear(), ty.clear();
        tx.push_back(n);
        for (int i = 1; i <= n - 2; ++i) ty.push_back(i);
        ans.emplace_back(tx, ty); // 4
        // print_answer(n, ans); cout << endl;
        tx.clear(), ty.clear();
        for (int i = n / 2 + 1; i <= n; ++i) tx.push_back(i);
        for (int i = 1; i <= n / 2 - 1; ++i) ty.push_back(i);
        ans.emplace_back(tx, ty); // 5
        // print_answer(n, ans); cout << endl;
        return ans;
        // vector<int> bot, rig, v1 = {1}, vn1 = {n - 1}, vn = {n};
        // for (int i = 1; i <= n - 2; ++i) bot.push_back(i);
        // for (int i = 2; i <= n - 1; ++i) rig.push_back(i);
        // ans.emplace_back(vn, bot);
        // ans.emplace_back(rig, vn);
        // ans.emplace_back(v1, vn1);
        return ans;
    } else {
        Result ans = solve_base(n / 2);
        for (auto &p : ans) {
            int z = p.first.size();
            for (int i = 0; i < z; ++i) p.first.push_back(p.first[i] + n / 2);
            z = p.second.size();
            for (int i = 0; i < z; ++i) p.second.push_back(p.second[i] + n / 2);
        }
        vector<int> tx, ty;
        tx.clear(), ty.clear();
        for (int i = n / 2 + 1; i <= n; ++i) tx.push_back(i);
        for (int i = 1; i <= n / 2 - 1; ++i) ty.push_back(i);
        ans.emplace_back(tx, ty); // 1
        tx.clear(), ty.clear();
        for (int i = 2; i <= n / 2 + 1; ++i) tx.push_back(i);
        for (int i = n / 2 + 2; i <= n; ++i) ty.push_back(i);
        ans.emplace_back(tx, ty); // 2 
        tx.clear(), ty.clear();
        tx.push_back(1); tx.push_back(2); tx.push_back(n);
        ty.push_back(n / 2); ty.push_back(n / 2 + 1);
        ans.emplace_back(tx, ty); // 3
        return ans;
    }
}

Result solve(int n) {
    Result ans = solve_base(n);
    vector<int> v1 = {1}, vn = {n};
    ans.emplace_back(v1, vn);
    return ans;
}

Vint cut(Vint &v, int n) {
    Vint r;
    for (int i : v) if (i <= n) r.push_back(i);
    return r;
}
Result cut(Result &ans, int n) {
    Result tmp;
    for (auto &p : ans) {
        p.first = cut(p.first, n);
        p.second = cut(p.second, n);
        if (p.first.empty() || p.second.empty());
        else tmp.push_back(p);
    }
    return tmp;
}

int main() {
    int n; cin >> n; 
    Result ans = solve(5000);
    ans = cut(ans, n);
    // vector<pair<vector<int>, vector<int>>> ans = solve(n);
    cout << ans.size() << endl;
    for (auto &p : ans) {
        cout << p.first.size();
        for (int i : p.first) cout << ' ' << i;
        cout << '\n';
        cout << p.second.size();
        for (int i : p.second) cout << ' ' << i;
        cout << '\n';
    }

    // check_answer(n, ans);
}
