n = int(input())

v = []

x = 2
rd = 1
for i in range(11):
    v.append(((x + 1) ** 2 - x ** 2, 2 * x * (x + 1)))
    rd *= (x ** 2) + (x + 1) ** 2
    x += 2

ans = []

for s in range(2048):
    x = v[0][0]
    y = v[0][1]
    for i in range(1, 11):
        tx = 0
        ty = 0
        if s >> i & 1:
            tx = x * v[i][0] + y * v[i][1]
            ty = abs(x * v[i][1] - y * v[i][0])
        else:
            tx = x * v[i][1] + y * v[i][0]
            ty = abs(x * v[i][0] - y * v[i][1])
        x, y = tx, ty
    ans.append((x, y))

tans = []
for p in ans:
    if not p in tans:
        tans.append(p)

assert len(tans) >= 1000
print(rd)

for i in range(n):
    print(tans[i][0], tans[i][1])
    for j in range(i):
        assert tans[j][0] != tans[i][0] or tans[j][1] != tans[i][1]
