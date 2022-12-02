use std::io::{self, BufRead};

fn swap_min(vec: &mut Vec<u32>, current: u32) {
    let mut min = vec[0];
    let mut index = 0;
    for i in 1..vec.len() {
        if vec[i] < min {
            min = vec[i];
            index = i;
        }
    }

    if vec[index] < current {
        vec[index] = current;
    }
}

fn main() {
    let stdin = io::stdin();
    let mut total_max = vec![0, 0, 0];
    let mut curr_max = 0;

    for line in stdin.lock().lines() {
        if line.as_ref().unwrap().is_empty() {
            swap_min(&mut total_max, curr_max);
            curr_max = 0;
            continue;
        }
        let value = line.unwrap().parse::<u32>().unwrap();
        curr_max += value;
    }

    swap_min(&mut total_max, curr_max);

    println!("{}", total_max[0] + total_max[1] + total_max[2]);
}
