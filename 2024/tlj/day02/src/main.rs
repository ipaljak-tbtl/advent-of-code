use itertools::Itertools;

fn is_safe(r: &&Vec<i64>) -> bool {
    #[derive(Debug, PartialEq)]
    enum UpDown {
        Up,
        Down,
    }
    let mut up_down = None;
    for (p, n) in r.iter().tuple_windows() {
        if p < n {
            if up_down == Some(UpDown::Down) {
                return false;
            }
            up_down = Some(UpDown::Up);
        } else if p > n {
            if up_down == Some(UpDown::Up) {
                return false;
            }
            up_down = Some(UpDown::Down);
        } else {
            return false;
        }
        if (p - n).abs() > 3 {
            return false;
        }
    }

    true
}

fn main() {
    let file = std::fs::read_to_string("in.txt").unwrap();
    let lines: Vec<&str> = file.lines().filter(|l| *l != "\n").collect();

    let reports = lines
        .into_iter()
        .map(|l| {
            l.split_whitespace()
                .map(|l| l.parse::<i64>().unwrap())
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    dbg!(&reports);

    let n_safe = reports.iter().filter(is_safe).count();

    let n_safe_2 = reports
        .iter()
        .filter(|r| {
            for i in 0..r.len() {
                let mut r2 = (*r).clone();
                r2.remove(i);

                if is_safe(&&r2) {
                    return true;
                }
            }

            false
        })
        .count();

    println!("p1: {}", n_safe);
    println!("p2: {}", n_safe_2);
}
