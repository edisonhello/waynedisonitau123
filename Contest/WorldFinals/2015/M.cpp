#include <bits/stdc++.h>
using namespace std;

struct Window {
    int x1, x2, y1, y2;
};

bool Collision(Window &a, Window &b) {
    int x1 = max(a.x1, b.x1);
    int x2 = min(a.x2, b.x2);
    int y1 = max(a.y1, b.y1);
    int y2 = min(a.y2, b.y2);
    if (x1 > x2 || y1 > y2) return 0;
    return 1;
}

bool Include(Window &w, int x, int y) {
    return w.x1 <= x && x <= w.x2 && w.y1 <= y && y <= w.y2;
}

int main() {
    int xmx, ymx; cin >> xmx >> ymx;

    auto Outside = [&] (Window &w) -> bool {
        return w.x1 < 0 || w.y1 < 0 || w.x2 >= xmx || w.y2 >= ymx;
    };

    vector<Window> ws;

    int ci = 0;
    string s; while (cin >> s) {
        ++ci;
        if (s == "OPEN") {
            int x, y, w, h; cin >> x >> y >> w >> h;

            Window now{x, x + w - 1, y, y + h - 1};
            bool col = 0;
            for (auto &w : ws) if (Collision(w, now)) { col = 1; break; }
            if (Outside(now)) col = 1;

            if (col) {
                cout << "Command " << ci << ": OPEN - window does not fit" << endl;
            } else {
                ws.push_back(now);
            }
        } else if (s == "RESIZE") {
            int x, y, w, h; cin >> x >> y >> w >> h;

            int wid = -1;
            for (int i = 0; i < (int)ws.size(); ++i) {
                if (Include(ws[i], x, y)) {
                    wid = i;
                    break;
                }
            }

            if (wid == -1) {
                cout << "Command " << ci << ": RESIZE - no window at given position" << endl;
            } else {
                Window now = ws[wid];
                now.x2 = now.x1 + w - 1;
                now.y2 = now.y1 + h - 1;

                bool col = 0;
                for (int i = 0; i < (int)ws.size(); ++i) if (i != wid && Collision(now, ws[i])) col = 1;
                if (Outside(now)) col = 1;

                if (col) {
                    cout << "Command " << ci << ": RESIZE - window does not fit" << endl;
                } else {
                    ws[wid] = now;
                }

            }
        } else if (s == "CLOSE") {
            int x, y; cin >> x >> y;

            int wid = -1;
            for (int i = 0; i < (int)ws.size(); ++i) {
                if (Include(ws[i], x, y)) {
                    wid = i;
                    break;
                }
            }

            if (wid == -1) {
                cout << "Command " << ci << ": CLOSE - no window at given position" << endl;
            } else {
                ws.erase(ws.begin() + wid);
            }
        } else {
            assert(s == "MOVE");

            int x, y, dx, dy; cin >> x >> y >> dx >> dy;

            int wid = -1;
            for (int i = 0; i < (int)ws.size(); ++i) {
                if (Include(ws[i], x, y)) {
                    wid = i;
                    break;
                }
            }

            if (wid == -1) {
                cout << "Command " << ci << ": MOVE - no window at given position" << endl;
            } else {
                if (dx > 0) {
                    vector<vector<pair<int, int>>> touches(ws.size()); // [dist, who]

                    for (int i = 0; i < (int)ws.size(); ++i) {
                        for (int j = 0; j < (int)ws.size(); ++j) {
                            if (i == j) continue;
                            if (ws[i].y2 < ws[j].y1 || ws[j].y2 < ws[i].y1) continue;
                            if (ws[j].x2 < ws[i].x1) continue;

                            int d = ws[j].x1 - ws[i].x2 - 1;
                            touches[i].emplace_back(d, j);
                        }

                        touches[i].emplace_back(xmx - ws[i].x2 - 1, -1);

                        sort(touches[i].begin(), touches[i].end());
                    }

                    int moved = 0;
                    set<int> pushing; pushing.insert(wid);
                    vector<int> it(ws.size(), 0);
                    vector<int> current_moved(ws.size(), 0);

                    while (moved < dx) {
                        int next_touch = -2;
                        int next_touch_d = INT_MAX;
                        int next_touch_by = -1;
                        
                        for (int i : pushing) {
                            while (it[i] < (int)touches[i].size()) {
                                if (pushing.count(touches[i][it[i]].second)) ++it[i];
                                else {
                                    if (touches[i][it[i]].first - current_moved[i] >= dx - moved) ;
                                    else if (touches[i][it[i]].first - current_moved[i] < next_touch_d) {
                                        next_touch = touches[i][it[i]].second;
                                        next_touch_d = touches[i][it[i]].first - current_moved[i];
                                        next_touch_by = i;
                                    }
                                    break;
                                }
                            }
                        }

                        if (next_touch == -2) {
                            for (int i : pushing) 
                                current_moved[i] += dx - moved;
                            moved = dx;
                        } else {
                            for (int i : pushing) 
                                current_moved[i] += next_touch_d;
                            moved += next_touch_d;
                            if (next_touch == -1) break;
                            else pushing.insert(next_touch);
                        }
                    }

                    if (moved < dx) {
                        cout << "Command " << ci << ": MOVE - moved " << moved << " instead of " << dx << endl;
                    }

                    for (int i : pushing) {
                        ws[i].x1 += current_moved[i];
                        ws[i].x2 += current_moved[i];
                    }
                } else if (dx < 0) {
                    dx = -dx;
                    vector<vector<pair<int, int>>> touches(ws.size()); // [dist, who]

                    for (int i = 0; i < (int)ws.size(); ++i) {
                        for (int j = 0; j < (int)ws.size(); ++j) {
                            if (i == j) continue;
                            if (ws[i].y2 < ws[j].y1 || ws[j].y2 < ws[i].y1) continue;
                            if (ws[i].x2 < ws[j].x1) continue;

                            int d = ws[i].x1 - ws[j].x2 - 1;
                            touches[i].emplace_back(d, j);
                        }

                        touches[i].emplace_back(ws[i].x1, -1);

                        sort(touches[i].begin(), touches[i].end());
                    }

                    int moved = 0;
                    set<int> pushing; pushing.insert(wid);
                    vector<int> it(ws.size(), 0);
                    vector<int> current_moved(ws.size(), 0);

                    while (moved < dx) {
                        int next_touch = -2;
                        int next_touch_d = INT_MAX;
                        int next_touch_by = -1;
                        
                        for (int i : pushing) {
                            while (it[i] < (int)touches[i].size()) {
                                if (pushing.count(touches[i][it[i]].second)) ++it[i];
                                else {
                                    if (touches[i][it[i]].first - current_moved[i] >= dx - moved) ;
                                    else if (touches[i][it[i]].first - current_moved[i] < next_touch_d) {
                                        next_touch = touches[i][it[i]].second;
                                        next_touch_d = touches[i][it[i]].first - current_moved[i];
                                        next_touch_by = i;
                                    }
                                    break;
                                }
                            }
                        }

                        if (next_touch == -2) {
                            for (int i : pushing) 
                                current_moved[i] += dx - moved;
                            moved = dx;
                        } else {
                            for (int i : pushing) 
                                current_moved[i] += next_touch_d;
                            moved += next_touch_d;
                            if (next_touch == -1) break;
                            else pushing.insert(next_touch);
                        }
                    }

                    if (moved < dx) {
                        cout << "Command " << ci << ": MOVE - moved " << moved << " instead of " << dx << endl;
                    }

                    for (int i : pushing) {
                        ws[i].x1 -= current_moved[i];
                        ws[i].x2 -= current_moved[i];
                    }
                } else if (dy > 0) {
                    vector<vector<pair<int, int>>> touches(ws.size()); // [dist, who]

                    for (int i = 0; i < (int)ws.size(); ++i) {
                        for (int j = 0; j < (int)ws.size(); ++j) {
                            if (i == j) continue;
                            if (ws[i].x2 < ws[j].x1 || ws[j].x2 < ws[i].x1) continue;
                            if (ws[j].y2 < ws[i].y1) continue;

                            int d = ws[j].y1 - ws[i].y2 - 1;
                            touches[i].emplace_back(d, j);
                        }

                        touches[i].emplace_back(ymx - ws[i].y2 - 1, -1);

                        sort(touches[i].begin(), touches[i].end());
                    }

                    int moved = 0;
                    set<int> pushing; pushing.insert(wid);
                    vector<int> it(ws.size(), 0);
                    vector<int> current_moved(ws.size(), 0);

                    while (moved < dy) {
                        int next_touch = -2;
                        int next_touch_d = INT_MAX;
                        int next_touch_by = -1;
                        
                        for (int i : pushing) {
                            while (it[i] < (int)touches[i].size()) {
                                if (pushing.count(touches[i][it[i]].second)) ++it[i];
                                else {
                                    if (touches[i][it[i]].first - current_moved[i] >= dy - moved) ;
                                    else if (touches[i][it[i]].first - current_moved[i] < next_touch_d) {
                                        next_touch = touches[i][it[i]].second;
                                        next_touch_d = touches[i][it[i]].first - current_moved[i];
                                        next_touch_by = i;
                                    }
                                    break;
                                }
                            }
                        }

                        if (next_touch == -2) {
                            for (int i : pushing) 
                                current_moved[i] += dy - moved;
                            moved = dy;
                        } else {
                            for (int i : pushing) 
                                current_moved[i] += next_touch_d;
                            moved += next_touch_d;
                            if (next_touch == -1) break;
                            else pushing.insert(next_touch);
                        }
                    }

                    if (moved < dy) {
                        cout << "Command " << ci << ": MOVE - moved " << moved << " instead of " << dy << endl;
                    }

                    for (int i : pushing) {
                        ws[i].y1 += current_moved[i];
                        ws[i].y2 += current_moved[i];
                    }
                } else if (dy < 0) {
                    dy = -dy;
                    vector<vector<pair<int, int>>> touches(ws.size()); // [dist, who]

                    for (int i = 0; i < (int)ws.size(); ++i) {
                        for (int j = 0; j < (int)ws.size(); ++j) {
                            if (i == j) continue;
                            if (ws[i].x2 < ws[j].x1 || ws[j].x2 < ws[i].x1) continue;
                            if (ws[i].y2 < ws[j].y1) continue;

                            int d = ws[i].y1 - ws[j].y2 - 1;
                            touches[i].emplace_back(d, j);
                        }

                        touches[i].emplace_back(ws[i].y1, -1);

                        sort(touches[i].begin(), touches[i].end());
                    }

                    int moved = 0;
                    set<int> pushing; pushing.insert(wid);
                    vector<int> it(ws.size(), 0);
                    vector<int> current_moved(ws.size(), 0);

                    while (moved < dy) {
                        int next_touch = -2;
                        int next_touch_d = INT_MAX;
                        int next_touch_by = -1;
                        
                        for (int i : pushing) {
                            while (it[i] < (int)touches[i].size()) {
                                if (pushing.count(touches[i][it[i]].second)) ++it[i];
                                else {
                                    if (touches[i][it[i]].first - current_moved[i] >= dy - moved) ;
                                    else if (touches[i][it[i]].first - current_moved[i] < next_touch_d) {
                                        next_touch = touches[i][it[i]].second;
                                        next_touch_d = touches[i][it[i]].first - current_moved[i];
                                        next_touch_by = i;
                                    }
                                    break;
                                }
                            }
                        }

                        if (next_touch == -2) {
                            for (int i : pushing) 
                                current_moved[i] += dy - moved;
                            moved = dy;
                        } else {
                            for (int i : pushing) 
                                current_moved[i] += next_touch_d;
                            moved += next_touch_d;
                            if (next_touch == -1) break;
                            else pushing.insert(next_touch);
                        }
                    }

                    if (moved < dy) {
                        cout << "Command " << ci << ": MOVE - moved " << moved << " instead of " << dy << endl;
                    }

                    for (int i : pushing) {
                        ws[i].y1 -= current_moved[i];
                        ws[i].y2 -= current_moved[i];
                    }
                }
            }
        }
    }

    cout << ws.size() << " window(s):" << endl;
    for (auto w : ws) {
        cout << w.x1 << ' ' << w.y1 << ' ' << w.x2 - w.x1 + 1 << ' ' << w.y2 - w.y1 + 1 << '\n';
    }
}

