#include <bits/stdc++.h>
using namespace std;

struct node {
    bool leaf;
    map<string, node*> child;
    string value;
    node() : leaf(0) {}
};

node *parse_KSON(const vector<string> &KSON, int L, int R) {
    // cerr << "parse_KSON at " << L << " " << R << endl;
    node *res = new node();
    while (L <= R) {
        int cr = L;
        // cerr << "KSON[cr] = " << KSON[cr] << endl;
        if (KSON[cr].back() == '{') {
            // cerr << "child case " << endl;
            int colo = KSON[cr].find(":");
            string key = KSON[cr].substr(1, colo - 1 - 1);
            int dep = 0;
            while (true) {
                if (KSON[cr].back() == '{') ++dep;
                if (KSON[cr][0] == '}') --dep;
                if (dep == 0) break;
                ++cr;
            }
            res->child[key] = parse_KSON(KSON, L + 1, cr - 1);
            L = cr + 1;
        } else {
            // cerr << "leaf case" << endl;
            int colo = KSON[cr].find(":");
            string key = KSON[cr].substr(1, colo - 1 - 1);
            // cerr << "leaf name " << key << endl;
            node *tmp = new node();
            res->child[key] = tmp;
            tmp->leaf = true;
            if (KSON[cr].back() == ',')
                tmp->value = KSON[cr].substr(colo + 2, (int)KSON[cr].size() - 2 - colo - 2);
            else 
                tmp->value = KSON[cr].substr(colo + 2, (int)KSON[cr].size() - 1 - colo - 2);
            ++L;
        }
    }
    return res;
}

string NO_ANSWER = "<>{}<{>>{>{<__>+<+>}><_>+";

string dfs(node *now, string &s, int idx, bool use_space = false) {
    // cerr << "dfs " << s << " " << idx << " at now = " << now << endl;
    if (!now) return NO_ANSWER;
    if ((int)s.size() <= idx) {
        if (now->leaf) return now->value;
        /* if (!use_space) {
            auto it = now->child.find("");
            if (it != now->child.end()) return dfs(it->second, s, idx, true);
        } */
        return NO_ANSWER;
    }
    // for (auto p : now->child) cerr << "child: " << p.first << " : " << p.second << endl;
    int dot = s.find(".", idx);
    if (dot == -1) dot = s.size();
    string key = s.substr(idx, dot - idx);
    // cerr << "next key: " << key << endl;
    auto it = now->child.find(key);
    // if (it == now->child.end()) cerr << "can't find next child " << endl;
    if (it == now->child.end()) return NO_ANSWER;
    return dfs(it->second, s, dot + 1);
}

string minify(string s) {
    string ns;
    bool no = 0;
    for (char c : s) {
        if (no) ns += c;
        else if (!isspace(c)) ns += c;
        if (c == '\"') no = !no;
    }
    return ns;
}

void minify(vector<string> &KSON) {
    for (auto &s : KSON) {
        string ns;
        bool no = 0;
        for (char c : s) {
            if (no) ns += c;
            else if (!isspace(c)) ns += c;
            if (c == '\"') no = !no;
        }
        s = ns;
    }
}

void parse_table(node *root, vector<string> v) {
    int n = v.size() / 2, m = -1;
    vector<int> col_sep;
    // cerr << "meow" << endl;
    // cerr << "v[0] = " << v[0] << endl;
    for (int i = 0; i < (int)v[0].size(); ++i) if (v[0][i] == '+') col_sep.push_back(i);
    // cerr << "meowmeow " << col_sep.size() << endl;
    m = col_sep.size() - 1;
    vector<vector<string>> table(n, vector<string>(m));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        // cerr << i << " " << j << endl;
        table[i][j] = v[i * 2 + 1].substr(col_sep[j] + 1, col_sep[j + 1] - col_sep[j] - 1);
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        string s = table[i][j];
        reverse(s.begin(), s.end());
        while (s.size() && s.back() == ' ') s.pop_back();
        reverse(s.begin(), s.end());
        while (s.size() && s.back() == ' ') s.pop_back();
        s += ".";
        if (s.substr(0, 6) == "Value:") {
            // cerr << "go dfs" << endl;
            string res = dfs(root, s, 6);
            // cerr << "out dfs" << endl;
            if (res != NO_ANSWER) table[i][j] = res;
        }
    }
    vector<int> width;
    for (int j = 0; j < m; ++j) {
        int mx = 0;
        for (int i = 0; i < n; ++i) mx = max(mx, (int)table[i][j].size());
        width.push_back(mx);
    }
    auto print_sep = [&] () -> void {
        cout << "+";
        for (int i : width) {
            while (i--) cout << "-";
            cout << "+";
        }
        cout << '\n';
    };
    print_sep();
    for (int i = 0; i < n; ++i) {
        cout << "|";
        for (int j = 0; j < m; ++j) {
            cout << table[i][j];
            for (int k = 0; k < width[j] - (int)table[i][j].size(); ++k) cout << " ";
            cout << "|";
        }
        cout << '\n';
        print_sep();
    }
}

vector<string> reline(string s) {
    vector<string> v;
    string cur;
    auto push = [&] () {
        v.push_back(cur);
        cur = "";
    };
    bool nospace = true;
    for (char c : s) {
        if (c == '\"') nospace ^= 1;
        if (nospace && isspace(c)) continue;

        if (c == ',') {
            if (cur == "") v.back() += ",";
            else {
                cur += ",";
                push();
            }
        }
        else if (c == '{') {
            cur += c;
            push();
        } else if (c == '}') {
            if (cur != "") push();
            cur += c;
            push();
        } else {
            cur += c;
        }
    }
    if (cur != "") push();
    return v;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    vector<string> v, KSON;
    string s;
    while (getline(cin, s)) v.push_back(s);
    {
        s = "";
        vector<string> tmp;
        int st = 0;
        while (v[st][0] != '+') ++st;
        for (int i = 0; i < st; ++i) s += v[i];
        for (int i = st; i < (int)v.size(); ++i) tmp.push_back(v[i]);
        KSON = reline(s);
        v.swap(tmp);
    }

    // cerr << "new KSON = " << endl;
    // for (string s : KSON) cerr << s << endl;
    // cerr << " = new KSON " << endl;
    
    minify(KSON);
    // cerr << "out minify" << endl;
    node *root = parse_KSON(KSON, 1, KSON.size() - 2);
    // cerr << "go to parse table " << endl;
    parse_table(root, v);
}
