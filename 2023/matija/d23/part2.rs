use std::collections::{HashMap, HashSet};

const DS: [(i32, i32); 4] = [(1, 0), (-1, 0), (0, 1), (0, -1)];

fn solve(reader: impl std::io::BufRead) -> u32 {
    let map: Vec<Vec<char>> = reader
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let (h, w) = (map.len() as i32, map[0].len() as i32);

    let si = 0;
    let sj = map[0].iter().position(|&c| c == '.').unwrap() as i32;
    let ei = (map.len() - 1) as i32;
    let ej = map[ei as usize].iter().position(|&c| c == '.').unwrap() as i32;

    let mut g = HashMap::<(i32, i32), HashMap<(i32, i32), u32>>::new();

    for (i, row) in map.iter().enumerate() {
        for (j, &c) in row.iter().enumerate() {
            if c == '#' {
                continue;
            }
            let (i, j) = (i as i32, j as i32);
            let mut next = HashMap::<(i32, i32), u32>::new();
            for (di, dj) in DS {
                let (ni, nj) = (i + di, j + dj);
                if ni < 0 || nj < 0 || ni >= h || nj >= w || map[ni as usize][nj as usize] == '#' {
                    continue;
                }
                next.insert((ni, nj), 1);
            }
            g.insert((i, j), next);
        }
    }

    let to_rm: Vec<_> = g
        .iter()
        .filter(|(_, v)| v.len() == 2)
        .map(|(&k, _)| k)
        .collect();

    for v in to_rm {
        let next: Vec<_> = g.remove(&v).unwrap().into_iter().collect();
        let ((v1, c1), (v2, c2)) = (next[0], next[1]);

        let n1 = g.get_mut(&v1).unwrap();
        n1.remove(&v);
        n1.insert(v2, c1 + c2);

        let n2 = g.get_mut(&v2).unwrap();
        n2.remove(&v);
        n2.insert(v1, c1 + c2);
    }

    let mut open = vec![((si, sj), 0, HashSet::new())];

    let mut max_path = 0;

    while let Some(((i, j), dist, mut visited)) = open.pop() {
        if i == ei && j == ej {
            if dist > max_path {
                max_path = dist;
            }
            continue;
        }

        visited.insert((i, j));

        for (&n, &c) in g.get(&(i, j)).unwrap() {
            if !visited.contains(&n) {
                open.push((n, dist + c, visited.clone()));
            }
        }
    }

    max_path
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d23p2() {
        let reader = BufReader::new(File::open("d23/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 154);
    }
}
