fn solve(reader: impl std::io::BufRead) -> u32 {
    let mut lines = reader.lines().map(Result::unwrap);

    let l1 = lines.next().unwrap();
    let l2 = lines.next().unwrap();

    let ts = l1.split_whitespace().skip(1).map(str::parse::<u32>);
    let ds = l2.split_whitespace().skip(1).map(str::parse::<u32>);

    let mut result = 1u32;

    for (t, d) in ts.zip(ds) {
        let t = t.unwrap();
        let d = d.unwrap();

        let mut cnt = 0;
        for th in 1..t {
            if th * (t - th) > d {
                cnt += 1;
            }
        }
        result *= cnt
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
    fn test_d06p1() {
        let reader = BufReader::new(File::open("d06/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 288);
    }
}
