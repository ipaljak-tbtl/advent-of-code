fn solve(reader: impl std::io::BufRead) -> u64 {
    let mut lines = reader.lines().map(Result::unwrap);

    let t: u64 = lines.next().unwrap().split_whitespace().collect::<String>()[5..]
        .parse()
        .unwrap();
    let d: u64 = lines.next().unwrap().split_whitespace().collect::<String>()[9..]
        .parse()
        .unwrap();

    let (mut low, mut high) = (1, t / 2);
    while low < high {
        let mid = low + (high - low) / 2;
        if mid * (t - mid) > d {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    t - 2 * low + 1
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d06p2() {
        let reader = BufReader::new(File::open("d06/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 71503);
    }
}
