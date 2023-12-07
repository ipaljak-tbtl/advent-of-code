const STRENGTHS: [char; 13] = [
    'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A',
];

fn hand_type(hand: &str) -> Vec<usize> {
    let mut cnts = std::collections::HashMap::<char, usize>::new();
    for c in hand.chars() {
        *cnts.entry(c).or_default() += 1;
    }
    let jokers = cnts.remove(&'J').unwrap_or_default();

    let mut cnts: Vec<usize> = cnts.into_values().collect();
    cnts.sort_by_key(|&k| std::cmp::Reverse(k));

    cnts.push(0);
    *cnts.first_mut().unwrap() += jokers;

    cnts
}

fn hand_lex(h: &str) -> Vec<usize> {
    h.chars()
        .map(|d| STRENGTHS.iter().position(|&c| c == d).unwrap())
        .collect()
}

fn solve(reader: impl std::io::BufRead) -> usize {
    let mut values: Vec<(String, usize)> = reader
        .lines()
        .map(Result::unwrap)
        .map(|line| (line[..5].to_owned(), line[6..].parse().unwrap()))
        .collect();

    values.sort_by_key(|(hand, _)| (hand_type(hand), hand_lex(hand)));

    values
        .into_iter()
        .enumerate()
        .map(|(i, (_, bid))| (i + 1) * bid)
        .sum()
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d07p2() {
        let reader = BufReader::new(File::open("d07/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 5905);
    }
}
