use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();

    let mut score = 0;
    let mut memo = vec![0; 256];

    for (i, line) in stdin.lock().lines().enumerate() {
        let line = line.unwrap();
        let modulus = i % 3;
        if modulus == 0 {
            memo = vec![0; 256];
        }
        for c in line.chars() {
            if memo[c as usize] == modulus {
                memo[c as usize] = modulus + 1;
            }
        }
        if modulus == 2 {
            let index = memo.iter().position(|&x| x == 3).unwrap() as u32;
            let s = if index >= 'a' as u32 && index <= 'z' as u32 {
                (index - 'a' as u32) + 1
            } else {
                (index - 'A' as u32) + 27
            };
            score += s;
        }
    }
    println!("{}", score);
}
