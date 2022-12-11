use std::io::{
    stdin,
    stdout,
    BufWriter,
    Write,
};

use md5;

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn main() {
    let mut scanner = Scanner::default();
    let out = &mut BufWriter::new(stdout());

    let key_pref = scanner.next::<String>();
    for i in 1.. {
        let mut key = key_pref.clone();
        key.push_str(&i.to_string());
        let hash = format!("{:x}", md5::compute(key.as_bytes()));
        if hash.starts_with("00000") {
            writeln!(out, "{}", key).ok();
            return;
        }
    }
}
