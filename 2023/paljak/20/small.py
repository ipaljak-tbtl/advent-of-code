from queue import Queue

lines = open("in", "r").readlines()
# lines = open("small_in", "r").readlines()

G, flip_flop, conjunction = {}, {}, {}
lo, hi = 0, 0


def parse_input(lines):
    global G, flip_flop, conjunction

    for line in lines:
        node, neigh = line.strip().split(" -> ")
        neigh = neigh.split(", ")

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
    global G, flip_flop, conjunction, lo, hi

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


parse_input(lines)

for _ in range(1000):
    lo += 1
    button()

print(lo, hi)
print(lo * hi)
