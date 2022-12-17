use std::collections::VecDeque;
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();

    let mut map = vec![];
    let mut queue: VecDeque<(i32, i32, u32)> = VecDeque::new();

    for (i, line) in stdin.lock().lines().enumerate() {
        let mut row: Vec<u8> = vec![];
        for (j, c) in line.unwrap().chars().enumerate() {
            if c == 'S' {
                row.push('a' as u8);
            } else if c == 'E' {
                row.push('z' as u8);
                queue.push_back((i as i32, j as i32, 0));
            } else {
                row.push(c as u8);
            }
        }
        map.push(row);
    }

    let max_row = map.len();
    let max_col = map[0].len();

    let mut visited = vec![vec![false; max_col]; max_row];
    let mut min = (max_row * max_col) as u32;

    while !queue.is_empty() {
        let (i, j, score) = queue.pop_front().unwrap();

        if visited[i as usize][j as usize] == true {
            continue;
        }

        visited[i as usize][j as usize] = true;

        if map[i as usize][j as usize] == 'a' as u8 {
            if score < min {
                min = score;
            }
        }

        for d in &[-1, 1] {
            if i + d >= 0
                && i + d < max_row as i32
                && visited[(i + d) as usize][j as usize] == false
            {
                if map[i as usize][j as usize] <= map[(i + d) as usize][j as usize] + 1 {
                    queue.push_back((i + d, j, score + 1));
                }
            }
            if j + d >= 0
                && j + d < max_col as i32
                && visited[i as usize][(j + d) as usize] == false
            {
                if map[i as usize][j as usize] <= map[i as usize][(j + d) as usize] + 1 {
                    queue.push_back((i, j + d, score + 1));
                }
            }
        }
    }
    println!("{}", min);
}
