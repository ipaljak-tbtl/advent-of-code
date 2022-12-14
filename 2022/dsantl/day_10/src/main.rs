use std::io::{self, BufRead};

fn split_line<'a>(line: &'a str, delimiter: &'a str) -> Vec<&'a str> {
    let split = line.split(delimiter);
    split.collect::<Vec<&str>>()
}

fn paint(cycle: i32, value: i32) {
    let pixel = (cycle - 1) % 40;
    if pixel == 0 {
        println!();
    }
    if pixel == value + 1 || pixel == value - 1 || pixel == value {
        print!("#");
    } else {
        print!(".")
    };
}

fn main() {
    let stdin = io::stdin();
    let mut x = 1;
    let mut cycle = 1;
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let split = split_line(&line, " ");
        match split[0] {
            "addx" => {
                paint(cycle, x);
                cycle += 1;
                paint(cycle, x);
                x += split[1].parse::<i32>().unwrap();
                cycle += 1;
            }
            "noop" => {
                paint(cycle, x);
                cycle += 1;
            }
            _ => unreachable!(),
        }
    }
}
