#include <bits/stdc++.h>
using namespace std;

struct Depart {
    int ppcnt;
    map<int, int> id_bd;
    map<int, set<int>> bd_id;
    map<int, string> id_name;
    int insert(string name, int bd) {
        int id = ++ppcnt;
        id_bd[id] = bd;
        bd_id[bd].insert(id);
        id_name[id] = name;
        return id;
    }
    pair<string, int> erase(int id) {
        pair<string, int> rt;
        rt.first = id_name[id];
        rt.second = id_bd[id];
        id_name.erase(id);
        id_bd.erase(id);
        bd_id[rt.second].erase(id);
        if (bd_id[rt.second].empty()) bd_id.erase(rt.second);
        return rt;
    }
    string get_old() {
        if (bd_id.empty()) return "Vacant";
        auto it = bd_id.begin();
        return id_name[*it->second.begin()];
    }
    Depart() : ppcnt(0) {}
};

map<int, Depart> dep_info;

map<tuple<int, int, int>, string> global_name;

string get_global_old() {
    if (global_name.empty()) return "Vacant";
    return global_name.begin()->second;
}

int main() {
    int n; scanf("%d", &n); while (n--) {
        int t; scanf("%d", &t);
        int dp; scanf("%d", &dp);
        if (t == 1) {
            char name[15] = {0}; scanf("%s", name);
            int y, m, d; scanf("%d:%d:%d", &d, &m, &y);
            int bd = y * 10000 + m * 100 + d;
            int id = dep_info[dp].insert(string(name), bd);
            global_name[make_tuple(bd, dp, id)] = string(name);
        } else {
            int id; scanf("%d", &id);
            pair<string, int> info = dep_info[dp].erase(id);
            global_name.erase(make_tuple(info.second, dp, id));
        }
        printf("%s %s\n", get_global_old().c_str(), dep_info[dp].get_old().c_str());
    }
}
