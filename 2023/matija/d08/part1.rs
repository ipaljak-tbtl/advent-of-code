fn solve(reader: impl std::io::BufRead) -> u32 {
    let mut lines = reader.lines().map(Result::unwrap);

    let first_line = lines.next().unwrap();
    let mut steps = first_line.chars().cycle();

    let mut nodes = std::collections::HashMap::<String, (String, String)>::new();
    lines.skip(1).for_each(|line| {
        nodes.insert(
            line[..3].to_owned(),
            (line[7..10].to_owned(), line[12..15].to_owned()),
        );
    });

    let mut current = "AAA";

    let mut cnt = 0;

    while current != "ZZZ" {
        let step = steps.next().unwrap();

        let next = nodes.get(current).unwrap();

        current = match step {
            'L' => &next.0,
            _ => &next.1,
        };

        cnt += 1;
    }

    cnt
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d08p1_1() {
        let reader = BufReader::new(File::open("d08/test_input1_1.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 2);
    }

    #[test]
    fn test_d08p1_2() {
        let reader = BufReader::new(File::open("d08/test_input1_2.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 6);
    }
}
