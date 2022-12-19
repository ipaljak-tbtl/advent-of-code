pub fn solve(input: &[String]) -> u32 {
    const X_MIN: usize = 200;
    const X_MAX: usize = 800;
    const Y_MAX: usize = 200;

    let mut grid = [['.'; X_MAX - X_MIN]; Y_MAX];

    for line in input {
        let mut line_iter = line.split(" -> ");
        let first: Vec<&str> = line_iter.next().unwrap().split(',').collect();

        let (mut x_prev, mut y_prev) = (
            first[0].parse::<usize>().unwrap() - X_MIN,
            first[1].parse().unwrap(),
        );

        for point in line_iter {
            let pair: Vec<&str> = point.split(',').collect();
            let x: usize = pair[0].parse::<usize>().unwrap() - X_MIN;
            let y: usize = pair[1].parse().unwrap();

            if x == x_prev {
                let (from, to) = if y_prev > y {
                    (y, y_prev + 1)
                } else {
                    (y_prev, y + 1)
                };

                for row in grid.iter_mut().take(to).skip(from) {
                    row[x] = '#';
                }
            } else {
                let (from, to) = if x_prev > x {
                    (x, x_prev + 1)
                } else {
                    (x_prev, x + 1)
                };

                for i in from..to {
                    grid[y][i] = '#';
                }
            }

            x_prev = x;
            y_prev = y;
        }
    }

    let mut sands = 0;
    let mut done = false;

    loop {
        let (mut x, mut y) = (500 - X_MIN, 0);

        loop {
            if y + 1 >= Y_MAX {
                done = true;
                break;
            }

            if grid[y + 1][x] == '.' {
                y += 1;
            } else if grid[y + 1][x - 1] == '.' {
                x -= 1;
                y += 1;
            } else if grid[y + 1][x + 1] == '.' {
                x += 1;
                y += 1;
            } else {
                break;
            }
        }

        if done {
            break;
        }

        grid[y][x] = 'o';
        sands += 1;
    }

    sands
}
