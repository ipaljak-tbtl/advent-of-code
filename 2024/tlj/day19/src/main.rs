use std::io::{self, BufRead};

use pathfinding::prelude::count_paths;

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle.lines().map(|l| l.unwrap()).collect::<Vec<_>>();

    let available_patterns = lines[0].split(',').map(|l| l.trim()).collect::<Vec<_>>();

    let designs = &lines[2..];

    dbg!(&available_patterns);
    dbg!(&designs);

    let res = designs
        .iter()
        .map(|d| d.as_str())
        .map(|d| {
            println!("d: {}", d);
            count_paths(
                d,
                |d| {
                    available_patterns.iter().filter_map(|p| {
                        if d.starts_with(p) {
                            Some(&d[p.len()..])
                        } else {
                            None
                        }
                    })
                },
                |d| d.is_empty(),
            )
        })
        .collect::<Vec<_>>();

    println!("p1: {}", res.iter().filter(|&v| *v > 0).count());

    println!("p2: {}", res.iter().sum::<usize>());
}
