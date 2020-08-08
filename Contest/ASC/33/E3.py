import sys

n = int(input())

dp = [[0 for i in range(n + 1)] for j in range(n + 1)]
dp2 = [[[0 for i in range(n + 1)] for j in range(n + 1)] for k in range(n + 1)]
for i in range(n + 1):
    dp2[i][0][0] = 1

dp[1][0] = 1

def fpow(a, n):
    res = 1
    while n > 0:
        if n % 2 == 1:
            res = res * a
        a = a * a
        n >>= 1
    return res

tabs = [[0 for i in range(n + 1)] for j in range(n + 1)]
ways = [[0 for i in range(n + 1)] for j in range(n + 1)]
frac = [0 for i in range(n + 1)]

frac[0] = 1
for i in range(1, n + 1):
    frac[i] = frac[i - 1] * i

for i in range(0, n + 1):
    tabs[i][0] = 1
    for j in range(1, i + 1):
        tabs[i][j] = tabs[i - 1][j] + tabs[i - 1][j - 1]

for i in range(0, n + 1):
    ways[0][i] = 1

for i in range(1, n + 1):
    for j in range(1, i + 1):
        if i % j != 0:
            continue
        ways[i][j] = 1
        x = i
        for k in range(i // j):
            ways[i][j] = ways[i][j] * tabs[x][j]
            x -= j
        ways[i][j] //= frac[i // j]
        # print("ways[%d][%d] = %d" % (i, j, ways[i][j]))

dp3 = [[[0 for a in range(n + 1)] for b in range(n + 1)] for c in range(n + 1)]

for i in range(2, n + 1):
    # for j in range(n + 1):
    #     print("dp[%d][%d] = %d\n" % (i - 1, j, dp[i - 1][j]))
    for j in range(1, n + 1):
        dp[i - 1][j] += dp[i - 1][j - 1]
    for p in range(n + 1):
        for x in range(n + 1):
            for k in range(n + 1):
                if dp2[p][x][k] == 0:
                    continue
                for t in range(n + 1):
                    if x + t > n or k + t * (i - 1) > n:
                        break
                    dp3[p][x + t][k + t * (i - 1)] += dp2[p][x][k] * fpow(dp[i - 1][p], t) * ways[t * (i - 1)][t] * tabs[k + t * (i - 1)][t * (i - 1)]
    for p in range(n + 1):
        for x in range(n + 1):
            for k in range(n + 1):
                dp2[p][x][k] = dp3[p][x][k]
                dp3[p][x][k] = 0

    ans = 0
    for p in range(n + 1):
        dp[i][p] = dp2[p][p][i - 1]
        ans += dp[i][p]
    print("ans[%d] = \"%d\"" % (i, ans))
    sys.stderr.write("i = %d\n" % i)
