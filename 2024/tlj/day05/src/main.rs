use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle
        .lines()
        .map(|l| l.unwrap())
        .filter(|l| l != "\n")
        .collect::<Vec<_>>();

    let lines = lines.split(|l| l == "").collect::<Vec<_>>();

    let ordering_init = lines[0]
        .iter()
        .map(|l| {
            let mut l = l.split('|');
            let a = l.next().unwrap().parse::<i64>().unwrap();
            let b = l.next().unwrap().parse::<i64>().unwrap();
            (a, b)
        })
        .collect::<Vec<_>>();

    let mut ordering = ordering_init.clone();

    ordering.sort_by(|a, b| {
        if ordering_init.contains(&(a.0, b.0)) {
            std::cmp::Ordering::Less
        } else if ordering_init.contains(&(b.0, a.0)) {
            std::cmp::Ordering::Greater
        } else {
            std::cmp::Ordering::Equal
        }
    });

    let mut ordering = ordering.into_iter().map(|(a, _)| a).collect::<Vec<_>>();
    ordering.dedup();

    let is_ordered = |a: i64, b: i64| {
        if ordering_init.contains(&(a, b)) {
            true
        } else if ordering_init.contains(&(b, a)) {
            false
        } else {
            true
        }
    };

    let p1: i64 = lines[1]
        .iter()
        .filter_map(|l| {
            let list = l
                .split(',')
                .map(|l| l.parse::<i64>().unwrap())
                .collect::<Vec<_>>();
            let sorted = list.iter().is_sorted_by(|&&a, &&b| is_ordered(a, b));

            if sorted {
                Some(list)
            } else {
                None
            }
        })
        .map(|o| o[o.len() / 2])
        .sum();

    let p2: i64 = lines[1]
        .iter()
        .filter_map(|l| {
            let mut list = l
                .split(',')
                .map(|l| l.parse::<i64>().unwrap())
                .collect::<Vec<_>>();

            let sorted = list.iter().is_sorted_by(|&&a, &&b| is_ordered(a, b));

            if sorted {
                return None;
            }

            list.sort_by(|a, b| {
                if is_ordered(*a, *b) {
                    std::cmp::Ordering::Less
                } else {
                    std::cmp::Ordering::Greater
                }
            });

            Some(list)
        })
        .map(|o| o[o.len() / 2])
        .sum();

    println!("p1: {}", p1);
    println!("p2: {}", p2);
}
