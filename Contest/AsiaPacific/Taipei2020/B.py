w = list(map(int, input().strip().split(' ')))

mid = ['', '+', '-', '*']

st = set()

def f(v):
    global st
    for i in mid:
        for j in mid:
            for k in mid:
                if i == '' and j == '' and k == '':
                    continue
                e = f'{v[0]}{i}{v[1]}{j}{v[2]}{k}{v[3]}'
                val = eval(e)
                if val >= 0:
                    #print(e, eval(e))
                    st.add(val)

for i in range(4):
    for j in range(4):
        for k in range(4):
            for l in range(4):
                if i == j or i == k or i == l or j == k or j == l or k == l:
                    continue
                f([w[i], w[j], w[k], w[l]])

# print(st)
print(len(st))
