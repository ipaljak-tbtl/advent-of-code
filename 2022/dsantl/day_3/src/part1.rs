use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();

    let mut score = 0;
    for line in stdin.lock().lines() {
        let mut memo = vec![-1; 256];
        let line = line.unwrap();
        let line_size = line.len();
        for (i, c) in line.chars().enumerate() {
            if i < line_size / 2 {
                memo[c as usize] = 1;
            } else if memo[c as usize] == 1 {
                memo[c as usize] = 0;
            }
        }
        let index = memo.iter().position(|&x| x == 0).unwrap() as u32;
        let s = if index >= 'a' as u32 && index <= 'z' as u32 {
            (index - 'a' as u32) + 1
        } else {
            (index - 'A' as u32) + 27
        };
        score += s;
    }
    println!("{}", score);
}
