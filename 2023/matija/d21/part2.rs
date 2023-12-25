const DS: [(i64, i64); 4] = [(1, 0), (-1, 0), (0, 1), (0, -1)];

fn solve(reader: impl std::io::BufRead) -> i64 {
    let map: Vec<Vec<char>> = reader
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let n = map.len() as i64;

    let mut open = std::collections::VecDeque::new();
    open.push_back((n / 2, n / 2, 0));

    let mut visited = std::collections::HashSet::<(i64, i64)>::new();

    let (mut full_even, mut full_odd, mut out_even, mut out_odd) = (0, 0, 0, 0);

    while let Some((i, j, dist)) = open.pop_front() {
        if dist % 2 == 0 {
            full_even += 1;
            if dist > n / 2 {
                out_even += 1;
            }
        } else {
            full_odd += 1;
            if dist > n / 2 {
                out_odd += 1;
            }
        }

        for (di, dj) in DS {
            let (ni, nj) = (i + di, j + dj);
            if !visited.contains(&(ni, nj))
                && ni >= 0
                && nj >= 0
                && ni < n
                && nj < n
                && map[ni as usize][nj as usize] == '.'
            {
                open.push_back((ni, nj, dist + 1));
                visited.insert((ni, nj));
            }
        }
    }

    let n = 26501365 / n;

    n * n * full_even + (n + 1) * (n + 1) * full_odd - (n + 1) * out_odd + n * out_even
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d21p2() {
        let reader = BufReader::new(File::open("d21/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 470149874997513);
    }
}
