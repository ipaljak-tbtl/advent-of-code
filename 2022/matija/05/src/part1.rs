pub fn solve(input: &[String]) -> String {
    let mut stacks: Vec<Vec<char>> = vec![Vec::new(); 9];
    let mut move_idx = 0;

    for (i, line) in input.iter().enumerate() {
        if line.starts_with(' ') {
            move_idx = i;
        }
    }

    for line in input.iter().take(move_idx).rev() {
        for (i, c) in line.chars().enumerate() {
            if ('A'..='Z').contains(&c) {
                stacks[(i - 1) / 4].push(c);
            }
        }
    }

    let re = regex::Regex::new(r"^move (\d+) from (\d+) to (\d+)$").unwrap();
    for line in input.iter().skip(move_idx + 2) {
        let cap = re.captures(line).unwrap();
        let n: u32 = cap[1].parse().unwrap();
        let from: usize = cap[2].parse().unwrap();
        let to: usize = cap[3].parse().unwrap();

        for _ in 0..n {
            let c = stacks[from - 1].pop().unwrap();
            stacks[to - 1].push(c);
        }
    }

    let mut result = String::new();
    for s in stacks {
        result.push(*s.last().unwrap());
    }

    result
}
