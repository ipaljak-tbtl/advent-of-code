use std::io::{self, BufRead};

fn split_line(line: &str) -> Vec<&str> {
    let split = line.split(" ");
    split.collect::<Vec<&str>>()
}

fn main() {
    let stdin = io::stdin();

    let mut total = 0;
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let split = split_line(&line);
        total += match split[1] {
            "X" => 1,
            "Y" => 2,
            "Z" => 3,
            _ => 0,
        };
        total += match (split[0], split[1]) {
            ("A", "X") => 3,
            ("A", "Y") => 6,
            ("B", "Y") => 3,
            ("B", "Z") => 6,
            ("C", "X") => 6,
            ("C", "Z") => 3,
            _ => 0,
        };
    }
    println!("{}", total);
}
