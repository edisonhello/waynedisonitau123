N = 60 + 1
M = [0] * N
F = [0] * N
 
def calc(n, m):
    res = 1
    for i in range(m):
        res *= (n + m - 1 - i)
    for i in range(m):
        res //= (m - i)
    return res
 
F[1] = 1
M[1] = 1
 
mu = [0 for i in range(N)]
v = [0 for i in range(N)]
p = []
 
mu[1] = 1
for i in range(2, N):
    if v[i] == 0:
        mu[i] = -1
        p.append(i)
    for j in range(len(p)):
        if p[j] * i >= N:
            break
        mu[i * p[j]] = -mu[i]
        v[i * p[j]] = 1
        if i % p[j] == 0:
            mu[i * p[j]] = 0
            break
 
 
print('M[1] = "1";')
for i in range(2, N):
    dp = [[0 for j in range(N)] for k in range(N)]
    dp[0][0] = 1
    for j in range(1, i):
        for k in range(i):
            for t in range(k + 1):
                if t * j <= k:
                    dp[j][k] += dp[j - 1][k - t * j] * calc(M[j], t)
    F[i] = dp[i - 1][i - 1]
    for t in range(1, i + 1):
        b = [0 for x in range(N)]
        for j in range(1, t + 1):
            if t % j == 0 and i % (t // j) == 0:
                dp = [[0 for _ in range(N)] for __ in range(N)]
                dp[0][0] = 1
                for v in range(1, j + 1):
                    for k in range(1, (i // (t // j)) + 1):
                        for z in range(1, i + 1):
                            if k - z >= 0:
                                dp[v][k] += dp[v - 1][k - z] * F[z]
                b[j] = dp[j][i // (t // j)]
        add = 0
        a = [0 for _ in range(N)]
        for v in range(1, t + 1):
            a[v] = 0
            for d in range(1, v + 1):
                if v % d == 0:
                    a[v] += mu[d] * b[v // d]
            if t % v == 0:
                add += a[v] // v
        M[i] += add
    print('M[%d] = "%d";' % (i, M[i]))
