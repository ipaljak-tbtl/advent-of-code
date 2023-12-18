use std::collections::{BTreeSet, HashSet};

/// `(cost, consecutive_direction, idx_direction, (i, j))`
type State = (u32, u8, usize, (i32, i32));

const DIRS: [(i32, i32); 4] = [(0, 1), (1, 0), (0, -1), (-1, 0)];

fn solve(reader: impl std::io::BufRead) -> u32 {
    let lines = reader.lines().map(Result::unwrap);
    let map: Vec<Vec<u32>> = lines
        .map(|line| line.chars().map(|c| c.to_digit(10).unwrap()).collect())
        .collect();

    let (h, w) = (map.len() as i32, map[0].len() as i32);

    let forbidden = [2, 3, 0, 1];

    let mut open = BTreeSet::<State>::new();
    let mut visited = HashSet::<(i32, i32, u8, usize)>::new();

    open.insert((map[0][1], 1, 0, (0, 1)));
    open.insert((map[1][0], 1, 1, (1, 0)));

    while let Some((cost, cons, idx_dir, (i, j))) = open.pop_first() {
        if i == h - 1 && j == w - 1 && cons >= 4 {
            return cost;
        }

        visited.insert((i, j, cons, idx_dir));

        for (i_dir, &(di, dj)) in DIRS.iter().enumerate() {
            if i_dir == forbidden[idx_dir] {
                continue;
            }

            let (i_new, j_new) = (i + di, j + dj);
            let new_cons = if i_dir == idx_dir { cons + 1 } else { 1 };
            if i_new < 0
                || j_new < 0
                || i_new >= h
                || j_new >= w
                || new_cons > 10
                || (cons < 4 && i_dir != idx_dir)
                || visited.contains(&(i_new, j_new, new_cons, i_dir))
            {
                continue;
            }

            let new_cost = cost + map[i_new as usize][j_new as usize];

            open.insert((new_cost, new_cons, i_dir, (i_new, j_new)));
        }
    }

    0
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d17p2_1() {
        let reader = BufReader::new(File::open("d17/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 94);
    }

    #[test]
    fn test_d17p2_2() {
        let reader = BufReader::new(File::open("d17/test_input2.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 71);
    }
}
