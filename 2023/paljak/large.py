tokens = open("in", "r").read().strip().split(",")


def h(token):
    ret = 0
    for c in token:
        ret += ord(c)
        ret *= 17
        ret %= 256
    return ret


buckets = [dict() for _ in range(256)]
for token in tokens:
    parts = token.strip("-").split("=")
    if len(parts) == 1:
        buckets[h(parts[0])].pop(parts[0], 0)
    else:
        buckets[h(parts[0])][parts[0]] = int(parts[1])

sol = 0
for i, bucket in enumerate(buckets, 1):
    for j, coef in enumerate(bucket.values(), 1):
        sol += i * j * coef

print(sol)
