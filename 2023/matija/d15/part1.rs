fn hash(input: &str) -> u32 {
    input
        .chars()
        .fold(0, |acc, c| ((acc + c as u32) * 17) % 256)
}

fn solve(reader: impl std::io::BufRead) -> u32 {
    let line = reader.lines().next().unwrap().unwrap();
    line.split(',').map(hash).sum()
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d15p1() {
        let reader = BufReader::new(File::open("d15/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 1320);
    }
}
