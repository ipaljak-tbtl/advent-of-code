pub fn solve(input: &[String]) -> u128 {
    const N_MAX: i32 = 4000000;

    let mut positions = vec![];

    for line in input {
        let parts: Vec<&str> = line.split(' ').collect();

        let sx: i32 = parts[2][2..].trim_end_matches(',').parse().unwrap();
        let sy: i32 = parts[3][2..].trim_end_matches(':').parse().unwrap();

        let bx: i32 = parts[8][2..].trim_end_matches(',').parse().unwrap();
        let by: i32 = parts[9][2..].parse().unwrap();

        positions.push((sx, sy, bx, by));
    }

    for ty in 0..(N_MAX + 1) {
        let mut intervals = vec![];

        for (sx, sy, bx, by) in &positions {
            if (sy - ty).abs() > (sx - bx).abs() + (sy - by).abs() {
                continue;
            }

            let tmp = (sx - bx).abs() + (sy - by).abs() - (sy - ty).abs();

            let tx_min = (sx - tmp).max(0);
            let tx_max = (sx + tmp).min(N_MAX);

            if tx_min > N_MAX || tx_max < 0 {
                continue;
            }

            intervals.push((tx_min, tx_max));
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

        if merged_intervals.len() > 1 {
            return (merged_intervals[0].1 + 1) as u128 * N_MAX as u128 + ty as u128;
        }
    }

    0
}
