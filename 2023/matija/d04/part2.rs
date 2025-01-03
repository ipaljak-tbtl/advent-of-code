use std::collections::{HashMap, HashSet};

fn solve(reader: impl std::io::BufRead) -> u32 {
    let mut result = 0u32;

    let mut copies = HashMap::<usize, u32>::new();

    for (i, line) in reader.lines().map(Result::unwrap).enumerate() {
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

        let i_total = 1 + *copies.get(&i).unwrap_or(&0);

        result += i_total;

        for h in 1..=hits {
            *copies.entry(i + h).or_default() += i_total;
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
    fn test_d04p2() {
        let reader = BufReader::new(File::open("d04/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 30);
    }
}
