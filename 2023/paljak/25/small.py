import random
import networkx as nx

lines = open("in", "r").readlines()
# lines = open("small_in", "r").readlines()

G = nx.Graph()
nodes = set()

for line in lines:
    node = line.split(":")[0]
    adj = line.split(":")[1].split()
    nodes.add(node)

    for nxt in adj:
        nodes.add(nxt)
        G.add_edge(node, nxt, capacity=1.0)

while True:
    n1 = random.choice(list(nodes))
    n2 = random.choice(list(nodes))

    if n1 == n2:
        continue

    cut, partition = nx.minimum_cut(G, n1, n2)

    if cut > 3:
        continue

    print(len(partition[0]) * len(partition[1]))
    break
