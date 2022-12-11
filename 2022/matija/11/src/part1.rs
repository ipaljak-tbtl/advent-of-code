struct Monkey {
    inspections: u32,
    items: Vec<u32>,
    operation: Vec<String>,
    test: u32,
    if_true: u32,
    if_false: u32,
}

fn perform_operation(old: u32, operation: &[String]) -> u32 {
    let x = if operation[0] == "old" {
        old
    } else {
        operation[0].parse().unwrap()
    };

    let y = if operation[2] == "old" {
        old
    } else {
        operation[2].parse().unwrap()
    };

    if operation[1] == "+" {
        x + y
    } else {
        x * y
    }
}

pub fn solve(input: &[String]) -> u32 {
    let mut monkeys: Vec<Monkey> = vec![];

    let mut i = 1;
    while i < input.len() {
        let items: Vec<u32> = input[i][18..]
            .split(", ")
            .map(|item| item.parse().unwrap())
            .collect();

        i += 1;
        let operation: Vec<String> = input[i][19..].split(" ").map(String::from).collect();

        i += 1;
        let test: u32 = input[i][21..].parse().unwrap();

        i += 1;
        let if_true: u32 = input[i][29..].parse().unwrap();

        i += 1;
        let if_false: u32 = input[i][30..].parse().unwrap();

        i += 3;

        monkeys.push(Monkey {
            inspections: 0,
            items,
            operation,
            test,
            if_true,
            if_false,
        })
    }

    for _ in 0..20 {
        for i in 0..monkeys.len() {
            for j in 0..monkeys[i].items.len() {
                let worry =
                    perform_operation(monkeys[i].items[j].clone(), &monkeys[i].operation) / 3;

                if worry % monkeys[i].test == 0 {
                    let if_true = monkeys[i].if_true as usize;
                    monkeys[if_true].items.push(worry);
                } else {
                    let if_false = monkeys[i].if_false as usize;
                    monkeys[if_false].items.push(worry);
                }

                monkeys[i].inspections += 1;
            }

            monkeys[i].items = vec![];
        }
    }

    monkeys.sort_by(|m1, m2| m2.inspections.cmp(&m1.inspections));

    monkeys[0].inspections * monkeys[1].inspections
}
