use std::{
    collections::HashMap,
    io::{self, Read},
};

fn n_digits(n: i64) -> i64 {
    let mut n = n;
    let mut count = 0;

    while n > 0 {
        count += 1;
        n /= 10;
    }

    count
}

fn split_digits(n: i64, n_digits: i64) -> (i64, i64) {
    let mut a = n;
    let mut b = 0;

    let mut tmp = 1;
    for _ in 0..n_digits / 2 {
        b += tmp * (a % 10);
        tmp *= 10;
        a /= 10;
    }

    (a, b)
}

fn blink_stone(n: i64, depth: i64, max_depth: i64, cache: &mut HashMap<(i64, i64), i64>) -> i64 {
    if let Some(&res) = cache.get(&(n, max_depth - depth)) {
        return res;
    }

    if depth == max_depth {
        return 1;
    }

    if n == 0 {
        let res = blink_stone(1, depth + 1, max_depth, cache);

        cache.insert((n, max_depth - depth), res);

        res
    } else {
        let n_digits = n_digits(n);
        if n_digits % 2 == 0 {
            let (a, b) = split_digits(n, n_digits);
            let res = blink_stone(a, depth + 1, max_depth, cache)
                + blink_stone(b, depth + 1, max_depth, cache);

            cache.insert((n, max_depth - depth), res);

            return res;
        } else {
            let res = blink_stone(n * 2024, depth + 1, max_depth, cache);

            cache.insert((n, max_depth - depth), res);

            return res;
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let mut handle = stdin.lock();

    let mut line = String::new();
    handle.read_to_string(&mut line).unwrap();

    let stones = line
        .split_whitespace()
        .map(|s| s.parse::<i64>().unwrap())
        .collect::<Vec<_>>();

    let mut cache: HashMap<(i64, i64), i64> = HashMap::new();

    let len1 = stones
        .iter()
        .map(|s| blink_stone(*s, 0, 25, &mut cache))
        .sum::<i64>();

    println!("p1: {}", len1);

    let len2 = stones
        .iter()
        .map(|s| blink_stone(*s, 0, 75, &mut cache))
        .sum::<i64>();

    println!("p2: {}", len2);
}
