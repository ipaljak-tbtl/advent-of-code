use std::{
    collections::{HashMap, HashSet},
    io::{self, BufRead},
};

fn scan_region(
    map: &Vec<Vec<char>>,
    visited: &mut HashSet<(usize, usize)>,
    x: usize,
    y: usize,
    c: char,
) -> (usize, usize, usize) {
    let mut stack = vec![(x as i32, y as i32)];

    let mut fence_count = 0;
    let mut area_count = 0;
    let mut sides_count = 0;

    let width = map.len() as i32;
    let height = map[0].len() as i32;

    while let Some((x, y)) = stack.pop() {
        if visited.contains(&(x as usize, y as usize)) {
            continue;
        } else {
            visited.insert((x as usize, y as usize));
        }

        if map[x as usize][y as usize] == c {
            area_count += 1;
        } else {
            continue;
        }

        let x = x as i32;
        let y = y as i32;

        let adjacents = [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)];

        for (nx, ny) in adjacents.iter() {
            if *nx == -1 || *nx == width {
                fence_count += 1;
                continue;
            }

            if *ny == -1 || *ny == height {
                fence_count += 1;
                continue;
            }

            if map[*nx as usize][*ny as usize] == c {
                stack.push((*nx, *ny));
            } else {
                fence_count += 1;
            }
        }

        let sides_cases = [
            ([true, false, false, false], 2),
            ([false, true, false, false], 2),
            ([false, false, true, false], 2),
            ([false, false, false, true], 2),
            //
            ([true, true, true, false], 2),
            ([true, true, false, true], 2),
            ([true, false, true, true], 2),
            ([false, true, true, true], 2),
            //
            ([true, false, true, false], 1),
            ([false, true, false, true], 1),
            ([true, false, false, true], 1),
            ([false, true, true, false], 1),
            //
            ([false, false, false, false], 4),
        ];

        for sc in sides_cases.iter() {
            let is_edge = sc.0.iter().enumerate().all(|(i, should_be_same)| {
                let (nx, ny) = adjacents[i];

                if nx == -1 || nx == width {
                    return !should_be_same;
                }

                if ny == -1 || ny == height {
                    return !should_be_same;
                }

                if map[nx as usize][ny as usize] == c {
                    return *should_be_same;
                }

                !should_be_same
            });

            if is_edge {
                sides_count += sc.1;
            }
        }
    }

    (fence_count, area_count, sides_count)
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let map = handle
        .lines()
        .map(|l| l.unwrap().chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut regions: HashMap<char, Vec<(usize, usize, usize)>> = HashMap::new();

    let mut visited: HashSet<(usize, usize)> = HashSet::new();

    for (x, row) in map.iter().enumerate() {
        for (y, &c) in row.iter().enumerate() {
            let (fence_count, area_count, sides_count) = scan_region(&map, &mut visited, x, y, c);

            if let Some(v) = regions.get_mut(&c) {
                v.push((fence_count, area_count, sides_count));
            } else {
                regions.insert(c, vec![(fence_count, area_count, sides_count)]);
            }
        }
    }

    let p1 = regions
        .iter()
        .map(|(_, v)| {
            v.iter()
                .map(|(fence_count, area_count, _)| fence_count * area_count)
                .sum::<usize>()
        })
        .sum::<usize>();

    println!("p1: {}", p1);

    let p2 = regions
        .iter()
        .map(|(c, v)| {
            v.iter()
                .map(|(_, area_count, sides_count)| {
                    println!("{} {} {}", c, area_count, sides_count);
                    sides_count * area_count
                })
                .sum::<usize>()
        })
        .sum::<usize>();

    println!("p2: {}", p2);
}
