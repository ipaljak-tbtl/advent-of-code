use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();

    for line in stdin.lock().lines() {
        let mut memo: Vec<usize> = vec![0; 26];
        let mut buff: Vec<char> = vec![];
        let line = line.unwrap();
        for (index, c) in line.chars().enumerate() {
            if buff.len() == 14 {
                let reset = buff.remove(0);
                let ord = (reset as usize) - ('a' as usize);
                memo[ord] -= 1;
            }
            let ord = (c as usize) - ('a' as usize);
            memo[ord] += 1;
            buff.push(c);
            let sum = memo.iter().filter(|x| **x == 1usize).sum::<usize>();
            if sum == 14 {
                println!("{}", index + 1);
                break;
            }
        }
    }
}
