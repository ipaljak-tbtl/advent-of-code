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

    let mut max = 0;

    for i in 0..row_size {
        for j in 0..col_size {
            if i == 0 || i == row_size - 1 || j == 0 || j == col_size - 1 {
                continue;
            }
            let mut total = 1;
            let mut tmp = 0;
            for k in (i + 1)..row_size {
                tmp += 1;
                if map[i][j] <= map[k][j] {
                    break;
                }
            }
            total *= tmp;

            tmp = 0;
            for k in (j + 1)..col_size {
                tmp += 1;
                if map[i][j] <= map[i][k] {
                    break;
                }
            }
            total *= tmp;

            tmp = 0;
            for k in (0..j).rev() {
                tmp += 1;
                if map[i][j] <= map[i][k] {
                    break;
                }
            }
            total *= tmp;

            tmp = 0;
            for k in (0..i).rev() {
                tmp += 1;
                if map[i][j] <= map[k][j] {
                    break;
                }
            }
            total *= tmp;

            if total > max {
                max = total;
            }
        }
    }
    println!("{}", max);
}
