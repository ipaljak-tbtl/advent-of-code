fn solve(reader: impl std::io::BufRead) -> u32 {
    let (mut ci, mut cj) = (0, 0);

    let ps: Vec<Vec<char>> = reader
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

    let is_north = ci > 0 && matches!(ps[ci - 1][cj], '|' | '7' | 'F');
    let is_south = ci + 1 < ps.len() && matches!(ps[ci + 1][cj], '|' | 'L' | 'J');

    let (mut pi, mut pj) = (ci, cj);

    if is_north {
        ci -= 1;
    } else if is_south {
        ci += 1;
    } else {
        cj += 1;
    }

    let mut len = 1;

    while ps[ci][cj] != 'S' {
        len += 1;

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

    len / 2
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d10p1_1() {
        let reader = BufReader::new(File::open("d10/test_input1_1.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 4);
    }

    #[test]
    fn test_d10p1_2() {
        let reader = BufReader::new(File::open("d10/test_input1_2.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 8);
    }
}
