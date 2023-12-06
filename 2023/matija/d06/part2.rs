fn binary_search<F: Fn(u64) -> bool>(mut low: u64, mut high: u64, condition: F) -> u64 {
    while low < high {
        let mid = low + (high - low) / 2;

        if condition(mid) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    low
}

fn solve(reader: impl std::io::BufRead) -> u64 {
    let mut lines = reader.lines().map(Result::unwrap);

    let l1 = lines.next().unwrap();
    let l2 = lines.next().unwrap();

    let t: u64 = l1.split_whitespace().collect::<String>()[5..]
        .parse()
        .unwrap();
    let d: u64 = l2.split_whitespace().collect::<String>()[9..]
        .parse()
        .unwrap();

    let low = binary_search(1, t / 2, |x| x * x + d < t * x);
    let high = binary_search(t / 2, t - 1, |x| x * x + d > t * x);

    high - low
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
