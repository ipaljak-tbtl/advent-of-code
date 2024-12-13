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
) -> (usize, usize, HashSet<(usize, usize)>) {
    let mut stack = vec![(x as i32, y as i32)];

    let mut fence_count = 0;
    let mut area_count = 0;
    let width = map.len() as i32;
    let height = map[0].len() as i32;

    let mut region = HashSet::new();

    while let Some((x, y)) = stack.pop() {
        if visited.contains(&(x as usize, y as usize)) {
            continue;
        } else {
            visited.insert((x as usize, y as usize));
        }

        region.insert((x as usize, y as usize));

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
    }

    (fence_count, area_count, region)
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let map = handle
        .lines()
        .map(|l| l.unwrap().chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut regions: HashMap<char, Vec<(usize, usize, HashSet<(usize, usize)>)>> = HashMap::new();

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
        .map(|(_, v)| {
            v.iter()
                .map(|(_, area_count, region)| {
                    let mut edges_touching_count =
                        HashMap::<(usize, usize), Vec<(usize, usize)>>::new();

                    for (x, y) in region.iter() {
                        let edges = [(*x, *y), (*x + 1, *y), (*x, *y + 1), (*x + 1, *y + 1)];

                        for (nx, ny) in edges.iter() {
                            let area_list =
                                edges_touching_count.entry((*nx, *ny)).or_insert(vec![]);
                            area_list.push((*x, *y));
                        }
                    }

                    let edges = edges_touching_count
                        .iter()
                        .map(|(_, l)| {
                            if l.len() == 2 {
                                if l[0].0 == l[1].0 || l[0].1 == l[1].1 {
                                    return 0;
                                } else {
                                    return 2;
                                }
                            }

                            if l.len() % 2 == 0 {
                                0
                            } else {
                                1
                            }
                        })
                        .sum::<usize>();

                    edges * area_count
                })
                .sum::<usize>()
        })
        .sum::<usize>();

    println!("p2: {}", p2);
}
