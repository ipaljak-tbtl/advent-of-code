use std::io::{
    stdin,
    stdout,
    BufWriter,
    Write,
};

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

    let s = scanner.next::<String>();
    let mut ret = 0i32;

    for c in s.chars() {
        ret += match c {
            '(' => 1,
            _ => -1,
        };
    }

    writeln!(out, "{}", ret).ok();
}
