use std::collections::HashMap;

#[derive(Clone, Copy)]
struct Condition {
    c: char,
    op: char,
    value: u32,
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

    fn eval(&self, part: (u32, u32, u32, u32)) -> bool {
        let value = match self.c {
            'x' => part.0,
            'm' => part.1,
            'a' => part.2,
            's' => part.3,
            _ => unreachable!(),
        };

        match self.op {
            '>' => value > self.value,
            '<' => value < self.value,
            _ => unreachable!(),
        }
    }
}

fn solve(reader: impl std::io::BufRead) -> u32 {
    let mut lines = reader.lines().map(Result::unwrap);

    let mut states = HashMap::<String, Vec<(String, Vec<Condition>)>>::new();

    for line in lines.by_ref() {
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

    let mut result = 0;

    for line in lines {
        let part: Vec<u32> = line[1..(line.len() - 1)]
            .split(',')
            .map(|part| part[2..].parse().unwrap())
            .collect();
        let part = (part[0], part[1], part[2], part[3]);

        let mut state = "in";

        while state != "A" && state != "R" {
            for (next, conds) in states.get(state).unwrap() {
                if conds.iter().all(|cond| cond.eval(part)) {
                    state = next;
                    break;
                }
            }
        }

        if state == "A" {
            result += part.0 + part.1 + part.2 + part.3;
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
    fn test_d19p1() {
        let reader = BufReader::new(File::open("d19/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 19114);
    }
}
