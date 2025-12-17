lines = open("in", "r").readlines()

G = {}
for line in lines:
    tokens = line.strip().split()
    node = tokens[0][:-1]
    neigh = tokens[1:]
    G[node] = neigh

memo = {}

def dfs(node):
    if node == "out":
        memo[node] = 1
    if node in memo:
        return memo[node]

    ret = 0
    for nxt in G[node]:
        ret += dfs(nxt)

    memo[node] = ret
    return ret

print(dfs("you"))
