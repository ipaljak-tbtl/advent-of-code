fn is_symbol(x: char) -> bool {
    !x.is_ascii_digit() && x != '.'
}

fn solve(reader: impl std::io::BufRead) -> u32 {
    let schema: Vec<Vec<char>> = reader
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

    for (ir, line) in schema.iter().enumerate() {
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

                        if r >= schema.len() || c >= schema[r].len() {
                            continue;
                        }

                        if is_symbol(schema[r][c]) {
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

    result
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d03p1() {
        let reader = BufReader::new(File::open("d03/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 4361);
    }
}
