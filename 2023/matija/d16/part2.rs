use std::collections::{BTreeSet, HashMap, HashSet};

const DIRS: [(i32, i32); 4] = [(0, 1), (1, 0), (0, -1), (-1, 0)];

fn simulate(layout: &Vec<Vec<char>>, start: ((i32, i32), usize)) -> usize {
    // position plus the index of the direction the beam came from
    let mut progress = BTreeSet::<((i32, i32), usize)>::new();

    let mut visited = HashSet::<((i32, i32), usize)>::new();

    let mut trans = HashMap::<char, [Vec<usize>; 4]>::new();
    trans.insert('.', [vec![0], vec![1], vec![2], vec![3]]);
    trans.insert('/', [vec![3], vec![2], vec![1], vec![0]]);
    trans.insert('\\', [vec![1], vec![0], vec![3], vec![2]]);
    trans.insert('-', [vec![0], vec![0, 2], vec![2], vec![0, 2]]);
    trans.insert('|', [vec![1, 3], vec![1], vec![1, 3], vec![3]]);

    progress.insert(start);

    while !progress.is_empty() {
        let ((i, j), dir_idx) = progress.pop_first().unwrap();

        if i < 0 || j < 0 || i as usize >= layout.len() || j as usize >= layout[0].len() {
            continue;
        }

        visited.insert(((i, j), dir_idx));

        for &new_dir in &trans.get(&layout[i as usize][j as usize]).unwrap()[dir_idx] {
            let (di, dj) = DIRS[new_dir];
            let new_state = ((i + di, j + dj), new_dir);
            if !visited.contains(&new_state) {
                progress.insert(new_state);
            }
        }
    }

    visited.iter().map(|s| s.0).collect::<HashSet<_>>().len()
}

fn solve(reader: impl std::io::BufRead) -> usize {
    let lines = reader.lines().map(Result::unwrap);
    let layout: Vec<Vec<char>> = lines.map(|line| line.chars().collect()).collect();

    let mut max = 0;

    let n = layout.len() as i32;
    for i in 0..n {
        max = max.max(simulate(&layout, ((i, 0), 0)));
        max = max.max(simulate(&layout, ((i, n - 1), 2)));
        max = max.max(simulate(&layout, ((0, i), 1)));
        max = max.max(simulate(&layout, ((n - 1, i), 3)));
    }

    max
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d16p2() {
        let reader = BufReader::new(File::open("d16/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 51);
    }
}