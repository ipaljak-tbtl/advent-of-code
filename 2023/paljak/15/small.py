tokens = open("in", "r").read().strip().split(",")


def h(token):
    ret = 0
    for c in token:
        ret += ord(c)
        ret *= 17
        ret %= 256
    return ret


print(sum([h(token) for token in tokens]))
