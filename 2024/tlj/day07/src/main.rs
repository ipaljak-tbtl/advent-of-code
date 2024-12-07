use std::io::{self, BufRead};

fn is_good_calibration1(target: i64, curr_score: i64, operands: &[i64]) -> bool {
    if operands.is_empty() {
        return curr_score == target;
    }

    return is_good_calibration1(target, curr_score + operands[0], &operands[1..])
        || is_good_calibration1(target, curr_score * operands[0], &operands[1..]);
}

fn is_good_calibration2(target: i64, curr_score: i64, operands: &[i64]) -> bool {
    if operands.is_empty() {
        return curr_score == target;
    }

    let concatenated = format!("{}{}", curr_score, operands[0].to_string().as_str())
        .parse::<i64>()
        .unwrap();

    return is_good_calibration2(target, curr_score + operands[0], &operands[1..])
        || is_good_calibration2(target, curr_score * operands[0], &operands[1..])
        || is_good_calibration2(target, concatenated, &operands[1..]);
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle
        .lines()
        .map(|l| {
            let l = l
                .unwrap()
                .split(':')
                .map(|l| l.to_owned())
                .collect::<Vec<_>>();

            (
                l[0].parse::<i64>().unwrap(),
                l[1].trim()
                    .split_whitespace()
                    .map(|n| n.parse::<i64>().unwrap())
                    .collect::<Vec<_>>(),
            )
        })
        .collect::<Vec<_>>();

    let sum1: i64 = lines
        .iter()
        .filter_map(|(target, operands)| {
            if is_good_calibration1(*target, operands[0], &operands[1..]) {
                Some(*target)
            } else {
                None
            }
        })
        .sum();

    let sum2: i64 = lines
        .iter()
        .filter_map(|(target, operands)| {
            if is_good_calibration2(*target, operands[0], &operands[1..]) {
                Some(*target)
            } else {
                None
            }
        })
        .sum();

    println!("p1: {}", sum1);
    println!("p2: {}", sum2);
}
