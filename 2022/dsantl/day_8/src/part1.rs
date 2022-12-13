use std::collections::HashSet;
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();

    let mut map = vec![];

    let mut row_size = 0;
    let mut col_size = 0;

    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let mut row = vec![];
        for c in line.chars() {
            let digit = (c as i32) - ('0' as i32);
            row.push(digit);
        }
        map.push(row);
        row_size += 1;
        col_size = line.len();
    }

    let mut pairs: HashSet<(usize, usize)> = HashSet::new();

    for i in 0..row_size {
        let mut max = -1;
        for j in 0..col_size {
            if map[i][j] > max {
                max = map[i][j];
                pairs.insert((i, j));
            }
        }
    }

    for i in 0..row_size {
        let mut max = -1;
        for j in (0..col_size).rev() {
            if map[i][j] > max {
                max = map[i][j];
                pairs.insert((i, j));
            }
        }
    }

    for j in 0..col_size {
        let mut max = -1;
        for i in 0..row_size {
            if map[i][j] > max {
                max = map[i][j];
                pairs.insert((i, j));
            }
        }
    }

    for j in 0..col_size {
        let mut max = -1;
        for i in (0..row_size).rev() {
            if map[i][j] > max {
                max = map[i][j];
                pairs.insert((i, j));
            }
        }
    }

    println!("{}", pairs.len());
}
