import decimal

# d = Decimal()
# print()

# print(dir(decimal.Decimal()))

decimal.getcontext().prec = 14004

t = int(input())

for _ in range(t):
	setsize = int(input())
	c_set = input()

	prob = list(map(decimal.Decimal, input().split(' ')))
	prob = [0] + prob + [0]
	for i in range(len(prob)):
		prob[i] += prob[i - 1]

	char_to_prob = {}
	for i in range(len(c_set)):
		char_to_prob[c_set[i]] = [prob[i], prob[i + 1]]

	# print(char_to_prob)

	s = input()
	pp = [char_to_prob[i] for i in s]

	# print(pp)

	d1 = decimal.Decimal(1)
	d2 = decimal.Decimal(2)

	# print(decimal.Decimal(87))
	L, R = decimal.Decimal(0), decimal.Decimal(1)
	ans = ''
	for p in pp:
		RL = R - L
		L, R = (R - L) * (p[0]) + L, (R - L) * (p[1]) + L
		# print(L, R)
		while ((L * d2) >= d1 and (R * d2) >= d1) or ((L * d2) < d1 and (R * d2) < d1):
			if (L * d2) >= d1:
				ans += '1'
				L = L * d2 - d1
				R = R * d2 - d1
			else:
				ans += '0'
				L = L * d2
				R = R * d2
	print(ans)
