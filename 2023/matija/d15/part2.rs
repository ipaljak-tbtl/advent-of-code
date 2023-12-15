fn hash(input: &str) -> usize {
    input
        .chars()
        .fold(0, |acc, c| ((acc + c as usize) * 17) % 256)
}

fn solve(reader: impl std::io::BufRead) -> usize {
    let line = reader.lines().next().unwrap().unwrap();

    let mut boxes = std::collections::HashMap::<usize, Vec<(&str, usize)>>::new();

    line.split(',').for_each(|step| {
        let i_op = step.find(|c| c == '=' || c == '-').unwrap();
        let op = &step[i_op..(i_op + 1)];

        let label = &step[..i_op];
        let bx = hash(label);

        if op == "-" {
            if let Some(lenses) = boxes.get_mut(&bx) {
                if let Some(idx) = lenses.iter().position(|(lens, _)| lens == &label) {
                    lenses.remove(idx);
                };
            };
        } else {
            let f_len = step[(i_op + 1)..].parse().unwrap();

            let lenses = boxes.entry(bx).or_default();

            if let Some(idx) = lenses.iter().position(|(lens, _)| lens == &label) {
                lenses.get_mut(idx).unwrap().1 = f_len;
            } else {
                lenses.push((label, f_len));
            };
        }
    });

    let mut result = 0;

    for (b, lenses) in boxes {
        for (i, (_, f_len)) in lenses.iter().enumerate() {
            result += (b + 1) * (i + 1) * f_len;
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
    fn test_d15p2() {
        let reader = BufReader::new(File::open("d15/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 145);
    }
}
