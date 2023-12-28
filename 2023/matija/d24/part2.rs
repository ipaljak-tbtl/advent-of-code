use std::collections::{HashMap, HashSet};

type Line = ((i64, i64, i64), (i64, i64, i64));

fn parse_input(reader: impl std::io::BufRead) -> Vec<Line> {
    let mut lines = Vec::new();
    for line in reader.lines().map(Result::unwrap) {
        let spl: Vec<Vec<i64>> = line
            .split(" @ ")
            .map(|s| s.split(", ").map(|s| s.parse().unwrap()).collect())
            .collect();
        lines.push((
            (spl[0][0], spl[0][1], spl[0][2]),
            (spl[1][0], spl[1][1], spl[1][2]),
        ));
    }
    lines
}

fn prime_factors(mut n: i64) -> Vec<i64> {
    let mut factors = Vec::new();
    let mut done = false;
    while !done {
        done = true;
        for i in 2..((n as f64).sqrt().round() as i64 + 1) {
            if n % i == 0 {
                factors.push(i);
                n /= i;
                done = false;
                break;
            }
        }
    }
    factors.push(n);
    factors
}

fn common_elements(vectors: Vec<Vec<i64>>) -> Vec<i64> {
    let mut freqs: Vec<HashSet<(i64, usize)>> = Vec::new();

    for vector in vectors {
        let mut freq_ns: HashSet<(i64, usize)> = HashSet::new();
        let mut freq_map: HashMap<i64, usize> = HashMap::new();
        for num in vector {
            let n = freq_map.entry(num).or_insert(0);
            *n += 1;
            freq_ns.insert((num, *n));
        }
        freqs.push(freq_ns);
    }

    let mut fs = freqs[0].clone();
    for freq in &freqs[1..] {
        fs = fs.intersection(freq).copied().collect();
    }

    let mut result: Vec<i64> = fs.into_iter().map(|(n, _)| n).collect();
    result.sort();
    result
}

fn solve(reader: impl std::io::BufRead) -> i64 {
    let lines = parse_input(reader);

    let mut factors = [
        HashMap::<i64, Vec<Vec<i64>>>::new(),
        HashMap::<i64, Vec<Vec<i64>>>::new(),
        HashMap::<i64, Vec<Vec<i64>>>::new(),
    ];

    for (i, &((x1, y1, z1), (dx1, dy1, dz1))) in lines.iter().enumerate() {
        for &((x2, y2, z2), (dx2, dy2, dz2)) in lines.iter().skip(i + 1) {
            if dx1 == dx2 {
                let facts = prime_factors((x1 - x2).abs());
                factors[0].entry(dx1).or_default().push(facts);
            }

            if dy1 == dy2 {
                let facts = prime_factors((y1 - y2).abs());
                factors[1].entry(dy1).or_default().push(facts);
            }

            if dz1 == dz2 {
                let facts = prime_factors((z1 - z2).abs());
                factors[2].entry(dz1).or_default().push(facts);
            }
        }
    }

    let velocities: Vec<_> = factors
        .into_iter()
        .map(|m| {
            let m: HashMap<i64, Vec<i64>> = m
                .into_iter()
                .map(|(v, fs)| (v, common_elements(fs)))
                .collect();

            let mut len = 1;

            let mut first = true;
            let mut cands = HashSet::<i64>::new();

            while first || cands.len() != 1 {
                for (v, cs) in &m {
                    if cs.len() != len {
                        continue;
                    }

                    let mut v_candidates: Vec<i64> = Vec::new();
                    for &c in cs {
                        let mut new_candidates = vec![c, -c];
                        for cand in &v_candidates {
                            new_candidates.push(cand * c);
                        }
                        v_candidates.append(&mut new_candidates);
                    }

                    let mut candidates = HashSet::<i64>::new();
                    for c in v_candidates {
                        candidates.insert(v - c);
                    }

                    if first {
                        first = false;
                        cands = candidates;
                    } else {
                        cands = cands.intersection(&candidates).copied().collect();
                    }
                }

                len += 1;
            }

            cands.into_iter().next().unwrap()
        })
        .collect();

    let (vx, vy, vz) = (velocities[0], velocities[1], velocities[2]);

    let ((x1, y1, z1), (dx1, dy1, dz1)) = lines[0];
    let ((x2, y2, _), (dx2, dy2, _)) = lines[1];

    let cx1 = vx - dx1;
    let cy1 = vy - dy1;
    let cz1 = vz - dz1;

    let cx2 = vx - dx2;
    let cy2 = vy - dy2;

    let t2 = (cx1 * (y1 - y2) - cy1 * (x1 - x2)) / (cy1 * cx2 - cx1 * cy2);

    let x = x2 - cx2 * t2;
    let y = y2 - cy2 * t2;
    let z = z1 - cz1 * (x1 - x2) / cx1 - cz1 * cx2 * t2 / cx1;

    x + y + z
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    #[ignore]
    fn test_d24p2() {
        let reader = BufReader::new(File::open("d24/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 47);
    }
}
