use std::{
    collections::HashSet,
    io::{self, BufRead},
};

#[derive(Debug, Clone, Copy)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
}

enum Guard {
    Turn(usize, usize, Direction),
    Leave,
    Loop,
}

fn traverse(
    map: &Vec<Vec<char>>,
    visited: &mut HashSet<(usize, usize)>,
    x: usize,
    y: usize,
    dir: Direction,
    step_count: &mut usize,
) -> Guard {
    const MAX_STEP_COUNT: usize = 100000;

    match dir {
        Direction::Up => {
            let mut xi: i64 = x as i64;
            loop {
                *step_count += 1;
                if *step_count > MAX_STEP_COUNT {
                    return Guard::Loop;
                }

                visited.insert((xi as usize, y));
                if xi - 1 < 0 {
                    return Guard::Leave;
                }

                if map[xi as usize - 1][y] == '#' {
                    return Guard::Turn(xi as usize, y, Direction::Right);
                }

                xi -= 1;
            }
        }
        Direction::Down => {
            let mut xi = x;
            loop {
                *step_count += 1;
                if *step_count > MAX_STEP_COUNT {
                    return Guard::Loop;
                }

                visited.insert((xi, y));
                if xi + 1 >= map.len() {
                    return Guard::Leave;
                }

                if map[xi + 1][y] == '#' {
                    return Guard::Turn(xi, y, Direction::Left);
                }

                xi += 1;
            }
        }
        Direction::Left => {
            let mut yi = y as i64;
            loop {
                *step_count += 1;
                if *step_count > MAX_STEP_COUNT {
                    return Guard::Loop;
                }

                visited.insert((x, yi as usize));
                if yi - 1 < 0 {
                    return Guard::Leave;
                }

                if map[x][yi as usize - 1] == '#' {
                    return Guard::Turn(x, yi as usize, Direction::Up);
                }

                yi -= 1;
            }
        }
        Direction::Right => {
            let mut yi = y;
            loop {
                *step_count += 1;
                if *step_count > MAX_STEP_COUNT {
                    return Guard::Loop;
                }

                visited.insert((x, yi));
                if yi + 1 >= map[x].len() {
                    return Guard::Leave;
                }

                if map[x][yi + 1] == '#' {
                    return Guard::Turn(x, yi, Direction::Down);
                }

                yi += 1;
            }
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle
        .lines()
        .map(|l| l.unwrap().chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut visited = HashSet::new();

    let mut start_x = 0;
    let mut start_y = 0;
    for (i, ci) in lines.iter().enumerate() {
        for (j, cj) in ci.iter().enumerate() {
            if *cj == '^' {
                start_x = i;
                start_y = j;

                let mut x = i;
                let mut y = j;
                let mut dir = Direction::Up;

                let mut step_count = 0;

                loop {
                    match traverse(&lines, &mut visited, x, y, dir, &mut step_count) {
                        Guard::Turn(nx, ny, ndir) => {
                            x = nx;
                            y = ny;
                            dir = ndir;
                        }
                        Guard::Leave => {
                            break;
                        }
                        Guard::Loop => {
                            unreachable!()
                        }
                    }
                }
            }
        }
    }

    let mut loop_count = 0;
    for (x, y) in &visited {
        let mut new_map = lines.clone();
        if new_map[*x][*y] == '.' {
            new_map[*x][*y] = '#';
        }

        let mut x = start_x;
        let mut y = start_y;
        let mut dir = Direction::Up;

        let mut new_visited = HashSet::new();
        let mut step_count = 0;

        loop {
            match traverse(&new_map, &mut new_visited, x, y, dir, &mut step_count) {
                Guard::Turn(nx, ny, ndir) => {
                    x = nx;
                    y = ny;
                    dir = ndir;
                }
                Guard::Leave => {
                    break;
                }
                Guard::Loop => {
                    loop_count += 1;
                    break;
                }
            }
        }
    }

    println!("p1: {}", visited.len());
    println!("p2: {}", loop_count);
}
