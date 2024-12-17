use std::{
    collections::HashSet,
    io::{self, BufRead},
};

fn move_robot(map: &mut Vec<Vec<char>>, mut location: (usize, usize), moves: &Vec<char>) {
    for m in moves {
        let (mx, my) = match m {
            '^' => (-1, 0),
            'v' => (1, 0),
            '<' => (0, -1),
            '>' => (0, 1),
            _ => unreachable!("Invalid move"),
        };

        let (mut x, mut y) = location;

        let mut c;
        loop {
            x = (x as i32 + mx) as usize;
            y = (y as i32 + my) as usize;

            c = map[x][y];

            if map[x][y] != 'O' {
                break;
            }
        }

        if c == '.' {
            if mx != 0 {
                let mut i = location.0 as i32 + mx;
                while i != x as i32 {
                    map[i as usize][location.1] = 'O';
                    i += mx;
                }
                map[i as usize][location.1] = 'O';
            }

            if my != 0 {
                let mut j = location.1 as i32 + my;
                while j != y as i32 {
                    map[location.0][j as usize] = 'O';
                    j += my;
                }
                map[location.0][j as usize] = 'O';
            }

            map[location.0][location.1] = '.';
            map[(location.0 as i32 + mx) as usize][(location.1 as i32 + my) as usize] = '.';

            location.0 = ((location.0 as i32) + mx) as usize;
            location.1 = ((location.1 as i32) + my) as usize;
        }
    }
}

fn move_robot2(map: &mut Vec<Vec<char>>, mut location: (usize, usize), moves: &Vec<char>) {
    for m in moves {
        let (mx, my) = match m {
            '^' => (-1, 0),
            'v' => (1, 0),
            '<' => (0, -1),
            '>' => (0, 1),
            _ => unreachable!("Invalid move"),
        };

        let (x, y) = location;

        let nc = map[(x as i32 + mx) as usize][(y as i32 + my) as usize];

        if nc == '#' {
        } else if nc == '.' {
            location.0 = (x as i32 + mx) as usize;
            location.1 = (y as i32 + my) as usize;
        } else if nc == '[' || nc == ']' {
            let res = if nc == '[' {
                detect_boxes(
                    map,
                    ((x as i32 + mx) as usize, (y as i32 + my) as usize),
                    mx,
                    my,
                )
            } else {
                detect_boxes(
                    map,
                    ((x as i32 + mx) as usize, (y as i32 + my) as usize - 1),
                    mx,
                    my,
                )
            };

            match res {
                MoveOrNo::Move(v) => {
                    for (i, j) in v.clone() {
                        map[i][j] = '.';
                        map[i][j + 1] = '.';
                    }

                    for (i, j) in v {
                        map[(i as i32 + mx) as usize][(j as i32 + my) as usize] = '[';
                        map[(i as i32 + mx) as usize][(j as i32 + my) as usize + 1] = ']';
                    }

                    location.0 = (x as i32 + mx) as usize;
                    location.1 = (y as i32 + my) as usize;
                }
                MoveOrNo::No => {}
            }
        }
    }
}

enum MoveOrNo {
    Move(HashSet<(usize, usize)>),
    No,
}

impl MoveOrNo {
    fn bind(self, o: MoveOrNo) -> MoveOrNo {
        match self {
            MoveOrNo::Move(v) => match o {
                MoveOrNo::Move(v2) => MoveOrNo::Move(v.into_iter().chain(v2).collect()),
                MoveOrNo::No => MoveOrNo::No,
            },
            MoveOrNo::No => MoveOrNo::No,
        }
    }
}

fn print_map(map: &Vec<Vec<char>>, loc: (usize, usize)) {
    for (i, l) in map.iter().enumerate() {
        for (j, c) in l.iter().enumerate() {
            if (i, j) == loc {
                print!("@");
            } else {
                print!("{}", c);
            }
        }
        println!();
    }
    println!();
}

fn detect_boxes(map: &Vec<Vec<char>>, bl: (usize, usize), mx: i32, my: i32) -> MoveOrNo {
    assert!(map[bl.0][bl.1] == '[');

    if my != 0 {
        let v: HashSet<_> = vec![(bl.0, bl.1)].into_iter().collect();
        if map[bl.0][(bl.1 as i32 + my) as usize] == '.' {
            return MoveOrNo::Move(v);
        } else if map[bl.0][(bl.1 as i32 + my) as usize] == '#' {
            return MoveOrNo::No;
        } else {
            if my > 0 {
                if map[bl.0][(bl.1 as i32 + 2 * my) as usize] == '.' {
                    return MoveOrNo::Move(v);
                } else if map[bl.0][(bl.1 as i32 + 2 * my) as usize] == '#' {
                    return MoveOrNo::No;
                } else if map[bl.0][(bl.1 as i32 + 2 * my) as usize] == '[' {
                    return MoveOrNo::Move(v).bind(detect_boxes(
                        map,
                        (bl.0, (bl.1 as i32 + 2 * my) as usize),
                        mx,
                        my,
                    ));
                }
            } else if map[bl.0][(bl.1 as i32 + my) as usize] == ']' {
                return MoveOrNo::Move(v).bind(detect_boxes(
                    map,
                    (bl.0, (bl.1 as i32 + 2 * my) as usize),
                    mx,
                    my,
                ));
            }
        }

        unreachable!();
    } else if mx != 0 {
        let v: HashSet<_> = vec![(bl.0, bl.1)].into_iter().collect();
        if map[(bl.0 as i32 + mx) as usize][bl.1] == '#' {
            return MoveOrNo::No;
        } else if map[(bl.0 as i32 + mx) as usize][bl.1 + 1] == '#' {
            return MoveOrNo::No;
        } else if ['[', ']'].contains(&map[(bl.0 as i32 + mx) as usize][bl.1])
            || ['[', ']'].contains(&map[(bl.0 as i32 + mx) as usize][(bl.1 + 1) as usize])
        {
            let mut res = vec![];
            if map[(bl.0 as i32 + mx) as usize][bl.1] == '[' {
                res.push(detect_boxes(
                    map,
                    ((bl.0 as i32 + mx) as usize, bl.1),
                    mx,
                    my,
                ));
            }

            if map[(bl.0 as i32 + mx) as usize][bl.1 + 1] == '[' {
                res.push(detect_boxes(
                    map,
                    ((bl.0 as i32 + mx) as usize, bl.1 + 1),
                    mx,
                    my,
                ));
            }

            if map[(bl.0 as i32 + mx) as usize][bl.1] == ']' {
                res.push(detect_boxes(
                    map,
                    ((bl.0 as i32 + mx) as usize, bl.1 - 1),
                    mx,
                    my,
                ));
            }

            if map[(bl.0 as i32 + mx) as usize][bl.1 + 1] == ']' {
                res.push(detect_boxes(
                    map,
                    ((bl.0 as i32 + mx) as usize, bl.1),
                    mx,
                    my,
                ));
            }

            return res
                .into_iter()
                .fold(MoveOrNo::Move(v), |acc, x| acc.bind(x));
        } else if map[(bl.0 as i32 + mx) as usize][bl.1] == '.'
            && map[(bl.0 as i32 + mx) as usize][bl.1 + 1] == '.'
        {
            return MoveOrNo::Move(v);
        }
        unreachable!();
    }

    unreachable!();
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle.lines().map(|l| l.unwrap()).collect::<Vec<_>>();

    let (map, moves) = lines.split_at(lines.iter().position(|l| l.is_empty()).unwrap());

    let mut map = map
        .iter()
        .map(|l| l.chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let map2 = map.clone();

    let moves = moves
        .iter()
        .flat_map(|l| l.as_str().chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let location = map
        .iter()
        .enumerate()
        .find_map(|(i, l)| {
            l.iter()
                .enumerate()
                .find_map(|(j, c)| if *c == '@' { Some((i, j)) } else { None })
        })
        .unwrap();

    map[location.0][location.1] = '.';

    move_robot(&mut map, location, &moves);

    let p1 = map
        .iter()
        .enumerate()
        .map(|(i, l)| {
            l.iter()
                .enumerate()
                .filter(|(_, c)| **c == 'O')
                .map(|(j, _)| (i * 100 + j))
                .sum::<usize>()
        })
        .sum::<usize>();

    println!("p1: {}", p1);

    let mut map2 = map2
        .into_iter()
        .map(|l| {
            l.into_iter()
                .map(|c| match c {
                    'O' => "[]".chars(),
                    '.' => "..".chars(),
                    '@' => "@.".chars(),
                    '#' => "##".chars(),
                    _ => unreachable!(),
                })
                .flatten()
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let location = map2
        .iter()
        .enumerate()
        .find_map(|(i, l)| {
            l.iter()
                .enumerate()
                .find_map(|(j, c)| if *c == '@' { Some((i, j)) } else { None })
        })
        .unwrap();

    map2[location.0][location.1] = '.';

    print_map(&map2, location);
    move_robot2(&mut map2, location, &moves);

    let p2 = map2
        .iter()
        .enumerate()
        .map(|(i, l)| {
            l.iter()
                .enumerate()
                .filter(|(_, c)| **c == '[')
                .map(|(j, _)| (i * 100 + j))
                .sum::<usize>()
        })
        .sum::<usize>();

    println!("p2: {}", p2);
}
