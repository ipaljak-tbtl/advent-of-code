use std::collections::HashSet;

fn solve(reader: impl std::io::BufRead) -> u32 {
    let mut result = 0u32;

    for line in reader.lines().map(Result::unwrap) {
        let mut winning = HashSet::<u32>::new();
        let mut chosen = HashSet::<u32>::new();

        let mut on_winning = true;
        for part in line.split_whitespace().skip(2) {
            if part == "|" {
                on_winning = false;
                continue;
            }

            if on_winning {
                winning.insert(part.parse().unwrap());
            } else {
                chosen.insert(part.parse().unwrap());
            }
        }

        let hits = winning.intersection(&chosen).count();
        if hits == 0 {
            continue;
        }

        result += 1 << (hits - 1);
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
    fn test_d04p1() {
        let reader = BufReader::new(File::open("d04/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 13);
    }
}
