fn solve(reader: impl std::io::BufRead) -> u64 {
    let mut lines = reader.lines().map(Result::unwrap);

    let first_line = lines.next().unwrap();
    let mut value_iter = first_line
        .split_whitespace()
        .skip(1)
        .map(|c| c.parse().unwrap());

    let mut values = Vec::<(u64, u64)>::new();
    while let Some(left) = value_iter.next() {
        let len = value_iter.next().unwrap();
        values.push((left, left + len - 1))
    }

    let mut maps = Vec::<(u64, u64, u64)>::new();
    for line in lines.skip(2).chain(std::iter::once(String::new())) {
        if line.is_empty() {
            for (left, right) in &mut values {
                for (ds, ss, len) in maps.iter().copied() {
                    if *left >= ss && *left < ss + len {
                        *left = ds + *left - ss;
                        break;
                    }
                }

                for (ds, ss, len) in maps.iter().copied() {
                    if *right >= ss && *right < ss + len {
                        *right = ds + *right - ss;
                        break;
                    }
                }
            }
            maps.clear();
        } else if !line.ends_with(':') {
            let mut ns = line.split_whitespace().map(|c| c.parse().unwrap());
            let (ds, ss, len) = (ns.next().unwrap(), ns.next().unwrap(), ns.next().unwrap());
            maps.push((ds, ss, len));

            let mut new_interval = None;
            for (left, right) in &mut values {
                if ss > *left && ss <= *right {
                    new_interval = Some((ss, *right));
                    *right = ss - 1;
                    break;
                }
            }

            if let Some(new_interval) = new_interval {
                values.push(new_interval);
            }

            let mut new_interval = None;
            for (left, right) in &mut values {
                if ss + len >= *left + 1 && ss + len < *right + 1 {
                    new_interval = Some((*left, ss + len - 1));
                    *left = ss + len;
                    break;
                }
            }

            if let Some(new_interval) = new_interval {
                values.push(new_interval);
            }
        }
    }

    values.iter().min().unwrap().0
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d05p2() {
        let reader = BufReader::new(File::open("d05/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 46);
    }
}
