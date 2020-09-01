def Parse(x):
    v = x.split('.')
    if len(v) == 1:
        return int(v[0]) * 1000
    [a, b] = v
    a = int(a)
    b = int(b)
    if len(v[1]) == 1:
        return a * 1000 + b * 100
    if len(v[1]) == 2:
        return a * 1000 + b * 10
    if len(v[1]) == 3:
        return a * 1000 + b * 1

t = int(input())

for T in range(1, t + 1):
    n = int(input())
    a = []
    for i in range(n):
        s = input()
        [x, y] = s.split(':')
        x = Parse(x)
        y = Parse(y)
        a.append([x, x + y])

    a.sort(key=lambda i: i[0] / i[1])

    tot = [0, 1]
    cnt = 0

    for i in a:
        tot = [tot[0] * i[1] + tot[1] * i[0], tot[1] * i[1]]
        if tot[0] >= tot[1]:
            break
        cnt += 1

    print(f"Case #{T}: {cnt}")

