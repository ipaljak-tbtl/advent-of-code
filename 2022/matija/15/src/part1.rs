pub fn solve(input: &[String]) -> u32 {
    const TY: i32 = 2000000;

    let mut intervals = vec![];

    let mut beacons = std::collections::HashSet::new();

    for line in input {
        let parts: Vec<&str> = line.split(' ').collect();

        let sx: i32 = parts[2][2..].trim_end_matches(',').parse().unwrap();
        let sy: i32 = parts[3][2..].trim_end_matches(':').parse().unwrap();

        let bx: i32 = parts[8][2..].trim_end_matches(',').parse().unwrap();
        let by: i32 = parts[9][2..].parse().unwrap();

        let tmp = (sx - bx).abs() + (sy - by).abs() - (sy - TY).abs();

        if tmp < 0 {
            continue;
        }

        let tx_min = sx - tmp;
        let tx_max = sx + tmp;

        intervals.push((tx_min, tx_max));

        if by == TY {
            beacons.insert((bx, by));
        }
    }

    intervals.sort_by(|i1, i2| i1.0.cmp(&i2.0));

    let mut merged_intervals = vec![];
    merged_intervals.push(intervals[0]);

    for interval in intervals.into_iter().skip(1) {
        let prev = merged_intervals.pop().unwrap();

        if interval.0 > prev.1 {
            merged_intervals.push(prev);
            merged_intervals.push(interval);
        } else if interval.1 > prev.1 {
            merged_intervals.push((prev.0, interval.1));
        } else {
            merged_intervals.push(prev);
        }
    }

    let mut result = 0;

    for interval in merged_intervals {
        result += (interval.1 - interval.0) as u32 + 1;
    }

    result - (beacons.len() as u32)
}
