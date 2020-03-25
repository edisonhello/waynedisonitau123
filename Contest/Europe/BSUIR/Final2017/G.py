import math

n, m = list(map(int, input().strip().split(' ')))

n -= 1
m -= 1

g = math.gcd(n, m)

x = n // g
y = m // g

print((g * x * y - x * y + (x + 1) * (y + 1) // 2) % 1000000000000000009)

