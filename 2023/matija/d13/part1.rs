fn solve(reader: impl std::io::BufRead) -> usize {
    let mut lines = reader
        .lines()
        .map(Result::unwrap)
        .chain(std::iter::once(String::new()))
        .peekable();

    let mut result = 0;

    while lines.peek().is_some() {
        let mut patterns: Vec<Vec<char>> = Vec::new();

        let mut line = lines.next().unwrap();
        while !line.is_empty() {
            patterns.push(line.chars().collect());
            line = lines.next().unwrap();
        }

        for i in 1..patterns.len() {
            let mut diffs = 0;
            for j in 0..std::cmp::min(i, patterns.len() - i) {
                for idx in 0..patterns[0].len() {
                    if patterns[i - j - 1][idx] != patterns[i + j][idx] {
                        diffs += 1;
                    }
                }
            }
            if diffs == 0 {
                result += 100 * i;
                break;
            }
        }

        for i in 1..patterns[0].len() {
            let mut diffs = 0;
            for j in 0..std::cmp::min(i, patterns[0].len() - i) {
                for row in &patterns {
                    if row[i - j - 1] != row[i + j] {
                        diffs += 1;
                    }
                }
            }
            if diffs == 0 {
                result += i;
                break;
            }
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
    fn test_d13p1() {
        let reader = BufReader::new(File::open("d13/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 405);
    }
}
