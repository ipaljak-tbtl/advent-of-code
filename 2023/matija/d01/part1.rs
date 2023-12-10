fn solve(reader: impl std::io::BufRead) -> u32 {
    reader
        .lines()
        .map(Result::unwrap)
        .map(|line| {
            let mut ns = line.chars().filter_map(|c| c.to_digit(10));

            let first = ns.next().unwrap();
            let last = ns.last().unwrap_or(first);

            10 * first + last
        })
        .sum()
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d01p1() {
        let reader = BufReader::new(File::open("d01/test_input1.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 142);
    }
}
