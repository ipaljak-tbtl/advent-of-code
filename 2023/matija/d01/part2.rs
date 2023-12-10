const NUMS: [&str; 9] = [
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
];

fn solve(reader: impl std::io::BufRead) -> u32 {
    reader
        .lines()
        .map(Result::unwrap)
        .map(|mut line| {
            for (i, &num) in NUMS.iter().enumerate() {
                line = line.replace(num, &format!("{num}{}{num}", i + 1));
            }

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
    fn test_d01p2() {
        let reader = BufReader::new(File::open("d01/test_input2.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 281);
    }
}
