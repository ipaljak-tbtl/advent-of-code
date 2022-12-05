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
        let n: usize = cap[1].parse().unwrap();
        let from: usize = cap[2].parse().unwrap();
        let to: usize = cap[3].parse().unwrap();

        let mut tmp_stack = Vec::with_capacity(n);
        for _ in 0..n {
            tmp_stack.push(stacks[from - 1].pop().unwrap());
        }

        for _ in 0..n {
            stacks[to - 1].push(tmp_stack.pop().unwrap())
        }
    }

    let mut result = String::new();
    for s in stacks {
        result.push(*s.last().unwrap());
    }

    result
}
