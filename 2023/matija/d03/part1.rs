fn is_symbol(x: char) -> bool {
    !x.is_ascii_digit() && x != '.'
}

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

    let mut result = 0u32;

    for (ir, line) in in_lines.iter().enumerate() {
        let mut is_part_number = false;
        let mut n_current = 0u32;

        for (ic, c) in line.iter().enumerate() {
            if let Some(d) = c.to_digit(10) {
                n_current = n_current * 10 + d;

                if !is_part_number {
                    for (dr, dc) in deltas {
                        let r = ir as i64 + dr;
                        let c = ic as i64 + dc;

                        let r = if r >= 0 { r as usize } else { continue };
                        let c = if c >= 0 { c as usize } else { continue };

                        if r >= in_lines.len() || c >= in_lines[r].len() {
                            continue;
                        }

                        if is_symbol(in_lines[r][c]) {
                            is_part_number = true;
                        }
                    }
                }
            } else {
                if is_part_number {
                    result += n_current;
                }

                n_current = 0u32;
                is_part_number = false;
            }
        }

        if is_part_number {
            result += n_current;
        }
    }

    println!("{result}")
}
