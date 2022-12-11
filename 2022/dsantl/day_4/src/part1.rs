use std::io::{self, BufRead};

fn split_line<'a>(line: &'a str, delimiter: &'a str) -> Vec<&'a str> {
    let split = line.split(delimiter);
    split.collect::<Vec<&str>>()
}

fn check_intervals(intervals: &Vec<u32>) -> bool {
    let a = intervals[0];
    let b = intervals[1];
    let c = intervals[2];
    let d = intervals[3];

    // Consider [a, b] - [c, d]

    if a >= c && b <= d {
        return true;
    }

    if c >= a && d <= b {
        return true;
    }

    false
}

fn main() {
    let stdin = io::stdin();

    let mut total = 0;
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let split = split_line(&line, ",");
        let mut intervals = vec![];
        for interval in split {
            let pair = split_line(interval, "-")
                .iter()
                .map(|x| x.parse::<u32>().unwrap())
                .collect::<Vec<u32>>();
            intervals.push(pair[0]);
            intervals.push(pair[1]);
        }
        if check_intervals(&intervals) {
            total += 1;
        }
    }
    println!("{}", total);
}
