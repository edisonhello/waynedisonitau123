import sys

n = int(input())

tabs = [[0 for i in range(n + 1)] for j in range(n + 1)]
frac = [0 for i in range(n + 1)]

frac[0] = 1
for i in range(1, n + 1):
    frac[i] = frac[i - 1] * i

for i in range(0, n + 1):
    tabs[i][0] = 1
    for j in range(1, i + 1):
        tabs[i][j] = tabs[i - 1][j] + tabs[i - 1][j - 1]

dp = [[0 for i in range(n + 1)] for j in range(n + 1)]
dp2 = [[[0 for i in range(n + 1)] for j in range(n + 1)] for k in range(n + 1)]

dp[1][0] = 1
for i in range(n + 1):
    dp2[0][0][i] = 1

for i in range(2, n + 1):
    for j in range(1, n + 1):
        dp[i - 1][j] += dp[i - 1][j - 1]
    for p in range(i - 1):
        for m in range(1, i + 1):
            for k in range(n + 1):
                dp2[i - 1][m][k] += dp2[p][m - 1][k] * dp[i - 1 - p][k] * tabs[i - 1][p]
    ans = 0
    for k in range(n + 1):
        # print("dp2[%d][%d][%d] = %d" % (i - 1, k, k, dp2[i - 1][k][k]))
        dp[i][k] = dp2[i - 1][k][k] // frac[k]
    for j in range(n + 1):
        ans += dp[i][j]
    print("ans[%d] = \"%d\"" % (i, ans))
    sys.stderr.write("i = %d\n" % i)
            
