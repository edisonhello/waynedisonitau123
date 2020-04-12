print(1000, 1000)

print((1 << 1000) - 1, end=' ')
for i in range(1000):
    print((1 << 999) - 1, end=' ')
print()
for i in range(1000):
    print(i, (1 << 1000) - 1)

