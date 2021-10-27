
def sigma(n):
  return (2 * (n ** 6) + 6 * (n ** 5) + 5 * (n ** 4) - (n ** 2)) // 12

p, q = list(map(int, input().split(' ')))

def get_dec_days():
  L = 1
  R = 10 ** 10
  while L < R:
    M = (L + R) // 2
    if q * (M ** 5) >= p:
      R = M
    else:
      L = M + 1
  return L

def get_low(dd):
  return -(-p * dd + q * sigma(dd) - p)

dd = get_dec_days()
low = get_low(dd - 1)

def check(x):
  def OK(D):
    return -D * p + q * sigma(D) >= 10 ** 99 - x

  L = dd
  R = 10 ** 50
  while L < R:
    M = (L + R) // 2
    if (OK(M)):
      R = M
    else:
      L = M + 1
  return L

# L = low, R = 10 ** 90
# while L < R:
#   M = (L + R) // 2
#   req_days = check(M)
#   if req_days == -1:
#     L = M + 1
#   else:
#     R = M
# 
# d = check(L)

print(low)
print(check(low))
