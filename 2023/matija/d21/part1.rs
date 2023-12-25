use std::collections::HashSet;

const DS: [(i32, i32); 4] = [(1, 0), (-1, 0), (0, 1), (0, -1)];

fn solve(reader: impl std::io::BufRead) -> u32 {
    let mut map: Vec<Vec<char>> = reader
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let n = map.len() as i32;

    map[n as usize / 2][n as usize / 2] = '.';

    let mut plots = HashSet::<(i32, i32)>::new();
    plots.insert((n / 2, n / 2));

    for _ in 0..64 {
        let mut new_plots = HashSet::<(i32, i32)>::new();
        for (i, j) in plots {
            for (di, dj) in DS {
                let (ni, nj) = (i + di, j + dj);
                if ni < 0 || nj < 0 || ni >= n || nj >= n || map[ni as usize][nj as usize] != '.' {
                    continue;
                }
                new_plots.insert((ni, nj));
            }
        }
        plots = new_plots;
    }

    plots.len() as u32
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d21p1() {
        let reader = BufReader::new(File::open("d21/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 42);
    }
}
