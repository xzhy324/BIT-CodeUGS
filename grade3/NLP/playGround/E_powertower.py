from pprint import pprint
while True:
    a = [2]
    p = int(input())
    for i in range(0,50):
        ans = a[-1] % p
        print(ans)
        a.append(2**a[-1])
