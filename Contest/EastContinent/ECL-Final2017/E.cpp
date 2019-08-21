#include <bits/stdc++.h>
using namespace std;

vector<string> mp;

struct Position {
    int x, y;
    Position(int x = 0, int y = 0): x(x), y(y) {}
    bool is_spike() { return mp[x][y] == '|'; }
    bool is_obstacle() { return mp[x][y] == '#'; }
    uint32_t hash() {
        uint32_t h = 0;
        h ^= ((uint32_t)x * 95956) + ((uint32_t)y * 918471502);
        return h ^ (h << 2) ^ (h >> 12) ^ (h << 23);
    }
    Position operator + (const Position b) const {
        return Position(x + b.x, y + b.y);
    }
    bool operator < (const Position b) const {
        return x == b.x ? y < b.y : x < b.x;
    }
    bool operator == (const Position b) const {
        return x == b.x && y == b.y;
    }
    char operator () () const {
        return mp[x][y];
    }
};
ostream& operator << (ostream& o, Position p) {
    o << "(" << p.x << ", " << p.y << ")";
    return o;
}

struct Snake {
    deque<Position> pos;
    bool occupy(Position p) const {
        for (Position pp : pos) if (p == pp) return true;
        return false;
    }
    uint32_t hash() {
        uint32_t x = 0;
        for (Position p : pos) x ^= (x << 2) ^ (x >> 13) ^ (p.hash() ^ 919191919u);
        return x;
    }
};

struct State {
    vector<Snake> snake;
    set<Position> fruit;
    uint32_t hash() {
        uint32_t x = 0;
        for (Snake s : snake) x ^= (x << 12) ^ (x >> 11) ^ (x << 7) ^ (s.hash() * 0xdeadbeef);
        for (Position f : fruit) x ^= (x << 12) ^ (x >> 11) ^ (x << 7) ^ (f.hash() * 0xdeadbeef);
        return x;
    }

    State walk(int snake_id, Position dir) const {
        Position head = snake[snake_id].pos[0];
        Position new_head = head + dir;

        // cerr << "new_head = " << new_head << ", is_obstacle = " << new_head.is_obstacle() << endl;

        if (new_head.is_obstacle() || new_head.is_spike()) {
            State s = State();
            s.snake.push_back(Snake());
            s.snake[0].pos.push_back(Position(-123, 0));
            return s;
        }
        for (int i = 0; i < (int)snake.size(); ++i) {
            if (snake[i].occupy(new_head)) {
                State s = State();
                s.snake.push_back(Snake());
                s.snake[0].pos.push_back(Position(-123, 0));
                return s;
            }
        }

        State s = *this;
        if (s.fruit.count(new_head)) s.snake[snake_id].pos.push_front(new_head), s.fruit.erase(new_head);
        else s.snake[snake_id].pos.push_front(new_head), s.snake[snake_id].pos.pop_back();

        if (s.fruit.empty() && new_head() == 'X') s.snake.erase(s.snake.begin() + snake_id);

        return s;
    }

    bool drop() {
        bool moved = false;
        while (true) {
            moved = false;
            for (int i = 0; i < (int)snake.size(); ++i) {
                bool drop = true;
                for (Position p : snake[i].pos) {
                    Position next_pos = p + Position(1, 0);

                    if (next_pos.is_obstacle()) drop = false;
                    for (int j = 0; j < (int)snake.size(); ++j) if (i != j) {
                        if (snake[j].occupy(next_pos)) drop = false;
                    }
                    if (fruit.count(next_pos)) drop = false;
                }

                if (!drop) continue;

                for (Position p : snake[i].pos) {
                    Position next_pos = p + Position(1, 0);
                    if (next_pos.is_spike()) return false;
                }

                moved = true;

                if (fruit.empty() && (snake[i].pos[0] + Position(1, 0))() == 'X') {
                    snake.erase(snake.begin() + i);
                    continue;
                }

                for (Position &p : snake[i].pos) {
                    p = p + Position(1, 0);
                }
            }
            if (!moved) break;
        }
        return true;
    }

    vector<State> go() {
        vector<Position> dirs = {
            Position(0, 1), Position(0, -1), Position(-1, 0), Position(1, 0) };

        vector<State> ret;
        for (Position dir : dirs) {
            for (int i = 0; i < (int)snake.size(); ++i) {
                State new_state = walk(i, dir);
                if (new_state.snake[0].pos[0].x == -123) continue;
                // cerr << "new_state = " << endl;
                // new_state.print();
                if (new_state.drop()) 
                    ret.push_back(new_state);
            }
        }
        return ret;
    }

    void print() {
        vector<string> op = mp;
        for (Snake s : snake) {
            op[s.pos[0].x][s.pos[0].y] = 'A';
            for (int i = 1; i < (int)s.pos.size(); ++i) op[s.pos[i].x][s.pos[i].y] = 'a';
        }
        for (Position f : fruit) {
            op[f.x][f.y] = '@';
        }
        for (int i = 1; i < (int)op.size() - 1; ++i) {
            for (int j = 1; j < (int)op[0].size() - 1; ++j) cerr << op[i][j];
            cerr << endl;
        }
    }
};

void init() {

}

vector<string> input() {
    int n, m; cin >> n >> m;
    vector<string> v;
    v.push_back(string(m + 2, '#'));
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        v.push_back("#" + s + '#');
    }
    v.push_back(string(m + 2, '|'));
    return v;
}

pair<State, vector<string>> parse(vector<string> input) {
    State state;

    function<void(int, int)> find_snake = [&] (int nx, int ny) -> void {
        state.snake.back().pos.emplace_back(nx, ny);
        input[nx][ny] = '.';
        if (input[nx - 1][ny] == 'v') find_snake(nx - 1, ny);
        if (input[nx + 1][ny] == '^') find_snake(nx + 1, ny);
        if (input[nx][ny - 1] == '>') find_snake(nx, ny - 1);
        if (input[nx][ny + 1] == '<') find_snake(nx, ny + 1);
    };

    for (int i = 1; i < (int)input.size() - 1; ++i) {
        for (int j = 1; j < (int)input[0].size() - 1; ++j) {
            if (input[i][j] == 'R' || input[i][j] == 'G' || input[i][j] == 'B') {
                state.snake.push_back(Snake());
                find_snake(i, j);
            }
            if (input[i][j] == '@') state.fruit.insert(Position(i, j)), input[i][j] = '.';
        }
    }
    return make_pair(state, input);
}

void output(int T, int ans) {
    cout << "Case #" << T << ": " << ans << endl;
}

unordered_map<uint32_t, int> visited;

void solve(int TTT, vector<string> input) {
    visited.clear();
    State init_state;
    tie(init_state, mp) = parse(input);
    queue<State> q; q.push(init_state); visited[init_state.hash()] = 0;
    while (q.size()) {
        State state = q.front(); q.pop();

        vector<State> next_states = state.go();

        uint32_t this_hash = state.hash();
        int this_step = visited[this_hash];

        for (State &s : next_states) {
            if (s.snake.empty()) {
                output(TTT, this_step + 1);
                return;
            }

            uint32_t next_hash = s.hash();
            if (visited.count(next_hash) == 0) {
                visited[next_hash] = this_step + 1;
                q.push(s);
                // cerr << " valid new_state = " << endl;
                // s.print();
            }
        }
    }
    output(TTT, -1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        init();
        solve(T, input());
    }
}
