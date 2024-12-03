use itertools::Itertools;

fn main() {
    let input = std::fs::read_to_string("in.txt").unwrap();

    let re = regex::Regex::new(r"mul\((\d+),(\d+)\)").unwrap();

    let do_re = regex::Regex::new(r"do\(\)").unwrap();
    let dont_re = regex::Regex::new(r"don't\(\)").unwrap();

    // get all indexes of dos
    let dos: Vec<_> = do_re.find_iter(&input).map(|m| m.start()).collect();

    // get all indexes of don'ts
    let donts: Vec<_> = dont_re.find_iter(&input).map(|m| m.start()).collect();

    #[derive(Debug, Clone, Copy)]
    enum DoDont {
        Do(usize),
        Dont(usize),
    }

    let mut dodonts = vec![DoDont::Do(0)];

    for do_ in dos {
        dodonts.push(DoDont::Do(do_));
    }

    for dont in donts {
        dodonts.push(DoDont::Dont(dont));
    }

    dodonts.push(DoDont::Dont(input.len()));

    dodonts.sort_by_key(|k| match k {
        DoDont::Do(k) => *k,
        DoDont::Dont(k) => *k,
    });

    let mut sum1 = 0;

    for (_, [a, b]) in re.captures_iter(&input).map(|c| c.extract()) {
        let a = a.parse::<i64>().unwrap();
        let b = b.parse::<i64>().unwrap();
        sum1 += a * b;
    }

    let mut sum2 = 0;
    for c in re.captures_iter(&input) {
        let pos = c.get(0).unwrap().start();

        let a = c[1].parse::<i64>().unwrap();
        let b = c[2].parse::<i64>().unwrap();

        // pos should be between a do and a dont and not between a dont and a do
        for (p, n) in dodonts.iter().tuple_windows() {
            match (p, n) {
                (DoDont::Do(p), DoDont::Dont(n)) => {
                    if pos > *p && pos < *n {
                        sum2 += a * b;
                    }
                }
                (DoDont::Do(p), DoDont::Do(n)) => {
                    if pos > *p && pos < *n {
                        sum2 += a * b;
                    }
                }
                _ => {}
            }
        }
    }

    println!("p1: {}", sum1);
    println!("p2: {}", sum2);
}
