use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle
        .lines()
        .map(|l| l.unwrap())
        .filter(|l| !l.is_empty())
        .collect::<Vec<_>>();

    let sim_time = 100;
    let width = 101;
    let height = 103;

    let mut quadrant_upper_left: i64 = 0;
    let mut quadrant_upper_right: i64 = 0;
    let mut quadrant_lower_left: i64 = 0;
    let mut quadrant_lower_right: i64 = 0;
    for l in &lines {
        let (x, y, vx, vy) =
            scan_fmt::scan_fmt!(&l, "p={},{} v={},{}", i64, i64, i64, i64).unwrap();

        let mut fx = (x + vx * sim_time) % width;
        let mut fy = (y + vy * sim_time) % height;

        if fx < 0 {
            fx = width + fx;
        }

        if fy < 0 {
            fy = height + fy;
        }

        if fx < width / 2 && fy < height / 2 {
            quadrant_upper_left += 1;
        } else if fx > width / 2 && fy < height / 2 {
            quadrant_upper_right += 1;
        } else if fx < width / 2 && fy > height / 2 {
            quadrant_lower_left += 1;
        } else if fx > width / 2 && fy > height / 2 {
            quadrant_lower_right += 1;
        }
    }

    let safety_factor =
        quadrant_lower_left * quadrant_lower_right * quadrant_upper_left * quadrant_upper_right;

    println!(
        "{} {} {} {}",
        quadrant_upper_left, quadrant_upper_right, quadrant_lower_left, quadrant_lower_right
    );

    println!("p1: {}", safety_factor);

    for sim in 0..10000 {
        println!("---------------------");
        println!("Simulation time: {}", sim);
        let mut map = vec![vec!['.'; width as usize]; height as usize];
        for l in &lines {
            let (x, y, vx, vy) =
                scan_fmt::scan_fmt!(&l, "p={},{} v={},{}", i64, i64, i64, i64).unwrap();

            let mut fx = (x + vx * sim) % width;
            let mut fy = (y + vy * sim) % height;

            if fx < 0 {
                fx = width + fx;
            }

            if fy < 0 {
                fy = height + fy;
            }

            map[fy as usize][fx as usize] = '#';
        }
        for i in (0..width).step_by(2) {
            for j in (0..height).step_by(2) {
                print!("{}", map[j as usize][i as usize]);
            }
            println!();
        }
    }
}
