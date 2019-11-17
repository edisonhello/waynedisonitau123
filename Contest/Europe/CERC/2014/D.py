
from math import gcd

n, g = 0, []
ans, v = [], []

def connect(i, j):
    global g
    dx = g[i][0] - g[j][0]
    dy = g[i][1] - g[j][1]
    r = g[i][2] + g[j][2]
    # print(i, j, dx, dy, r)
    return dx ** 2 + dy ** 2 == r ** 2

def dfs(now, nu, nd):
    global n, g, ans, v
    # print(now, nu, nd)
    ans[now] = [nu, nd]
    
    v[now] = True
    for i in range(n): 
        if not v[i]:
            if connect(now, i):
                dfs(i, int(-nu * g[now][2]), int(nd * g[i][2]))

def solve():
    global n, g, ans, v
    n = int(input())
    g = [list(map(int, input().split(' '))) for _ in range(n)]
    ans = [[0, 0] for _ in range(n)]
    v = [False for _ in range(n)]

    dfs(0, 1, 1)

    for i in range(n):
        if ans[i][0] == 0: 
            print("not moving")
            continue

        z = gcd(ans[i][0], ans[i][1])
        ans[i][0] /= z
        ans[i][1] /= z
        if ans[i][1] > 1: print(str(int(abs(ans[i][0]))) + "/" + str(int(abs(ans[i][1]))), end=' ')
        else: print(str(int(abs(ans[i][0]))), end=' ')
        print("clockwise" if ans[i][0] * ans[i][1] > 0 else "counterclockwise")
            
    

t = int(input())

for _ in range(t): solve()
