use std::io::{self, BufRead};

fn split_line<'a>(line: &'a str, delimiter: &'a str) -> Vec<&'a str> {
    let split = line.split(delimiter);
    split.collect::<Vec<&str>>()
}

fn strength(cycle: i32, value: i32) -> i32 {
    if cycle <= 220 && (cycle - 20) % 40 == 0 {
        cycle * value
    } else {
        0
    }
}

fn main() {
    let stdin = io::stdin();
    let mut x = 1;
    let mut cycle = 1;
    let mut total = 0i32;
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let split = split_line(&line, " ");
        match split[0] {
            "addx" => {
                total += strength(cycle, x);
                cycle += 1;
                total += strength(cycle, x);
                x += split[1].parse::<i32>().unwrap();
                cycle += 1;
            }
            "noop" => {
                total += strength(cycle, x);
                cycle += 1;
            }
            _ => unreachable!(),
        }
    }
    println!("{}", total);
}
