m, n, d = map(int, input().split())
c = 1
for i in range(n):
    c *= (m - i)

for i in range(n):
    c //= (n - i)

while c % d == 0: c //= d
print(c % d)
