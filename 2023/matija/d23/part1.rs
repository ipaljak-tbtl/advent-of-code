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

    let forbidden = [1, 0, 3, 2];

    let mut open = vec![(si + 1, sj, 0, 1)];

    let mut max_path = 0;

    while let Some((i, j, i_dir, dist)) = open.pop() {
        if i == ei && j == ej {
            if dist > max_path {
                max_path = dist;
            }
            continue;
        }

        let next = match map[i as usize][j as usize] {
            '^' => vec![1],
            '>' => vec![2],
            '<' => vec![3],
            'v' => vec![0],
            _ => vec![0, 1, 2, 3],
        };

        for d in next {
            let (di, dj) = DS[d];
            let (ni, nj) = (i + di, j + dj);
            if ni < 0
                || nj < 0
                || ni >= h
                || nj >= w
                || d == forbidden[i_dir]
                || map[ni as usize][nj as usize] == '#'
            {
                continue;
            }

            open.push((ni, nj, d, dist + 1));
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
    fn test_d23p1() {
        let reader = BufReader::new(File::open("d23/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 94);
    }
}
