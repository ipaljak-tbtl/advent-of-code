use std::{
    collections::HashSet,
    io::{self, BufRead},
};

use pathfinding::prelude::astar_bag_collect;

#[derive(Clone, Copy, Eq, PartialEq, Debug, Hash)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
}

#[derive(Clone, Copy, Eq, PartialEq, Debug, Hash)]
struct Pos {
    x: usize,
    y: usize,
    dir: Direction,
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let map = handle
        .lines()
        .map(|l| l.unwrap().chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let start_pos = map
        .iter()
        .enumerate()
        .find_map(|(i, l)| {
            l.iter().enumerate().find_map(|(j, c)| {
                if *c == 'S' {
                    Some(Pos {
                        x: i,
                        y: j,
                        dir: Direction::Right,
                    })
                } else {
                    None
                }
            })
        })
        .unwrap();

    let end_pos = map
        .iter()
        .enumerate()
        .find_map(|(i, l)| {
            l.iter()
                .enumerate()
                .find_map(|(j, c)| if *c == 'E' { Some((i, j)) } else { None })
        })
        .unwrap();

    let res = astar_bag_collect(
        &start_pos,
        |pos| {
            let mut next_moves = match pos.dir {
                Direction::Up => vec![Direction::Left, Direction::Right],
                Direction::Down => vec![Direction::Right, Direction::Left],
                Direction::Left => vec![Direction::Down, Direction::Up],
                Direction::Right => vec![Direction::Up, Direction::Down],
            }
            .into_iter()
            .map(|dir| {
                (
                    Pos {
                        x: pos.x,
                        y: pos.y,
                        dir,
                    },
                    1000,
                )
            })
            .collect::<Vec<_>>();

            let (nx, ny) = match pos.dir {
                Direction::Up => (pos.x - 1, pos.y),
                Direction::Down => (pos.x + 1, pos.y),
                Direction::Left => (pos.x, pos.y - 1),
                Direction::Right => (pos.x, pos.y + 1),
            };

            if map[nx][ny] != '#' {
                next_moves.push((
                    Pos {
                        x: nx,
                        y: ny,
                        dir: pos.dir,
                    },
                    1,
                ));
            }

            next_moves
        },
        |pos| (pos.x as i32 - end_pos.0 as i32).abs() + (pos.y as i32 - end_pos.1 as i32).abs(),
        |pos| pos.x == end_pos.0 && pos.y == end_pos.1,
    )
    .unwrap();

    println!("p1: {}", res.1);

    let p2 = res
        .0
        .into_iter()
        .flatten()
        .map(|p| (p.x, p.y))
        .collect::<HashSet<_>>()
        .len();

    println!("p2: {}", p2);
}
