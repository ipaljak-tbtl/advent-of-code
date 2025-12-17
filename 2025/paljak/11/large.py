lines = open("in", "r").readlines()

G = {}
for line in lines:
    tokens = line.strip().split()
    node = tokens[0][:-1]
    G[node] = tokens[1:]

memo = {}

def dfs(node, seen_dac=False, seen_fft=False):
    seen_dac |= node == "dac"
    seen_fft |= node == "fft"

    key = (node, seen_dac, seen_fft)
    if key in memo:
        return memo[key]

    if node == "out":
        return 1 if (seen_dac and seen_fft) else 0

    ret = 0
    for nxt in G.get(node, []):
        ret += dfs(nxt, seen_dac, seen_fft)

    memo[key] = ret
    return ret

print(dfs("svr"))
