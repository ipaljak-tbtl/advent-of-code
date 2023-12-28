fn parse_input(reader: impl std::io::BufRead) -> Vec<((f64, bool), (f64, f64))> {
    let mut lines = Vec::new();
    for line in reader.lines().map(Result::unwrap) {
        let spl: Vec<Vec<f64>> = line
            .split(" @ ")
            .map(|s| s.split(", ").map(|s| s.parse().unwrap()).collect())
            .collect();
        let (x, y, dx, dy) = (spl[0][0], spl[0][1], spl[1][0], spl[1][1]);
        let k = dy / dx;
        let l = y - k * x;
        lines.push(((x, dx > 0.0), (k, l)));
    }
    lines
}

fn solve(reader: impl std::io::BufRead, min: f64, max: f64) -> u32 {
    let lines = parse_input(reader);

    let mut cnt = 0;
    for (i, ((x1, pos1), (k1, l1))) in lines.iter().enumerate() {
        for ((x2, pos2), (k2, l2)) in lines.iter().skip(i + 1) {
            if k1 == k2 {
                continue;
            }
            let x = (l2 - l1) / (k1 - k2);
            let y = k1 * x + l1;
            if pos1 ^ (&x > x1) || pos2 ^ (&x > x2) {
                continue;
            }
            if x >= min && y >= min && x <= max && y <= max {
                cnt += 1;
            }
        }
    }
    cnt
}

fn main() {
    println!(
        "{}",
        solve(
            std::io::stdin().lock(),
            200_000_000_000_000.0,
            400_000_000_000_000.0
        )
    );
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d24p1() {
        let reader = BufReader::new(File::open("d24/test_input.txt").unwrap());
        let result = solve(reader, 7.0, 27.0);
        assert_eq!(result, 2);
    }
}
