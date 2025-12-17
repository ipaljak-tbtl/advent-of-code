lines = open("in", "r").readlines()

trivial = 0
for line in lines:
    if "x" not in line:
        continue

    tokens = line.strip().split()
    a = int(tokens[0].split("x")[0])
    b = int(tokens[0].split("x")[1][:-1])

    s = sum([int(tok) for tok in tokens[1:]])

    print(a, b, s)
    trivial += (a // 3) * (b // 3) >= s

print(trivial)
