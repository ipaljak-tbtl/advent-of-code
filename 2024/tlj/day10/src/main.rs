use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn find_trails(map: &Vec<Vec<usize>>, trailhead: (usize, usize)) -> (u32, u32) {
    let mut peaks = HashSet::<(usize, usize)>::new();

    let mut unique_paths = HashSet::<Vec<(usize, usize)>>::new();

    let mut stack = vec![(trailhead.0, trailhead.1, 0, Vec::<(usize, usize)>::new())];

    while let Some((i, j, h, mut trail)) = stack.pop() {
        trail.push((i, j));

        if h == 9 {
            peaks.insert((i, j));
            unique_paths.insert(trail.clone());
        }

        if i > 0 && map[i - 1][j] == h + 1 {
            stack.push((i - 1, j, map[i - 1][j], trail.clone()));
        }

        if i < map.len() - 1 && map[i + 1][j] == h + 1 {
            stack.push((i + 1, j, map[i + 1][j], trail.clone()));
        }

        if j > 0 && map[i][j - 1] == h + 1 {
            stack.push((i, j - 1, map[i][j - 1], trail.clone()));
        }

        if j < map[i].len() - 1 && map[i][j + 1] == h + 1 {
            stack.push((i, j + 1, map[i][j + 1], trail.clone()));
        }
    }

    (peaks.len() as u32, unique_paths.len() as u32)
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let map = handle
        .lines()
        .map(|l| {
            l.unwrap()
                .chars()
                .map(|c| c.to_digit(10).unwrap() as usize)
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let trailheads = map
        .iter()
        .enumerate()
        .flat_map(|(i, l)| {
            l.iter()
                .enumerate()
                .filter_map(|(j, h)| if *h == 0 { Some((i, j)) } else { None })
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let p1 = trailheads
        .iter()
        .map(|(i, j)| find_trails(&map, (*i, *j)).0)
        .sum::<u32>();

    println!("p1: {}", p1);

    let p2 = trailheads
        .iter()
        .map(|(i, j)| find_trails(&map, (*i, *j)).1)
        .sum::<u32>();

    println!("p2: {}", p2);
}
