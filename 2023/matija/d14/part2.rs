use std::collections::HashMap;

const CYCLES: usize = 1_000_000_000;

fn rotate_clockwise<T: Copy>(matrix: &mut Vec<Vec<T>>) {
    let n = matrix.len();

    for i in 0..(n / 2) {
        for j in i..(n - i - 1) {
            let temp = matrix[i][j];
            matrix[i][j] = matrix[n - 1 - j][i];
            matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
            matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
            matrix[j][n - 1 - i] = temp;
        }
    }
}

fn north(positions: &mut Vec<Vec<char>>) {
    let n = positions.len();

    for j in 0..n {
        for mut i in 0..n {
            if positions[i][j] != 'O' {
                continue;
            }

            positions[i][j] = '.';

            while i > 0 && positions[i - 1][j] == '.' {
                i -= 1;
            }

            positions[i][j] = 'O';
        }
    }
}

fn load(positions: &Vec<Vec<char>>) -> usize {
    let n = positions.len();

    let mut load = 0;

    for (i, row) in positions.iter().enumerate() {
        for c in row {
            if c == &'O' {
                load += n - i;
            }
        }
    }

    load
}

fn cycle(positions: &mut Vec<Vec<char>>) {
    for _ in 0..4 {
        north(positions);
        rotate_clockwise(positions);
    }
}

fn solve(reader: impl std::io::BufRead) -> usize {
    let mut positions: Vec<Vec<char>> = reader
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let mut cycle_end = 0;

    let mut visited = HashMap::<Vec<Vec<char>>, usize>::new();

    while cycle_end == 0 || !visited.contains_key(&positions) {
        visited.insert(positions.clone(), cycle_end);
        cycle(&mut positions);
        cycle_end += 1
    }

    let cycle_start = visited.get(&positions).unwrap();

    for _ in 0..((CYCLES - cycle_start) % (cycle_end - cycle_start)) {
        cycle(&mut positions);
    }

    load(&positions)
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d14p2() {
        let reader = BufReader::new(File::open("d14/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 64);
    }
}
