fn solve(reader: impl std::io::BufRead) -> usize {
    let mut positions: Vec<Vec<char>> = reader
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let mut result = 0;

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

            result += n - i;
        }
    }

    result
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d14p1() {
        let reader = BufReader::new(File::open("d14/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 136);
    }
}
