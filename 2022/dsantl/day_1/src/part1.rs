use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut total_max = 0;
    let mut curr_max = 0;

    for line in stdin.lock().lines() {
        if line.as_ref().unwrap().is_empty() {
            if total_max < curr_max {
                total_max = curr_max;
            }
            curr_max = 0;
            continue;
        }
        let value = line.unwrap().parse::<u32>().unwrap();
        curr_max += value;
    }

    if total_max < curr_max {
        total_max = curr_max;
    }

    println!("{}", total_max);
}
