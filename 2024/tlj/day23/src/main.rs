use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::{self, BufRead},
};

fn find_tris<'a>(
    graph: &HashMap<&'a str, HashSet<&'a str>>,
    start: &'a str,
) -> HashSet<[&'a str; 3]> {
    let mut res = HashSet::new();

    let mut stack = VecDeque::new();
    stack.push_front((vec![], start));

    while let Some((path, node)) = stack.pop_back() {
        if path.len() == 3 && path[path.len() - 3] == node {
            let mut new_tri = [path[path.len() - 2], path[path.len() - 1], node];
            new_tri.sort();
            res.insert(new_tri);
            continue;
        }

        if path.len() > 3 {
            continue;
        }

        if path.contains(&node) {
            continue;
        }

        for n in graph[node].iter() {
            let mut new_path = path.clone();
            new_path.push(node);

            stack.push_front((new_path, *n));
        }
    }

    res
}

fn bron_kerbosch_v2<'a>(
    r: &HashSet<&'a str>,
    p: &mut HashSet<&'a str>,
    x: &mut HashSet<&'a str>,
    g: &HashMap<&'a str, HashSet<&'a str>>,
    cliques: &mut Vec<Vec<&'a str>>,
) {
    if p.is_empty() && x.is_empty() {
        if r.len() > 2 {
            let mut clique: Vec<&str> = r.iter().cloned().collect();
            clique.sort();
            cliques.push(clique);
        }
        return;
    }

    // Choose a pivot with the maximum degree in P ∪ X
    let pivot = p
        .union(x)
        .max_by_key(|v| g.get(**v).map_or(0, |neighbors| neighbors.len()))
        .cloned();

    if let Some(pivot_vertex) = pivot {
        let neighbors = g.get(pivot_vertex).cloned().unwrap_or_default();
        let candidates: Vec<&str> = p.difference(&neighbors).cloned().collect();

        for v in candidates {
            // New R is R ∪ {v}
            let mut new_r = r.clone();
            new_r.insert(v);

            // New P is P ∩ N(v)
            let neighbors_v = g.get(&v).cloned().unwrap_or_default();
            let mut new_p = p
                .intersection(&neighbors_v)
                .cloned()
                .collect::<HashSet<&str>>();

            // New X is X ∩ N(v)
            let mut new_x = x
                .intersection(&neighbors_v)
                .cloned()
                .collect::<HashSet<&str>>();

            // Recursive call
            bron_kerbosch_v2(&new_r, &mut new_p, &mut new_x, g, cliques);

            // Move v from P to X
            p.remove(&v);
            x.insert(v);
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle.lines().map(|l| l.unwrap()).collect::<Vec<_>>();

    let conns = lines
        .iter()
        .map(|l| {
            let l = l.split('-').collect::<Vec<_>>();
            let c1 = l[0];
            let c2 = l[1];

            (c1, c2)
        })
        .collect::<HashSet<_>>();

    let mut graph = HashMap::new();

    for (c0, c1) in conns {
        let g = graph.entry(c0).or_insert_with(HashSet::new);
        g.insert(c1);

        let g = graph.entry(c1).or_insert_with(HashSet::new);
        g.insert(c0);
    }

    let mut tris = HashSet::new();

    for c in graph.keys() {
        let new_tris = find_tris(&graph, c);
        tris.extend(new_tris);
    }

    let p1 = tris
        .iter()
        .filter(|t| t.iter().any(|c| c.starts_with('t')))
        .count();

    println!("p1: {}", p1);

    let r: HashSet<&str> = HashSet::new();
    let mut p: HashSet<&str> = graph.keys().cloned().collect();
    let mut x: HashSet<&str> = HashSet::new();

    let mut cliques = Vec::new();
    bron_kerbosch_v2(&r, &mut p, &mut x, &graph, &mut cliques);

    cliques.sort_by_key(|g| g.len());

    let mut p2 = cliques.pop().unwrap().into_iter().collect::<Vec<_>>();

    p2.sort();

    let p2 = p2.join(",");

    println!("p2: {}", p2);
}
