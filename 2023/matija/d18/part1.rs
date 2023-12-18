fn solve(reader: impl std::io::BufRead) -> i32 {
    let mut area = 0;
    let mut circ = 0;

    let (mut pi, mut pj) = (0, 0);

    for line in reader.lines().map(Result::unwrap) {
        let parts: Vec<&str> = line.split_whitespace().collect();
        let amount: i32 = parts[1].parse().unwrap();

        let (i, j) = match parts[0] {
            "U" => (pi - amount, pj),
            "D" => (pi + amount, pj),
            "R" => (pi, pj + amount),
            "L" => (pi, pj - amount),
            _ => unreachable!(),
        };

        area += pi * j - i * pj;
        circ += amount;

        (pi, pj) = (i, j);
    }

    area.abs() / 2 + circ / 2 + 1
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d18p1() {
        let reader = BufReader::new(File::open("d18/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 62);
    }
}
