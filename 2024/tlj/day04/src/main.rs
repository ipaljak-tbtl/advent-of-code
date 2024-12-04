use std::io::{self, BufRead};

const SEARCH_STR: &str = "XMAS";
const SEARCH_X: &str = "MAS";

#[derive(Debug, Clone, Copy)]
enum Slice {
    Horizontal,
    Vertical,
    DiagonalUp,
    DiagonalDown,
}

fn slice(slice: Slice, lines: &Vec<String>, x: usize, y: usize, slice_len: usize) -> String {
    match slice {
        Slice::Horizontal => lines[x][y..lines[x].len().min(y + slice_len)].to_string(),
        Slice::Vertical => lines[x..lines.len().min(x + slice_len)]
            .iter()
            .map(|l| l.chars().nth(y).unwrap())
            .collect(),
        Slice::DiagonalUp => {
            let mut s = String::new();
            for i in 0i32..slice_len as i32 {
                let x: i32 = x as i32 - i;
                let y: i32 = y as i32 + i;
                if x >= 0 && y < lines[x as usize].len() as i32 {
                    s.push(lines[x as usize].chars().nth(y as usize).unwrap());
                }
            }

            s
        }
        Slice::DiagonalDown => {
            let mut s = String::new();
            for i in 0..slice_len {
                let x = x + i;
                let y = y + i;
                if x < lines.len() && y < lines[x].len() {
                    s.push(lines[x].chars().nth(y).unwrap());
                }
            }

            s
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle
        .lines()
        .map(|l| l.unwrap())
        .filter(|l| l != "\n")
        .collect::<Vec<_>>();

    let mut count = 0;
    for slice_type in [
        Slice::Horizontal,
        Slice::Vertical,
        Slice::DiagonalUp,
        Slice::DiagonalDown,
    ] {
        for x in 0..lines.len() {
            for y in 0..lines[x].len() {
                let s = slice(slice_type, &lines, x, y, SEARCH_STR.len());
                if s == SEARCH_STR || s == SEARCH_STR.chars().rev().collect::<String>() {
                    count += 1;
                }
            }
        }
    }

    let mut count2 = 0;
    for i in 0..lines.len() - SEARCH_X.len() + 1 {
        for j in 0..lines[i].len() - SEARCH_X.len() + 1 {
            let s1 = slice(Slice::DiagonalDown, &lines, i, j, SEARCH_X.len());

            let s2 = slice(
                Slice::DiagonalUp,
                &lines,
                i + SEARCH_X.len() - 1,
                j,
                SEARCH_X.len(),
            );

            if (s1 == SEARCH_X || s1 == SEARCH_X.chars().rev().collect::<String>())
                && (s2 == SEARCH_X || s2 == SEARCH_X.chars().rev().collect::<String>())
            {
                count2 += 1;
            }
        }
    }

    println!("p1: {}", count);
    println!("p2: {}", count2);
}
