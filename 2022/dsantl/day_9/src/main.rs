use std::cmp;
use std::collections::HashSet;
use std::io::{self, BufRead};

fn split_line<'a>(line: &'a str, delimiter: &'a str) -> Vec<&'a str> {
    let split = line.split(delimiter);
    split.collect::<Vec<&str>>()
}

fn max_distance(a: (i32, i32), b: (i32, i32)) -> i32 {
    cmp::max((a.0 - b.0).abs(), (a.1 - b.1).abs())
}

#[allow(dead_code)]
fn print_rope(rope: &Vec<(i32, i32)>) {
    for i in 0..20 {
        for j in 0..20 {
            let mut visited = false;
            for (index, r) in rope.iter().enumerate() {
                if r.0 == j && r.1 == i {
                    visited = true;
                    print!("{}", index);
                    break;
                }
            }
            if visited == false {
                print!("{}", '#');
            }
        }
        println!();
    }
    println!();
}

fn calc_force(from: (i32, i32), to: (i32, i32)) -> (i32, i32) {
    let dx = if (to.0 - from.0) == 0 {
        0
    } else {
        (to.0 - from.0).abs() / (to.0 - from.0)
    };
    let dy = if (to.1 - from.1) == 0 {
        0
    } else {
        (to.1 - from.1).abs() / (to.1 - from.1)
    };
    (dx, dy)
}

fn main() {
    let stdin = io::stdin();

    let mut rope = vec![(10, 10); 10];

    let mut positions = HashSet::new();
    positions.insert(rope[0]);

    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let split = split_line(&line, " ");
        let direction = split[0];
        let steps = split[1].parse::<u32>().unwrap();
        for _ in 0..steps {
            let mut force = match direction {
                "U" => (0, 1),
                "D" => (0, -1),
                "L" => (-1, 0),
                "R" => (1, 0),
                _ => unreachable!(),
            };
            rope[0] = (rope[0].0 + force.0, rope[0].1 + force.1);

            for i in 1..10 {
                if max_distance(rope[i - 1], rope[i]) > 1 {
                    force = calc_force(rope[i], rope[i - 1]);

                    rope[i] = (rope[i].0 + force.0, rope[i].1 + force.1);
                }
            }
            positions.insert(rope[9]);
        }
    }
    println!("{}", positions.len());
}
