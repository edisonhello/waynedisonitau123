
def godp(val):
    print('godp', val)

#    while i <= val: i *= 2
#    i //= 2
#
#    while i >= 1:
#        j = 0
#        v = i
#        while v <= val: 
#            v *= 3
#            j += 1
#
#        v /= 3
#        j -= 1
#
#        while j >= 0:
#            pass

    i = 0

#    dp[0] = dp[1] = 1
    vv = val
    x = 0
    y = 0
    while vv > 0:
        x += 1
        vv //= 2
    vv = val
    while vv > 0:
        y += 1
        vv //= 3

    dp = [0 for _ in range(1 << y)]
    ndp = [0 for _ in range(1 << y)]
    dp[0] = dp[1] = 1

    for i in range(x + 1):
        for j in range(y + 1):
            if i == 0 and j == 0:
                continue
            print(i, j, (2 ** i) * (3 ** j))
            for z in range(1 << y):
                if dp[z] == 0:
                    continue
                a = z >> (y - 1) & 1
                b = z & 1
                if not a and not b and (2 ** i) * (3 ** j) <= val:
                    ndp[(z * 2 % (1 << y)) + 1] += dp[z]
                ndp[(z * 2 % (1 << y))] += dp[z]
            print("i = ", i, " j = ", j, " dp = ", dp)
            for z in range(1 << y):
                dp[z] = ndp[z]
                ndp[z] = 0
    s = 0
    for z in range(1 << y):
        s += dp[z]
    return (val, s)

    # while True:
    #     if 2 ** i > val: break
    #     v = 2 ** i
    #     if i == 0: v *= 3
    #     for j in range(0 if i else 1, 13):
    #         for z in range(2 ** 13):
    #             if dp[z] == 0:
    #                 continue

    #         take[j], free[j] = (0 if v > val else free[j] + (free[j - 1] if j else 0)), take[j] + free[j] + take[j - 1] + free[j - 1]
    #         v *= 3
    #     i += 1
    #     print(take, free)

    # return (val, take[29] + free[29])

n = int(input())

vals = []

val = 1
while val <= n:
    val2 = val
    while val2 <= n:
        vals.append(val2)
        val2 *= 3
    val *= 2

cutpoint = []
for val in vals:
    cutpoint.append(godp(val))

cutpoint.sort()
anss = [0 for i in range(n + 1)]
it = 0

print(cutpoint)

for i in range(1, n + 1):
    if it + 1 < len(cutpoint) and cutpoint[it + 1][0] == i: it += 1
    anss[i] = cutpoint[it][1]

print(anss)

ans = 1
for i in range(1, n + 1):
    if i % 2 == 0 or i % 3 == 0: continue
    ans *= anss[n // i]

print(ans - 1)
