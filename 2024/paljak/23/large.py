import networkx as nx


def read_graph_from_file(filename):
    G = nx.Graph()
    with open(filename, "r") as f:
        for line in f:
            line = line.strip()
            if line:
                node1, node2 = line.split("-")
                G.add_edge(node1, node2)
    return G


cliques = nx.find_cliques(read_graph_from_file("in"))
max_clique = max(cliques, key=len)
print(",".join(sorted(max_clique)))
