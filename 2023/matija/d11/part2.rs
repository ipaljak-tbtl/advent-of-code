fn solve(reader: impl std::io::BufRead) -> u64 {
    let mut total = 0;
    let img: Vec<Vec<char>> = reader
        .lines()
        .map(|line| {
            let mut row = Vec::new();
            for c in line.unwrap().chars() {
                if c == '#' {
                    total += 1;
                }
                row.push(c)
            }
            row
        })
        .collect();

    let mut result = 0;

    let mut cnt = 0;
    for row in &img {
        result += cnt * (total - cnt);
        let mut found = false;
        for &e in row {
            if e == '#' {
                cnt += 1;
                found = true;
            }
        }
        if !found {
            result += 999999 * cnt * (total - cnt)
        }
    }

    let mut cnt = 0;
    for j in 0..img[0].len() {
        result += cnt * (total - cnt);
        let mut found = false;
        for row in &img {
            if row[j] == '#' {
                cnt += 1;
                found = true;
            }
        }
        if !found {
            result += 999999 * cnt * (total - cnt)
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
    fn test_d11p2() {
        let reader = BufReader::new(File::open("d11/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 82000210);
    }
}
