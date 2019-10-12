fin = open("binary.in", "r")
fout = open("binary.out", "w")
 
n = int(fin.readline())
 
prepow = [[0 for i in range(21)] for j in range(1005)]
tab = [[0 for i in range(21)] for j in range(21)]
npow = [0 for i in range(1005)]
 
def solve(x, n):
    l = 0
    r = n
    status = [0 for i in range(n)]
    while l < r - 1:
        m = (l + r) // 2;
        if x >= m:
            status[m] = -1
            l = m
        else:
            status[m] = 1
            r = m
    status[l] = 999
    mbig = 0
    msml = 0
    abtr = 0
    for i in range(n):
        if status[i] == -1:
            msml += 1
        if status[i] == 1:
            mbig += 1
        if status[i] == 0:
            abtr += 1
    return tab[msml][mbig] * npow[abtr]
 
 
npow[0] = 1
for i in range(1, n + 1):
    npow[i] = npow[i - 1] * n
 
for i in range(n + 1):
    prepow[i][0] = 1
    for j in range(1, 21):
        prepow[i][j] = prepow[i][j - 1] * i
 
for a in range(21):
    for b in range(21):
        tab[a][b] = 0
        for i in range(1, n + 1):
            tab[a][b] += prepow[i][a] * prepow[n - i][b]
 
ans = 0
for i in range(n):
    ans += solve(i, n)
 
fout.write(str(ans))
