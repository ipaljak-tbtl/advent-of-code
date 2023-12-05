fn solve(reader: impl std::io::BufRead) -> u64 {
    let mut lines = reader.lines().map(Result::unwrap);

    let mut values: Vec<u64> = lines
        .next()
        .unwrap()
        .split_whitespace()
        .skip(1)
        .map(|c| c.parse().unwrap())
        .collect();

    let mut maps = Vec::<(u64, u64, u64)>::new();

    for line in lines.skip(2).chain(std::iter::once(String::new())) {
        if line.is_empty() {
            for value in &mut values {
                for (ds, ss, len) in maps.iter().copied() {
                    if *value >= ss && *value < ss + len {
                        *value = ds + *value - ss;
                        break;
                    }
                }
            }
            maps.clear();
        } else if !line.ends_with(':') {
            let mut ns = line.split_whitespace().map(|c| c.parse().unwrap());
            maps.push((ns.next().unwrap(), ns.next().unwrap(), ns.next().unwrap()));
        }
    }

    *values.iter().min().unwrap()
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d05p1() {
        let reader = BufReader::new(File::open("d05/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 35);
    }
}
