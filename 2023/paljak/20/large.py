from queue import Queue
from Crypto.Util.number import GCD

lines = open("in", "r").readlines()

G, flip_flop, conjunction = {}, {}, {}
lo, hi = 0, 0

rx_parent = None


def parse_input(lines):
    global G, flip_flop, conjunction, rx_parent

    for line in lines:
        node, neigh = line.strip().split(" -> ")
        neigh = neigh.split(", ")

        if "rx" in neigh:
            rx_parent = node[1:]

        for nxt in neigh:
            if nxt not in G:
                G[nxt] = {}

        G[node[node[0] in "&%" :]] = neigh

        if node[0] == "%":
            flip_flop[node[1:]] = False

        if node[0] == "&":
            conjunction[node[1:]] = {}

    for node, neigh in G.items():
        for nxt in neigh:
            if nxt in conjunction:
                conjunction[nxt][node] = False


def button():
    global G, flip_flop, conjunction, lo, hi, rx_parent, tick, cycles

    tick += 1
    lo += len(G["broadcaster"])
    q = Queue()
    for nxt in G["broadcaster"]:
        q.put(("broadcaster", nxt, False))

    while not q.empty():
        prev, node, val = q.get()

        assert node != "broadcaster"

        if node in flip_flop and val:
            continue

        nxt_val = False
        if node in flip_flop:
            flip_flop[node] = not flip_flop[node]
            nxt_val = flip_flop[node]

        if node in conjunction:
            conjunction[node][prev] = val
            nxt_val = not all(past_val for past_val in conjunction[node].values())

        for nxt in G[node]:
            q.put((node, nxt, nxt_val))
            hi += nxt_val
            lo += not nxt_val
            if nxt_val and nxt == rx_parent and node not in cycles:
                cycles[node] = tick


parse_input(lines)

tick = 0
cycles = {}

while len(cycles) != 4:
    button()

sol = 1
for cycle in cycles.values():
    sol = sol * cycle // GCD(sol, cycle)

print(sol)
