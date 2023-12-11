use std::collections::HashSet;

fn solve(reader: impl std::io::BufRead) -> u32 {
    let (mut ci, mut cj) = (0, 0);

    let mut ps: Vec<Vec<char>> = reader
        .lines()
        .enumerate()
        .map(|(i, line)| {
            let mut row = Vec::<char>::new();
            for (j, c) in line.unwrap().chars().enumerate() {
                row.push(c);

                if c == 'S' {
                    (ci, cj) = (i, j)
                }
            }
            row
        })
        .collect();

    let mut path = HashSet::new();
    path.insert((ci, cj));

    let is_north = ci > 0 && matches!(ps[ci - 1][cj], '|' | '7' | 'F');
    let is_south = ci + 1 < ps.len() && matches!(ps[ci + 1][cj], '|' | 'L' | 'J');
    let is_east = cj + 1 < ps[ci].len() && matches!(ps[ci][cj + 1], '-' | 'J' | '7');
    let is_west = cj > 0 && matches!(ps[ci][cj - 1], '-' | 'L' | 'F');

    let (mut pi, mut pj) = (ci, cj);

    if is_north {
        ci -= 1;
    } else if is_south {
        ci += 1;
    } else {
        cj += 1;
    }

    while ps[ci][cj] != 'S' {
        path.insert((ci, cj));

        let (temp_i, temp_j) = (ci, cj);

        match ps[ci][cj] {
            '|' => {
                if pi + 1 == ci {
                    ci += 1
                } else {
                    ci -= 1
                }
            }
            '-' => {
                if pj + 1 == cj {
                    cj += 1
                } else {
                    cj -= 1
                }
            }
            'L' => {
                if pi + 1 == ci {
                    cj += 1
                } else {
                    ci -= 1
                }
            }
            'J' => {
                if pi + 1 == ci {
                    cj -= 1
                } else {
                    ci -= 1
                }
            }
            '7' => {
                if pi == ci + 1 {
                    cj -= 1
                } else {
                    ci += 1
                }
            }
            'F' => {
                if pi == ci + 1 {
                    cj += 1
                } else {
                    ci += 1
                }
            }
            _ => unreachable!(),
        }

        (pi, pj) = (temp_i, temp_j)
    }

    ps[ci][cj] = if is_north && is_south {
        '|'
    } else if is_north && is_east {
        'L'
    } else if is_north && is_west {
        'J'
    } else if is_south && is_east {
        'F'
    } else if is_south && is_west {
        '7'
    } else {
        '-'
    };

    let mut result = 0;

    for (ti, row) in ps.iter().enumerate() {
        let mut cnt = 0;

        let mut horizontal_start = '.';

        for (tj, &curr) in row.iter().enumerate() {
            if path.contains(&(ti, tj)) {
                if curr == '-'
                    || curr == '7' && horizontal_start == 'L'
                    || curr == 'J' && horizontal_start == 'F'
                {
                    continue;
                }

                if curr == 'F' || curr == 'L' {
                    horizontal_start = curr;
                }

                cnt += 1;
            } else if cnt % 2 == 1 {
                result += 1;
            }
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
    fn test_d10p2_1() {
        let reader = BufReader::new(File::open("d10/test_input2_1.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 4);
    }

    #[test]
    fn test_d10p2_2() {
        let reader = BufReader::new(File::open("d10/test_input2_2.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 8);
    }

    #[test]
    fn test_d10p2_3() {
        let reader = BufReader::new(File::open("d10/test_input2_3.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 10);
    }
}
