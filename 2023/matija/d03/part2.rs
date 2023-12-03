use std::collections::{HashMap, HashSet};

fn main() {
    let in_lines: Vec<Vec<char>> = std::io::stdin()
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    let deltas = [
        (-1, -1),
        (-1, 0),
        (-1, 1),
        (0, -1),
        (0, 1),
        (1, -1),
        (1, 0),
        (1, 1),
    ];

    let mut gears = HashMap::<(usize, usize), Vec<u32>>::new();

    for (ir, line) in in_lines.iter().enumerate() {
        let mut n_current = 0u32;

        let mut curr_gears = HashSet::<(usize, usize)>::new();

        for (ic, c) in line.iter().enumerate() {
            if let Some(d) = c.to_digit(10) {
                n_current = n_current * 10 + d;

                for (dr, dc) in deltas {
                    let r = ir as i64 + dr;
                    let c = ic as i64 + dc;

                    let r = if r >= 0 { r as usize } else { continue };
                    let c = if c >= 0 { c as usize } else { continue };

                    if r >= in_lines.len() || c >= in_lines[r].len() {
                        continue;
                    }

                    if in_lines[r][c] == '*' {
                        curr_gears.insert((r, c));
                    }
                }
            } else {
                for gear in curr_gears.iter() {
                    gears.entry(*gear).or_default().push(n_current);
                }

                n_current = 0u32;
                curr_gears.clear();
            }
        }

        for gear in curr_gears {
            gears.entry(gear).or_default().push(n_current);
        }
    }

    let mut result = 0u32;

    for ns in gears.values() {
        if ns.len() == 2 {
            result += ns[0] * ns[1];
        }
    }

    println!("{result}")
}
