fn solve(reader: impl std::io::BufRead) -> i64 {
    let mut result = 0i64;

    for line in reader.lines().map(Result::unwrap) {
        let mut seq: Vec<i64> = line
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();

        let mut len = seq.len();

        while seq.iter().take(len).any(|&x| x != 0) {
            for i in 0..(len - 1) {
                seq[i] = seq[i + 1] - seq[i];
            }
            len -= 1;
        }

        result += seq.iter().sum::<i64>();
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
    fn test_d09p1() {
        let reader = BufReader::new(File::open("d09/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 114);
    }
}
