use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle
        .lines()
        .map(|l| l.unwrap())
        .filter(|l| !l.is_empty())
        .collect::<Vec<_>>();

    let mut sum_tokens: u64 = 0;
    let mut sum_tokens2: u64 = 0;
    for game in lines.chunks(3) {
        let la = game[0].strip_prefix("Button A: ").unwrap();
        let la = la.split(',').collect::<Vec<_>>();
        let x1 = la[0].split('+').collect::<Vec<_>>()[1]
            .trim()
            .parse::<f64>()
            .unwrap();
        let y1 = la[1].split('+').collect::<Vec<_>>()[1]
            .trim()
            .parse::<f64>()
            .unwrap();

        let lb = game[1].strip_prefix("Button B: ").unwrap();
        let lb = lb.split(',').collect::<Vec<_>>();
        let x2 = lb[0].split('+').collect::<Vec<_>>()[1]
            .trim()
            .parse::<f64>()
            .unwrap();
        let y2 = lb[1].split('+').collect::<Vec<_>>()[1]
            .trim()
            .parse::<f64>()
            .unwrap();

        let lp = game[2].strip_prefix("Prize: ").unwrap();
        let lp = lp.split(',').collect::<Vec<_>>();
        let xx = lp[0].split('=').collect::<Vec<_>>()[1]
            .trim()
            .parse::<f64>()
            .unwrap();
        let yy = lp[1].split('=').collect::<Vec<_>>()[1]
            .trim()
            .parse::<f64>()
            .unwrap();

        let a = (xx * y2 - x2 * yy) / (x1 * y2 - y1 * x2);
        let b = (yy - y1 * a) / y2;

        if a.fract() == 0.0 && b.fract() == 0.0 {
            sum_tokens += a as u64 * 3 + b as u64;
        }

        // part 2
        let xx = xx + 10000000000000.0;
        let yy = yy + 10000000000000.0;

        let a = (xx * y2 - x2 * yy) / (x1 * y2 - y1 * x2);
        let b = (yy - y1 * a) / y2;

        if a.fract() == 0.0 && b.fract() == 0.0 {
            sum_tokens2 += a as u64 * 3 + b as u64;
        }
    }

    println!("p1: {}", sum_tokens);
    println!("p2: {}", sum_tokens2);
}
