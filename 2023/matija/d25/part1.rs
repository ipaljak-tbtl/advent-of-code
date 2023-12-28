use std::collections::{HashMap, HashSet, VecDeque};

fn parse_input(reader: impl std::io::BufRead) -> HashMap<u32, HashSet<u32>> {
    let lines: Vec<_> = reader.lines().map(Result::unwrap).collect();

    let mut result: HashMap<u32, HashSet<u32>> = HashMap::new();
    let mut maps = HashMap::<&str, u32>::new();
    let mut cnt = 0u32;

    for line in &lines {
        let i = line.find(':').unwrap();
        let from = *maps.entry(&line[..i]).or_insert_with(|| {
            cnt += 1;
            cnt
        });

        for to in line[(i + 2)..].split_whitespace() {
            let to = *maps.entry(to).or_insert_with(|| {
                cnt += 1;
                cnt
            });

            result.entry(from).or_default().insert(to);
            result.entry(to).or_default().insert(from);
        }
    }

    result
}

fn solve(reader: impl std::io::BufRead) -> usize {
    let graph = parse_input(reader);

    let mut freqs = HashMap::<(u32, u32), u32>::new();

    for &start in graph.keys() {
        let mut open = VecDeque::new();
        open.push_back(start);

        let mut visited = HashSet::new();
        visited.insert(start);

        while let Some(c) = open.pop_front() {
            for &n in &graph[&c] {
                if visited.insert(n) {
                    open.push_back(n);
                    let e = if c < n { (c, n) } else { (n, c) };
                    *freqs.entry(e).or_default() += 1;
                }
            }
        }
    }

    let mut freqs: Vec<_> = freqs.into_iter().collect();
    freqs.sort_by_key(|f| f.1);

    let min_cut: HashSet<_> = freqs.into_iter().rev().take(3).map(|f| f.0).collect();

    let mut open = VecDeque::new();
    open.push_back(1);

    let mut visited = HashSet::new();
    visited.insert(1);

    let mut cnt = 0;

    while let Some(c) = open.pop_front() {
        cnt += 1;
        for &n in &graph[&c] {
            let e = if c < n { (c, n) } else { (n, c) };
            if !min_cut.contains(&e) && visited.insert(n) {
                open.push_back(n);
            }
        }
    }

    cnt * (graph.len() - cnt)
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    #[ignore]
    fn test_d25() {
        let reader = BufReader::new(File::open("d25/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 54);
    }
}
