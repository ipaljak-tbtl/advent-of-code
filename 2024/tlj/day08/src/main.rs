use std::{
    collections::{HashMap, HashSet},
    io::{self, BufRead},
};

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let map = handle
        .lines()
        .map(|l| l.unwrap().chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut nodes = HashMap::<char, Vec<(i64, i64)>>::new();

    for (i, row) in map.iter().enumerate() {
        for (j, ch) in row.iter().enumerate() {
            if *ch == '.' {
                continue;
            }

            let mut positions = nodes.remove(ch).unwrap_or_default();

            positions.push((i as i64, j as i64));

            nodes.insert(*ch, positions);
        }
    }

    let mut antinodes = HashSet::<(i64, i64)>::new();

    let height = map.len() as i64;
    let width = map[0].len() as i64;

    for (_, positions) in nodes.iter() {
        for i in 0..positions.len() {
            for j in i + 1..positions.len() {
                let (x1, y1) = positions[i];
                let (x2, y2) = positions[j];

                let antix1 = x1 - (x2 - x1);
                let antiy1 = y1 - (y2 - y1);

                let antix2 = x2 + (x2 - x1);
                let antiy2 = y2 + (y2 - y1);

                if antix1 >= 0 && antix1 < height && antiy1 >= 0 && antiy1 < width {
                    antinodes.insert((antix1, antiy1));
                }

                if antix2 >= 0 && antix2 < height && antiy2 >= 0 && antiy2 < width {
                    antinodes.insert((antix2, antiy2));
                }
            }
        }
    }

    let n_antinodes = antinodes.len();

    println!("p1: {}", n_antinodes);

    for (_, positions) in nodes.iter() {
        for i in 0..positions.len() {
            for j in i + 1..positions.len() {
                for k in 0..width {
                    let (x1, y1) = positions[i];
                    let (x2, y2) = positions[j];

                    let antix1 = x1 - (x2 - x1) * k;
                    let antiy1 = y1 - (y2 - y1) * k;

                    let antix2 = x2 + (x2 - x1) * k;
                    let antiy2 = y2 + (y2 - y1) * k;

                    if antix1 >= 0 && antix1 < height && antiy1 >= 0 && antiy1 < width {
                        antinodes.insert((antix1, antiy1));
                    }

                    if antix2 >= 0 && antix2 < height && antiy2 >= 0 && antiy2 < width {
                        antinodes.insert((antix2, antiy2));
                    }
                }
            }
        }
    }

    let n_antinodes = antinodes.len();

    println!("p2: {}", n_antinodes);
}
