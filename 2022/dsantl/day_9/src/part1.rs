use std::cmp;
use std::collections::HashSet;
use std::io::{self, BufRead};

fn split_line<'a>(line: &'a str, delimiter: &'a str) -> Vec<&'a str> {
    let split = line.split(delimiter);
    split.collect::<Vec<&str>>()
}

fn max_distance(a: (i32, i32), b: (i32, i32)) -> i32 {
    cmp::max((a.0 - b.0).abs(), (a.1 - b.1).abs())
}

fn main() {
    let stdin = io::stdin();

    let mut head = (0, 0);
    let mut tail = (0, 0);

    let mut positions = HashSet::new();
    positions.insert(tail);

    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let split = split_line(&line, " ");
        let direction = split[0];
        let steps = split[1].parse::<u32>().unwrap();
        for _ in 0..steps {
            head = match direction {
                "U" => (head.0, head.1 + 1),
                "D" => (head.0, head.1 - 1),
                "L" => (head.0 - 1, head.1),
                "R" => (head.0 + 1, head.1),
                _ => unreachable!(),
            };
            if max_distance(head, tail) > 1 {
                tail = match direction {
                    "U" => (head.0, head.1 - 1),
                    "D" => (head.0, head.1 + 1),
                    "L" => (head.0 + 1, head.1),
                    "R" => (head.0 - 1, head.1),
                    _ => unreachable!(),
                };
            }
            positions.insert(tail);
        }
    }
    println!("{}", positions.len());
}
