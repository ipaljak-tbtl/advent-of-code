fn solve(reader: impl std::io::BufRead) -> i64 {
    let mut area = 0;
    let mut circ = 0;

    let (mut pi, mut pj) = (0, 0);

    for line in reader.lines().map(Result::unwrap) {
        let p = line.find('#').unwrap();
        let amount = i64::from_str_radix(&line[(p + 1)..(p + 6)], 16).unwrap();

        let (i, j) = match &line[(p + 6)..(p + 7)] {
            "0" => (pi, pj + amount),
            "1" => (pi + amount, pj),
            "2" => (pi, pj - amount),
            "3" => (pi - amount, pj),
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
    fn test_d18p2() {
        let reader = BufReader::new(File::open("d18/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 952408144115);
    }
}
