
cnt = [0 for i in range(10)]
for i in range(1, 100):
    ii = 2 ** i
    s = str(ii)
    c = int(s[0])
    cnt[c] += 1

print(cnt)
