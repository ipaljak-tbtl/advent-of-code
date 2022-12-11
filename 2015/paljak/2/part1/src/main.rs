use std::{
    cmp::min,
    io::{
        stdin,
        stdout,
        BufWriter,
        Write,
    },
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

    let n = scanner.next::<i32>();
    let mut sol = 0i32;
    for _ in 0..n {
        let v = scanner
            .next::<String>()
            .split('x')
            .map(|x| x.parse::<i32>().unwrap())
            .collect::<Vec<i32>>();
        sol += 2 * (v[0] * v[1] + v[1] * v[2] + v[2] * v[0])
            + min(v[0] * v[1], min(v[1] * v[2], v[2] * v[0]));
    }

    writeln!(out, "{}", sol).ok();
}
