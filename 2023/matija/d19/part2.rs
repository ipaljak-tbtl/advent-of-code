use std::collections::HashMap;

#[derive(Clone, Copy, Debug)]
struct Condition {
    c: char,
    op: char,
    value: u64,
}

impl Condition {
    fn from_str(s: &str) -> Self {
        let value = s[2..].parse().unwrap();
        let chars: Vec<_> = s[..2].chars().collect();

        Self {
            c: chars[0],
            op: chars[1],
            value,
        }
    }

    fn neg(&self) -> Self {
        let (op, value) = match self.op {
            '>' => ('<', self.value + 1),
            '<' => ('>', self.value - 1),
            _ => unreachable!(),
        };

        Self {
            c: self.c,
            op,
            value,
        }
    }
}

fn condition_combinations(conds: &[Condition]) -> u64 {
    let mut min = [0, 0, 0, 0];
    let mut max = [4001, 4001, 4001, 4001];

    for cond in conds {
        let i = match cond.c {
            'x' => 0,
            'm' => 1,
            'a' => 2,
            's' => 3,
            _ => unreachable!(),
        };

        match cond.op {
            '>' if cond.value > min[i] => min[i] = cond.value,
            '<' if cond.value < max[i] => max[i] = cond.value,
            _ => continue,
        };
    }

    (max[0] - min[0] - 1) * (max[1] - min[1] - 1) * (max[2] - min[2] - 1) * (max[3] - min[3] - 1)
}

fn solve(reader: impl std::io::BufRead) -> u64 {
    let mut states = HashMap::<String, Vec<(String, Vec<Condition>)>>::new();

    for line in reader.lines().map(Result::unwrap) {
        if line.is_empty() {
            break;
        }

        let b = line.find('{').unwrap();

        let name = line[..b].to_owned();

        let mut prev_negated = Vec::new();

        let mut rules = Vec::new();

        for rule in line[(b + 1)..(line.len() - 1)].split(',') {
            if let Some(r) = rule.find(':') {
                let cond = Condition::from_str(&rule[..r]);

                let mut conds = prev_negated.clone();
                conds.push(cond);

                prev_negated.push(cond.neg());

                rules.push((rule[(r + 1)..].to_owned(), conds));
            } else {
                rules.push((rule.to_owned(), prev_negated.clone()));
            };
        }

        states.insert(name, rules);
    }

    let mut open = vec![("in", Vec::new())];

    let mut result = 0;

    while let Some((state, conds)) = open.pop() {
        if state == "A" {
            result += condition_combinations(&conds);
            continue;
        } else if state == "R" {
            continue;
        }

        for (next, new_conds) in states.get(state).unwrap() {
            let mut conds = conds.clone();
            conds.append(&mut new_conds.clone());
            open.push((next, conds));
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
    fn test_d19p2() {
        let reader = BufReader::new(File::open("d19/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 167409079868000);
    }
}
