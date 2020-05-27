import random

n = 3
print("".join([str(chr(ord('a') + random.randint(0, 2))) for i in range(n)]))
