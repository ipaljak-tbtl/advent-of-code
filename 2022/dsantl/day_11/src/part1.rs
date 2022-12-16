use std::io::{self, BufRead};

fn split_line<'a>(line: &'a str, delimiter: &'a str) -> Vec<&'a str> {
    let split = line.split(delimiter);
    split.collect::<Vec<&str>>()
}

#[derive(Clone)]
struct MonkeyBuilder {
    id: Option<u32>,
    items: Option<Vec<u32>>,
    operator: Option<String>,
    operand_1: Option<String>,
    operand_2: Option<String>,
    divisible_by: Option<u32>,
    for_true: Option<usize>,
    for_false: Option<usize>,
}

struct Monkey {
    #[allow(dead_code)]
    id: u32,
    items: Vec<u32>,
    operator: String,
    operand_1: String,
    operand_2: String,
    divisible_by: u32,
    for_true: usize,
    for_false: usize,
}

impl MonkeyBuilder {
    fn new() -> Self {
        Self {
            id: None,
            items: None,
            operator: None,
            operand_1: None,
            operand_2: None,
            divisible_by: None,
            for_true: None,
            for_false: None,
        }
    }

    fn build(self) -> Monkey {
        Monkey {
            id: self.id.unwrap(),
            items: self.items.unwrap(),
            operator: self.operator.unwrap(),
            operand_1: self.operand_1.unwrap(),
            operand_2: self.operand_2.unwrap(),
            divisible_by: self.divisible_by.unwrap(),
            for_true: self.for_true.unwrap(),
            for_false: self.for_false.unwrap(),
        }
    }
}

fn calculate_level(level: u32, a: &String, o: &String, b: &String) -> u32 {
    let first = if a == "old" {
        level
    } else {
        a.parse::<u32>().unwrap()
    };

    let second = if b == "old" {
        level
    } else {
        b.parse::<u32>().unwrap()
    };

    if o == "+" {
        return first + second;
    } else if o == "*" {
        return first * second;
    }

    unreachable!()
}

fn main() {
    let stdin = io::stdin();

    let mut monkeys: Vec<Monkey> = vec![];
    let mut tmp_monkey = MonkeyBuilder::new();

    for (index, line) in stdin.lock().lines().enumerate() {
        let line = line.unwrap();
        let split = split_line(&line, " ");
        match index % 7 {
            0 => {
                tmp_monkey = MonkeyBuilder::new();
                let id = split[1].replace(":", "").parse::<u32>().unwrap();
                tmp_monkey.id = Some(id);
            }
            1 => {
                let mut items = vec![];
                for e in &split[4..] {
                    items.push(e.replace(",", "").parse::<u32>().unwrap());
                }
                tmp_monkey.items = Some(items);
            }
            2 => {
                tmp_monkey.operand_1 = Some(split[5].to_owned());
                tmp_monkey.operator = Some(split[6].to_owned());
                tmp_monkey.operand_2 = Some(split[7].to_owned());
            }
            3 => {
                tmp_monkey.divisible_by = Some(split[5].parse::<u32>().unwrap());
            }
            4 => tmp_monkey.for_true = Some(split[9].parse::<usize>().unwrap()),
            5 => {
                tmp_monkey.for_false = Some(split[9].parse::<usize>().unwrap());
                monkeys.push(tmp_monkey.clone().build());
            }
            6 => {}
            _ => unreachable!(),
        }
    }

    let mut counter = vec![0; monkeys.len()];

    for _ in 0..20 {
        for index in 0..monkeys.len() {
            if monkeys[index].items.is_empty() {
                continue;
            }
            for level_index in 0..monkeys[index].items.len() {
                let worry_level = monkeys[index].items[level_index];
                counter[index] += 1;
                let worry_level = calculate_level(
                    worry_level,
                    &monkeys[index].operand_1,
                    &monkeys[index].operator,
                    &monkeys[index].operand_2,
                );

                let worry_level = worry_level / 3;

                if worry_level % monkeys[index].divisible_by == 0 {
                    let to = monkeys[index].for_true;
                    monkeys[to].items.push(worry_level);
                } else {
                    let to = monkeys[index].for_false;
                    monkeys[to].items.push(worry_level);
                }
            }
            monkeys[index].items = vec![];
        }
    }

    counter.sort_by(|a, b| b.cmp(a));

    println!("{}", counter[0] * counter[1]);
}
