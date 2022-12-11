use std::{
    collections::HashSet,
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

    let s = scanner.next::<String>();
    let mut set: HashSet<(i32, i32)> = HashSet::new();
    let (mut x, mut y) = ([0i32, 0i32], [0i32, 0i32]);
    let mut turn = 0;

    set.insert((0i32, 0i32));
    for c in s.chars() {
        match c {
            '>' => x[turn] += 1,
            '<' => x[turn] -= 1,
            '^' => y[turn] += 1,
            'v' => y[turn] -= 1,
            _ => panic!(),
        };
        set.insert((x[turn], y[turn]));
        turn = 1 - turn;
    }

    writeln!(out, "{}", set.len()).ok();
}
