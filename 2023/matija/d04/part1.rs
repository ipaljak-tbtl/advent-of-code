use std::collections::HashSet;

fn main() {
    let in_lines: Vec<String> = std::io::stdin().lines().collect::<Result<_, _>>().unwrap();

    let mut result = 0u32;

    for line in in_lines {
        let mut winning = HashSet::<u32>::new();
        let mut chosen = HashSet::<u32>::new();

        let mut on_winning = true;
        for part in line.split_whitespace().skip(2) {
            if part == "|" {
                on_winning = false;
                continue;
            }

            if on_winning {
                winning.insert(part.parse().unwrap());
            } else {
                chosen.insert(part.parse().unwrap());
            }
        }

        let hits = winning.intersection(&chosen).count();
        if hits == 0 {
            continue;
        }

        result += 1 << (hits - 1);
    }

    println!("{result}")
}
