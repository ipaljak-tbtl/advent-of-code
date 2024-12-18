use std::{
    collections::HashSet,
    io::{self, BufRead},
};

use pathfinding::directed::astar;

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let walls = handle
        .lines()
        .map(|l| {
            let l = l.unwrap();
            let l = l.split(",").collect::<Vec<_>>();
            let i = l[0].parse::<usize>().unwrap();
            let j = l[1].parse::<usize>().unwrap();
            (i, j)
        })
        .collect::<Vec<_>>();

    let p1_walls = walls[0..1024]
        .iter()
        .map(|l| l.clone())
        .collect::<HashSet<_>>();

    let width = 70;
    let height = 70;

    let (_, steps) = astar::astar(
        &(0, 0),
        |(x, y)| {
            let mut succ: Vec<((usize, usize), usize)> = Vec::new();

            if *x > 0 {
                if !p1_walls.contains(&((x - 1), *y)) {
                    succ.push(((x - 1, *y), 1));
                }
            }

            if *x < width {
                if !p1_walls.contains(&((x + 1), *y)) {
                    succ.push(((x + 1, *y), 1));
                }
            }

            if *y > 0 {
                if !p1_walls.contains(&(*x, (y - 1))) {
                    succ.push(((*x, (y - 1)), 1));
                }
            }

            if *y < height {
                if !p1_walls.contains(&(*x, (y + 1))) {
                    succ.push(((*x, (y + 1)), 1));
                }
            }

            succ
        },
        |(x, y)| (*x as i32 - 70).abs() as usize + (*y as i32 - 70).abs() as usize,
        |&n| n == (width, height),
    )
    .unwrap();

    println!("p1: {}", steps);

    let p2 = (0..walls.len())
        .find_map(|i| {
            let p2_walls = walls[0..i]
                .iter()
                .map(|l| l.clone())
                .collect::<HashSet<_>>();

            let res = astar::astar(
                &(0, 0),
                |(x, y)| {
                    let mut succ: Vec<((usize, usize), usize)> = Vec::new();

                    if *x > 0 {
                        if !p2_walls.contains(&((x - 1), *y)) {
                            succ.push(((x - 1, *y), 1));
                        }
                    }

                    if *x < width {
                        if !p2_walls.contains(&((x + 1), *y)) {
                            succ.push(((x + 1, *y), 1));
                        }
                    }

                    if *y > 0 {
                        if !p2_walls.contains(&(*x, (y - 1))) {
                            succ.push(((*x, (y - 1)), 1));
                        }
                    }

                    if *y < height {
                        if !p2_walls.contains(&(*x, (y + 1))) {
                            succ.push(((*x, (y + 1)), 1));
                        }
                    }

                    succ
                },
                |(x, y)| (*x as i32 - 70).abs() as usize + (*y as i32 - 70).abs() as usize,
                |&n| n == (width, height),
            );

            match res {
                Some(_) => None,
                None => Some((walls[i - 1].0, walls[i - 1].1)),
            }
        })
        .unwrap();

    println!("p2: {},{}", p2.0, p2.1);
}
