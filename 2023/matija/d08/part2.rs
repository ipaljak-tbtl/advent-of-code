type Node = (char, char, char);

fn str_to_node(s: &str) -> Node {
    let mut chars = s.chars();
    (
        chars.next().unwrap(),
        chars.next().unwrap(),
        chars.next().unwrap(),
    )
}

fn gcd(mut a: u64, mut b: u64) -> u64 {
    while b != 0 {
        (a, b) = (b, a % b);
    }
    a
}

fn lcm(a: u64, b: u64) -> u64 {
    b * (a / gcd(a, b))
}

fn solve(reader: impl std::io::BufRead) -> u64 {
    let mut lines = reader.lines().map(Result::unwrap);

    let first_line = lines.next().unwrap();

    let mut nodes = std::collections::HashMap::<Node, (Node, Node)>::new();
    lines.skip(1).for_each(|line| {
        nodes.insert(
            str_to_node(&line[..3]),
            (str_to_node(&line[7..10]), str_to_node(&line[12..15])),
        );
    });

    let mut current = Vec::<Node>::new();
    nodes.keys().for_each(|node| {
        if node.2 == 'A' {
            current.push(*node);
        }
    });

    let mut cycles = Vec::<u64>::new();

    for mut node in current {
        let mut steps = first_line.chars().cycle();

        let mut cnt = 0;

        while node.2 != 'Z' {
            let step = steps.next().unwrap();
            let next = nodes.get(&node).unwrap();

            node = match step {
                'L' => next.0,
                _ => next.1,
            };

            cnt += 1;
        }

        cycles.push(cnt);
    }

    cycles.iter().fold(1, |acc, &x| lcm(acc, x))
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d08p2() {
        let reader = BufReader::new(File::open("d08/test_input2.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 6);
    }
}
